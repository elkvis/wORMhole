#pragma once

#include "Sql.h"

class SqlAggregateExpression : public SqlExpression
{
public:
    enum class ExpressionType
    {
        Sum,
        Count,
        Average,
        GroupConcat,
        Min,
        Max,
        StdDev,
        Variance,
    };
private:
    ExpressionType AggregateExpressionType;
    std::shared_ptr<SqlExpression> m_expression;
    std::string m_separator;

    std::string ExpressionTypeString() const
    {
        switch (AggregateExpressionType)
        {
            case ExpressionType::Sum:
                return "SUM";
            case ExpressionType::Count:
                return "COUNT";
            case ExpressionType::Average:
                return "AVG";
            case ExpressionType::GroupConcat:
                return "GROUP_CONCAT";
            case ExpressionType::Min:
                return "MIN";
            case ExpressionType::Max:
                return "MAX";
            case ExpressionType::StdDev:
                return "STDDEV";
            case ExpressionType::Variance:
                return "VARIANCE";
        }

        return {};
    }

public:
    template<SqlExpressionConcept Expression_T>
    SqlAggregateExpression(ExpressionType eType, const Expression_T& expression, const std::string& separator = ",") :
        SqlExpression{},
        AggregateExpressionType{eType},
        m_expression{expression.GetSharedPtrCopy()}
    {
        expression.GetType();
    }

    SqlAggregateExpression() = default;
    SqlAggregateExpression(const SqlAggregateExpression&) = default;
    SqlAggregateExpression(SqlAggregateExpression&&) = default;
    SqlAggregateExpression& operator=(const SqlAggregateExpression&) = default;
    SqlAggregateExpression& operator=(SqlAggregateExpression&&) = default;
    virtual ~SqlAggregateExpression() = default;

    virtual std::string ToString() const
    {
        std::string retVal = ExpressionTypeString() + "(" + m_expression->ToString();
        if (AggregateExpressionType == ExpressionType::GroupConcat) retVal += " SEPARATOR '" + m_separator + "'";
        retVal += ")";

        return retVal;
    }

    virtual std::string GetType() const { return "SqlAggregateExpression"; }

    virtual std::shared_ptr<SqlExpression> GetSharedPtrCopy() const override { return std::make_shared<SqlAggregateExpression>(*this); }
};

SqlAggregateExpression SqlExpression::Sum() 
{
    return {SqlAggregateExpression::ExpressionType::Sum, *this};
}

SqlAggregateExpression SqlExpression::Count()
{
    return {SqlAggregateExpression::ExpressionType::Count, *this};
}

SqlAggregateExpression SqlExpression::Average()
{
    return {SqlAggregateExpression::ExpressionType::Average, *this};
}

SqlAggregateExpression SqlExpression::GroupConcat(const std::string& separator)
{
    return {SqlAggregateExpression::ExpressionType::GroupConcat, *this, separator};
}

SqlAggregateExpression SqlExpression::Min()
{
    return {SqlAggregateExpression::ExpressionType::Min, *this};
}

SqlAggregateExpression SqlExpression::Max()
{
    return {SqlAggregateExpression::ExpressionType::Max, *this};
}

SqlAggregateExpression SqlExpression::StdDev()
{
    return {SqlAggregateExpression::ExpressionType::StdDev, *this};
}

SqlAggregateExpression SqlExpression::Variance()
{
    return {SqlAggregateExpression::ExpressionType::Variance, *this};
}
