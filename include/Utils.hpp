#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <string_view>

namespace cryptopals
{
	std::string base64_encode(std::string_view hex_str);
	std::string hex_to_ascii(std::string_view hex_str);
	std::string ascii_to_hex(std::string_view ascii_str);
	std::string fixed_xor(std::string_view in1, std::string_view in2);
}

#endif
