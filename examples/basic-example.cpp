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

  std::vector<const wORMhole::SqlExpression*> Columns {&id, &name, &age};

  virtual const std::vector<const wORMhole::SqlExpression*>& GetColumns() const override { return Columns; }
};


// country table from MySQL's "world" example database
struct country : public wORMhole::SqlTable
{
  constexpr virtual std::string TableName() const override { return "country"; }
  wORMhole::SqlValue<std::string> Code;
  wORMhole::SqlValue<std::string> Name;
  wORMhole::SqlValue<int> Continent;
  wORMhole::SqlValue<std::string> Region;
  wORMhole::SqlValue<double> SurfaceArea;
  wORMhole::SqlValue<int> IndepYear;
  wORMhole::SqlValue<int> Population;
  wORMhole::SqlValue<double> LifeExpectancy;
  wORMhole::SqlValue<double> GNP;
  wORMhole::SqlValue<double> GNPOld;
  wORMhole::SqlValue<std::string> LocalName;
  wORMhole::SqlValue<std::string> GovernmentForm;
  wORMhole::SqlValue<std::string> HeadOfState;
  wORMhole::SqlValue<int> Capital;
  wORMhole::SqlValue<std::string> Code2;
};

// query representing the country table
struct countryQuery : public wORMhole::SqlQuery<country>
{
  wORMhole::SqlColumn<std::string, country> Code{"Code"};
  wORMhole::SqlColumn<std::string, country> Name{"Name"};
  wORMhole::SqlColumn<int, country> Continent{"Continent"};
  wORMhole::SqlColumn<std::string, country> Region{"Region"};
  wORMhole::SqlColumn<double, country> SurfaceArea{"SurfaceArea"};
  wORMhole::SqlColumn<int, country> IndepYear{"IndepYear"};
  wORMhole::SqlColumn<int, country> Population{"Population"};
  wORMhole::SqlColumn<double, country> LifeExpectancy{"LifeExpectancy"};
  wORMhole::SqlColumn<double, country> GNP{"GNP"};
  wORMhole::SqlColumn<double, country> GNPOld{"GNPOld"};
  wORMhole::SqlColumn<std::string, country> LocalName{"LocalName"};
  wORMhole::SqlColumn<std::string, country> GovernmentForm{"GovernmentForm"};
  wORMhole::SqlColumn<std::string, country> HeadOfState{"HeadOfState"};
  wORMhole::SqlColumn<int, country> Capital{"Capital"};
  wORMhole::SqlColumn<std::string, country> Code2{"Code2"};  

  std::vector<const wORMhole::SqlExpression*> Columns {&Code, &Name, &Continent, &Region, &SurfaceArea, &IndepYear, &Population, &LifeExpectancy, &GNP, &GNPOld, &LocalName, &GovernmentForm, &HeadOfState, &Capital, &Code2};

  virtual const std::vector<const wORMhole::SqlExpression*>& GetColumns() const override { return Columns; }
};

int main()
{
  Table1Query query;
  using wORMhole::operator""sle;

  auto& q = query.Where(((query.age == query.id) && (query.age + query.name > query.id)))
                 .GroupBy(query.name)
                 .OrderBy(query.age, wORMhole::Descending(query.id))
                 .Select(query.age.Average(), "Name: "sle + query.name, (query.id + query.age).Count(), 3sle, "hello, world!"sle, 3.141592sle);

  std::cout << q.ToString() << '\n';

  countryQuery cQuery;
  auto& q2 = cQuery.Where(cQuery.GNP > 1e+12sle)
                   .OrderBy(wORMhole::Descending(cQuery.GNP))
                   .Delete()
                   .Limit(10, 35)
                   .Explain();

  std::cout << q2.ToString() << '\n';

  return 0;
}
