#pragma once

#include "Sql.h"
#include "SqlTable.h"
#include <optional>
#include <utility>

template<typename Value_T, typename Table_T>
class SqlColumn : public SqlExpression
{
    static_assert(std::is_base_of_v<SqlTable, Table_T>);

    std::string m_name;
public:
    SqlColumn(const std::string& name) : m_name{name}
    {

    }
    virtual ~SqlColumn() = default;
    inline virtual constexpr std::string ToString() const override
    {
        return Table_T{}.TableName() + '.' + m_name;
    };

    virtual constexpr std::string GetType() const
    {
        return "SqlColumn";
    }
};