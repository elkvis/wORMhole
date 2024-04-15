#pragma once

#include <optional>

template <typename ValueT>
class SqlValue
{
    std::optional<ValueT> m_value;
};
