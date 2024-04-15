#pragma once

#include "Sql.h"

class SqlOrderByExpression : public SqlExpression
{
private:
    std::shared_ptr<SqlExpression> m_expression;
    bool m_isDescending;
public:
    template<SqlExpressionConcept Expression_T>
    SqlOrderByExpression(const Expression_T& expression, bool isDescending = false) :
        SqlExpression{},
        m_expression{expression.GetSharedPtrCopy()},
        m_isDescending(isDescending)
    {

    }

    SqlOrderByExpression() = default;
    SqlOrderByExpression(const SqlOrderByExpression&) = default;
    SqlOrderByExpression(SqlOrderByExpression&&) = default;
    SqlOrderByExpression& operator=(const SqlOrderByExpression&) = default;
    SqlOrderByExpression& operator=(SqlOrderByExpression&&) = default;
    virtual ~SqlOrderByExpression() = default;

    virtual std::string ToString() const
    {
        if (m_isDescending) return m_expression->ToString() + " DESC";
        return m_expression->ToString();
    };

    virtual std::string GetType() const { return "SqlOrderByExpression"; }

    virtual std::shared_ptr<SqlExpression> GetSharedPtrCopy() const override { return std::make_shared<SqlOrderByExpression>(*this); }
};

template<SqlExpressionConcept Expression_T>
SqlOrderByExpression Descending(const Expression_T& expression)
{
    return {expression, true};
}