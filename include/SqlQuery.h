#pragma once

#include <vector>
#include <string>
#include <ranges>
#include <sstream>
#include "Sql.h"

namespace wORMhole
{
    template <typename Table_T>
    class SqlQuery
    {
    private:
        std::shared_ptr<SqlExpression> m_whereExpression;
        std::vector<std::shared_ptr<SqlExpression>> m_groupByExpression;
        std::vector<std::shared_ptr<SqlExpression>> m_orderByExpression;
        std::vector<std::shared_ptr<SqlExpression>> m_selectExpression;

    public:
        virtual ~SqlQuery() = default;

        virtual const std::vector<const wORMhole::SqlExpression*>& GetColumns() const = 0;

        template<SqlExpressionConcept Expression_T>
        SqlQuery& Where(const Expression_T& sqlExpression)
        {
            m_whereExpression = std::make_shared<Expression_T>(sqlExpression);
            return *this;
        }
        
        template<SqlExpressionConcept... Args>
        SqlQuery& OrderBy(Args... args)
        {
            using expander = std::vector<int>;
            (void)expander {
                0, (void(m_orderByExpression.push_back(std::make_unique<Args>(args))), 0)...
            };

            return *this;
        }
        
        template<SqlExpressionConcept... Args>
        SqlQuery& GroupBy(Args... args)
        {
            using expander = std::vector<int>;
            (void)expander {
                0, (void(m_groupByExpression.push_back(std::make_unique<Args>(args))), 0)...
            };
            return *this;
        }

        template<SqlExpressionConcept... Args>
        SqlQuery& Select(Args... args)
        {
            using expander = std::vector<int>;
            (void)expander {
                0, (void(m_selectExpression.push_back(std::make_unique<Args>(args))), 0)...
            };
            return *this;
        }

        std::string ToString() const
        {
            std::ostringstream oss;

            oss << "SELECT ";
            if (m_selectExpression.empty())
            {
                for (auto [i, exp] : GetColumns() | std::views::enumerate)
                {
                    if (i) oss << ", ";
                    oss << exp->ToString();
                }
            }
            else
            {
                for (auto [i, exp] : m_selectExpression | std::views::enumerate)
                {
                    if (i) oss << ", ";
                    oss << exp->ToString();
                }
            }
            oss << '\n';

            oss << "FROM " << Table_T{}.TableName() << "\nWHERE " << m_whereExpression->ToString() << '\n';

            if (!m_orderByExpression.empty())
            {
                oss << "ORDER BY ";
                for (auto [i, exp] : m_orderByExpression | std::views::enumerate)
                {
                    if (i) oss << ", ";
                    oss << exp->ToString();
                }
                oss << '\n';
            }

            if (!m_groupByExpression.empty())
            {
                oss << "GROUP BY ";
                for (auto [i, exp] : m_groupByExpression | std::views::enumerate)
                {
                    if (i) oss << ", ";
                    oss << exp->ToString();
                }
                oss << '\n';
            }


            return oss.str();
        }
    };
}
