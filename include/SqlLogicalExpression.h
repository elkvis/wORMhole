#pragma once

#include "SqlExpression.h"

class SqlLogicalExpression : public SqlExpression
{
public:
    enum class ExpressionType
    {
        LogicalAnd,
        LogicalOr,
        LogicalNot
    };

private:
    ExpressionType LogicalExpressionType;
    std::shared_ptr<SqlExpression> m_lhs;
    std::shared_ptr<SqlExpression> m_rhs;

    std::string ExpressionTypeString() const
    {
        switch (LogicalExpressionType)
        {
            case ExpressionType::LogicalAnd:
                return "&&";
            case ExpressionType::LogicalOr:
                return "||";
            case ExpressionType::LogicalNot:
                return "!";
        }

        return {};
    }

public:
    template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
    SqlLogicalExpression(ExpressionType eType, const Expression_T1& lhs, const Expression_T2& rhs) :
        SqlExpression{},
        LogicalExpressionType{eType},
        m_lhs{std::make_shared<Expression_T1>(lhs)},
        m_rhs{std::make_shared<Expression_T2>(rhs)}
    {
    }
    
    SqlLogicalExpression() = default;
    SqlLogicalExpression(const SqlLogicalExpression&) = default;
    SqlLogicalExpression(SqlLogicalExpression&&) = default;
    SqlLogicalExpression& operator=(const SqlLogicalExpression&) = default;
    SqlLogicalExpression& operator=(SqlLogicalExpression&&) = default;
    virtual ~SqlLogicalExpression() = default;

    inline virtual std::string ToString() const override
    {
        if (LogicalExpressionType == ExpressionType::LogicalNot)
        {
            return ExpressionTypeString() + m_rhs->ToString();
        }
        else
        {
            return 
                '(' +
                m_lhs->ToString() + ' ' +
                ExpressionTypeString() + ' ' +
                m_rhs->ToString() + ')';
        }
    }

    virtual std::string GetType() const
    {
        return "SqlLogicalExpression";
    }
};

template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
SqlLogicalExpression operator && (const Expression_T1& lhs, const Expression_T2& rhs)
{
    return { SqlLogicalExpression::ExpressionType::LogicalAnd, lhs, rhs };
}

template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
SqlLogicalExpression operator || (const Expression_T1& lhs, const Expression_T2& rhs)
{
    return { SqlLogicalExpression::ExpressionType::LogicalOr, lhs, rhs };
}

template<SqlExpressionConcept Expression_T>
SqlLogicalExpression operator ! (const Expression_T& op)
{
    return { SqlLogicalExpression::ExpressionType::LogicalNot, op, op };
}