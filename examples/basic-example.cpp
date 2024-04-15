#include <iostream>
#include "Sql.h"

struct Table1 : public SqlTable
{
  constexpr virtual std::string TableName() const override { return "Table1"; }
  SqlValue<int> id;
  SqlValue<std::string> name;
  SqlValue<int> age;
};

struct Table1Query : public SqlQuery<Table1>
{
  SqlColumn<int, Table1> id{"id"};
  SqlColumn<std::string, Table1> name{"name"};
  SqlColumn<int, Table1> age{"age"};
};

int main()
{
  Table1Query query;

  auto q = query.Where(((query.age == query.id) && (query.age + query.name > query.id)))
                .GroupBy(query.name)
                .OrderBy(query.age)
                .Select(query.age, "Name: "sle + query.name, 3sle, "hello, world!"sle, 3.141592sle);

  std::cout << q.ToString() << '\n';

  return 0;
}