#pragma once

#include <optional>

namespace wORMhole
{
    template <typename ValueT>
    class SqlValue
    {
        std::optional<ValueT> m_value;
    };
}
