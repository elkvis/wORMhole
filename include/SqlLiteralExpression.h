#pragma once

#include "SqlExpression.h"

class SqlLiteralExpression : public SqlExpression
{
    std::string m_value;
public:
    SqlLiteralExpression(const std::string& value) :
        SqlExpression{},
        m_value{value}
    {

    }

    SqlLiteralExpression() = default;
    SqlLiteralExpression(const SqlLiteralExpression&) = default;
    SqlLiteralExpression(SqlLiteralExpression&&) = default;
    SqlLiteralExpression& operator=(const SqlLiteralExpression&) = default;
    SqlLiteralExpression& operator=(SqlLiteralExpression&&) = default;
    virtual ~SqlLiteralExpression() = default;

    virtual std::string ToString() const override { return m_value; }
    virtual std::string GetType() const override { return "SqlLiteralExpression"; }

    virtual std::shared_ptr<SqlExpression> GetSharedPtrCopy() const override { return std::make_shared<SqlLiteralExpression>(*this); }
};

SqlLiteralExpression operator ""sle(unsigned long long int val)
{
    return SqlLiteralExpression{ std::to_string(val) };
}

SqlLiteralExpression operator ""sle(long double val)
{
    return SqlLiteralExpression{ std::to_string(val) };
}
SqlLiteralExpression operator ""sle(const char* val, std::size_t len)
{
    return SqlLiteralExpression{ "'" + std::string(val, len) + "'" };
}
