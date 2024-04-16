#pragma once

#include <string>

namespace wORMhole
{
    class SqlTable
    {
    private:
    public:
        virtual ~SqlTable() = default;
        constexpr virtual std::string TableName() const = 0;
    };
}