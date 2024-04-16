#include <iostream>
#include "Sql.h"

struct Table1 : public wORMhole::SqlTable
{
  constexpr virtual std::string TableName() const override { return "Table1"; }
  wORMhole::SqlValue<int> id;
  wORMhole::SqlValue<std::string> name;
  wORMhole::SqlValue<int> age;
};

struct Table1Query : public wORMhole::SqlQuery<Table1>
{
  wORMhole::SqlColumn<int, Table1> id{"id"};
  wORMhole::SqlColumn<std::string, Table1> name{"name"};
  wORMhole::SqlColumn<int, Table1> age{"age"};

  std::vector<const wORMhole::SqlExpression*> Columns = {&id, &name, &age};
};

int main()
{
  Table1Query query;
  using wORMhole::operator""sle;

  auto q = query.Where(((query.age == query.id) && (query.age + query.name > query.id)))
                .GroupBy(query.name)
                .OrderBy(query.age, wORMhole::Descending(query.id))
                .Select(query.age.Average(), "Name: "sle + query.name, (query.id + query.age).Count(), 3sle, "hello, world!"sle, 3.141592sle);

  std::cout << q.ToString() << '\n';

  return 0;
}