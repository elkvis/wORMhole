#pragma once

#include "Sql.h"
#include "SqlTable.h"
#include <optional>
#include <utility>

template<typename Value_T, typename Table_T, typename = std::enable_if_t<std::is_base_of_v<SqlTable, Table_T>>>
class SqlColumn : public SqlExpression
{
    static_assert(std::is_base_of_v<SqlTable, Table_T>);

    std::string m_name;
public:
    SqlColumn(const std::string& name) : m_name{name}
    {

    }
    
    SqlColumn() = default;
    SqlColumn(const SqlColumn&) = default;
    SqlColumn(SqlColumn&&) = default;
    SqlColumn& operator=(const SqlColumn&) = default;
    SqlColumn& operator=(SqlColumn&&) = default;
    virtual ~SqlColumn() = default;

    inline virtual constexpr std::string ToString() const override
    {
        return Table_T{}.TableName() + '.' + m_name;
    };

    virtual constexpr std::string GetType() const
    {
        return "SqlColumn";
    }

    virtual std::shared_ptr<SqlExpression> GetSharedPtrCopy() const override { return std::make_shared<SqlColumn>(*this); }
};