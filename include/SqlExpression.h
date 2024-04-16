#pragma once

#include "Sql.h"
#include <string>
#include <iostream>

namespace wORMhole
{
    class SqlAggregateExpression;

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

        inline SqlAggregateExpression Sum();
        inline SqlAggregateExpression Count();
        inline SqlAggregateExpression Average();
        inline SqlAggregateExpression GroupConcat(const std::string& separator = ",");
        inline SqlAggregateExpression Min();
        inline SqlAggregateExpression Max();
        inline SqlAggregateExpression StdDev();
        inline SqlAggregateExpression Variance();

        virtual std::shared_ptr<SqlExpression> GetSharedPtrCopy() const { return std::make_shared<SqlExpression>(*this); }
    };

    template<typename T>
    concept SqlExpressionConcept = std::is_base_of<SqlExpression, T>::value;

    std::ostream& operator<<(std::ostream& os, const SqlExpression& exp)
    {
        os << exp.ToString();
        return os;
    }
}
