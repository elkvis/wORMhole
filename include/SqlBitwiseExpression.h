#pragma once

#include "Sql.h"

namespace wORMhole
{
    class SqlBitwiseExpression : public SqlExpression
    {
    public:
        enum class ExpressionType
        {
            BitwiseAnd,
            BitwiseOr,
            BitwiseNot,
            BitwiseXor
        };

    private:
        ExpressionType BitwiseExpressionType;
        std::shared_ptr<SqlExpression> m_lhs;
        std::shared_ptr<SqlExpression> m_rhs;

        std::string ExpressionTypeString() const
        {
            switch (BitwiseExpressionType)
            {
                case ExpressionType::BitwiseAnd:
                    return "&";
                case ExpressionType::BitwiseOr:
                    return "|";
                case ExpressionType::BitwiseNot:
                    return "~";
                case ExpressionType::BitwiseXor:
                    return "^";
            }

            return {};
        }
        
    public:
        template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
        SqlBitwiseExpression(ExpressionType eType, const Expression_T1& lhs, const Expression_T2& rhs) :
            SqlExpression{},
            BitwiseExpressionType{eType},
            m_lhs{lhs.GetSharedPtrCopy()},
            m_rhs{rhs.GetSharedPtrCopy()}
        {
        }
        
        SqlBitwiseExpression() = default;
        SqlBitwiseExpression(const SqlBitwiseExpression&) = default;
        SqlBitwiseExpression(SqlBitwiseExpression&&) = default;
        SqlBitwiseExpression& operator=(const SqlBitwiseExpression&) = default;
        SqlBitwiseExpression& operator=(SqlBitwiseExpression&&) = default;
        virtual ~SqlBitwiseExpression() = default;

        inline virtual std::string ToString() const override
        {
            if (BitwiseExpressionType == ExpressionType::BitwiseNot)
                return ExpressionTypeString() + m_rhs->ToString();
            else
                return
                    m_lhs->ToString() + ' ' +
                    ExpressionTypeString() + ' ' +
                    m_rhs->ToString();
        }

        virtual std::string GetType() const
        {
            return "SqlBitwiseExpression";
        }

        virtual std::shared_ptr<SqlExpression> GetSharedPtrCopy() const override { return std::make_shared<SqlBitwiseExpression>(*this); }
    };

    template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
    SqlBitwiseExpression operator & (const Expression_T1& lhs, const Expression_T2& rhs)
    {
        return { SqlBitwiseExpression::ExpressionType::BitwiseAnd, lhs, rhs };
    }

    template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
    SqlBitwiseExpression operator | (const Expression_T1& lhs, const Expression_T2& rhs)
    {
        return { SqlBitwiseExpression::ExpressionType::BitwiseOr, lhs, rhs };
    }

    template<SqlExpressionConcept Expression_T>
    SqlBitwiseExpression operator ~ (const Expression_T& op)
    {
        return { SqlBitwiseExpression::ExpressionType::BitwiseNot, op, op };
    }

    template<SqlExpressionConcept Expression_T1, SqlExpressionConcept Expression_T2>
    SqlBitwiseExpression operator ^ (const Expression_T1& lhs, const Expression_T2& rhs)
    {
        return { SqlBitwiseExpression::ExpressionType::BitwiseXor, lhs, rhs };
    }
}
