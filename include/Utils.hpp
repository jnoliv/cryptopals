#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <string_view>

namespace cryptopals
{
    std::string base64_encode(std::string_view hex_str);
    std::string hex_to_str(std::string_view hex_str);
}

#endif
