#pragma once

#include "SqlExpression.h"

class SqlArithmeticExpression : public SqlExpression
{
public:
    enum class ExpressionType
    {
        ArithmeticAdd,
        ArithmeticSubtract,
        ArithmeticNegation,
        ArithmeticMultiply,
        ArithmeticDivide,
        ArithmeticModulus
    };

private:
    ExpressionType ArithmeticExpressionType;
    std::shared_ptr<SqlExpression> m_lhs;
    std::shared_ptr<SqlExpression> m_rhs;
    
    std::string ExpressionTypeString() const
    {
        switch (ArithmeticExpressionType)
        {
            case ExpressionType::ArithmeticAdd:
                return "+";
            case ExpressionType::ArithmeticSubtract:
                return "-";
            case ExpressionType::ArithmeticNegation:
                return "-";
            case ExpressionType::ArithmeticMultiply:
                return "*";
            case ExpressionType::ArithmeticDivide:
                return "/";
            case ExpressionType::ArithmeticModulus:
                return "%";
        }

        return {};
    }

public:
    template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
    SqlArithmeticExpression(ExpressionType eType, const Expression_T1& lhs, const Expression_T2& rhs) :
        SqlExpression{},
        ArithmeticExpressionType{eType},
        m_lhs{lhs.GetSharedPtrCopy()},
        m_rhs{rhs.GetSharedPtrCopy()}
    {
    }

    SqlArithmeticExpression() = default;
    SqlArithmeticExpression(const SqlArithmeticExpression&) = default;
    SqlArithmeticExpression(SqlArithmeticExpression&&) = default;
    SqlArithmeticExpression& operator=(const SqlArithmeticExpression&) = default;
    SqlArithmeticExpression& operator=(SqlArithmeticExpression&&) = default;
    virtual ~SqlArithmeticExpression() = default;
    
    inline virtual std::string ToString() const override
    {
        if (ArithmeticExpressionType == ExpressionType::ArithmeticNegation)
            return ExpressionTypeString() + m_rhs->ToString();
        else
            return 
                '(' +
                m_lhs->ToString() + ' ' +
                ExpressionTypeString() +  ' ' +
                m_rhs->ToString() +
                ')';
    };

    virtual std::string GetType() const
    {
        return "SqlArithmeticExpression";
    }

    virtual std::shared_ptr<SqlExpression> GetSharedPtrCopy() const override { return std::make_shared<SqlArithmeticExpression>(*this); }
};

template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
SqlArithmeticExpression operator + (const Expression_T1& lhs, const Expression_T2& rhs)
{
    return { SqlArithmeticExpression::ExpressionType::ArithmeticAdd, lhs, rhs };
}

template<SqlExpressionConcept Expression_T>
SqlArithmeticExpression operator - (const Expression_T& op) // negation
{
    return { SqlArithmeticExpression::ExpressionType::ArithmeticNegation, op, op };
}

template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
SqlArithmeticExpression operator - (const Expression_T1& lhs, const Expression_T2& rhs)
{
    return { SqlArithmeticExpression::ExpressionType::ArithmeticSubtract, lhs, rhs };
}

template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
SqlArithmeticExpression operator * (const Expression_T1& lhs, const Expression_T2& rhs)
{
    return { SqlArithmeticExpression::ExpressionType::ArithmeticMultiply, lhs, rhs };
}

template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
SqlArithmeticExpression operator / (const Expression_T1& lhs, const Expression_T2& rhs)
{
    return { SqlArithmeticExpression::ExpressionType::ArithmeticDivide, lhs, rhs };
}

template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
SqlArithmeticExpression operator % (const Expression_T1& lhs, const Expression_T2& rhs)
{
    return { SqlArithmeticExpression::ExpressionType::ArithmeticModulus, lhs, rhs };
}