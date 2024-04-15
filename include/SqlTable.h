#pragma once

#include <string>

class SqlTable
{
private:
public:
    virtual ~SqlTable() = default;
    constexpr virtual std::string TableName() const = 0;
};