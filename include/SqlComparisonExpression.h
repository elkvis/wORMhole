#pragma once

#include "Sql.h"

namespace wORMhole
{
    class SqlComparisonExpression : public SqlExpression
    {
    public:
        enum class ExpressionType
        {
            ComparisonEqual,
            ComparisonNotEqual,
            ComparisonLess,
            ComparisonLessEqual,
            ComparisonGreater,
            ComparisonGreaterEqual
        };

    private:
        ExpressionType ComparisonExpressionType;
        std::shared_ptr<SqlExpression> m_lhs;
        std::shared_ptr<SqlExpression> m_rhs;

        std::string ExpressionTypeString() const
        {
            switch (ComparisonExpressionType)
            {
                case ExpressionType::ComparisonEqual:
                    return "=";
                case ExpressionType::ComparisonNotEqual:
                    return "!=";
                case ExpressionType::ComparisonLess:
                    return "<";
                case ExpressionType::ComparisonLessEqual:
                    return "<=";
                case ExpressionType::ComparisonGreater:
                    return ">";
                case ExpressionType::ComparisonGreaterEqual:
                    return ">=";
            }

            return {};
        }

    public:
        template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
        SqlComparisonExpression(ExpressionType eType, const Expression_T1& lhs, const Expression_T2& rhs) :
            SqlExpression{},
            ComparisonExpressionType(eType),
            m_lhs{lhs.GetSharedPtrCopy()},
            m_rhs{rhs.GetSharedPtrCopy()}
        {
        }

        SqlComparisonExpression() = default;
        SqlComparisonExpression(const SqlComparisonExpression&) = default;
        SqlComparisonExpression(SqlComparisonExpression&&) = default;
        SqlComparisonExpression& operator=(const SqlComparisonExpression&) = default;
        SqlComparisonExpression& operator=(SqlComparisonExpression&&) = default;
        virtual ~SqlComparisonExpression() = default;

        inline virtual std::string ToString() const override
        {
            return 
                '(' +
                m_lhs->ToString() + ' ' +
                ExpressionTypeString() +  ' ' +
                m_rhs->ToString() +
                ')';
        }

        virtual std::string GetType() const
        {
            return "SqlComparisonExpression";
        }
        
        virtual std::shared_ptr<SqlExpression> GetSharedPtrCopy() const override { return std::make_shared<SqlComparisonExpression>(*this); }
    };

    template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
    SqlComparisonExpression operator == (const Expression_T1& lhs, const Expression_T2& rhs)
    {
        return { SqlComparisonExpression::ExpressionType::ComparisonEqual, lhs, rhs };
    }

    template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
    SqlComparisonExpression operator != (const Expression_T1& lhs, const Expression_T2& rhs)
    {
        return { SqlComparisonExpression::ExpressionType::ComparisonNotEqual, lhs, rhs };
    }

    template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
    SqlComparisonExpression operator < (const Expression_T1& lhs, const Expression_T2& rhs)
    {
        return { SqlComparisonExpression::ExpressionType::ComparisonLess, lhs, rhs };
    }

    template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
    SqlComparisonExpression operator <= (const Expression_T1& lhs, const Expression_T2& rhs)
    {
        return { SqlComparisonExpression::ExpressionType::ComparisonLessEqual, lhs, rhs };
    }

    template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
    SqlComparisonExpression operator > (const Expression_T1& lhs, const Expression_T2& rhs)
    {
        return { SqlComparisonExpression::ExpressionType::ComparisonGreater, lhs, rhs };
    }

    template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
    SqlComparisonExpression operator >= (const Expression_T1& lhs, const Expression_T2& rhs)
    {
        return { SqlComparisonExpression::ExpressionType::ComparisonGreaterEqual, lhs, rhs };
    }
}
