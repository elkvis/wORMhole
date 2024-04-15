#pragma once

#include <string>
#include <iostream>

class SqlExpression
{
public:
    SqlExpression() = default;
    SqlExpression(const SqlExpression&) = default;
    SqlExpression(SqlExpression&&) = default;
    SqlExpression& operator=(const SqlExpression&) = default;
    SqlExpression& operator=(SqlExpression&&) = default;
    virtual ~SqlExpression() = default;

    virtual std::string ToString() const { return {}; };
    virtual std::string GetType() const { return "SqlExpression"; }
};

template<typename T>
concept SqlExpressionConcept = std::is_base_of<SqlExpression, T>::value;

std::ostream& operator<<(std::ostream& os, const SqlExpression& exp)
{
    os << exp.ToString();
    return os;
}