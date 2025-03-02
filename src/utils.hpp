#pragma once

#include <cstdint>

namespace pragma
{

using category_id_t = std::uint32_t;

constexpr category_id_t djb2_hash(const char* str, unsigned int hash = 5381) 
{
    return (str[0] == '\0') ? hash : djb2_hash(str + 1, ((hash << 5) + hash) + static_cast<unsigned char>(str[0]));
}

}
