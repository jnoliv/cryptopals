#include <array>
#include <cmath>
#include <string>
#include <string_view>

#include "Utils.hpp"

namespace cryptopals
{
	/**
	 * Returns a string containing the base64 encoding of the given string_view.
	 * 
	 * Based on the algorithm described in
	 * https://en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/Base64#C++
	 */
	std::string base64_encode(std::string_view str)
	{
		constexpr char padding_char = '=';
		constexpr std::string_view lookup_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

		std::string base64_str;
		base64_str.reserve(std::ceil(str.size() / 3.0) * 4);

		size_t idx;
		long accum;
		for (size_t i = 0; i < (str.size() / 3); i++)
		{
			idx = 3 * i;

			accum  = str[idx]     << 16;
			accum += str[idx + 1] <<  8;
			accum += str[idx + 2];

			base64_str.append(1, lookup_table[(accum & 0xFC0000) >> 18]);
			base64_str.append(1, lookup_table[(accum & 0x03F000) >> 12]);
			base64_str.append(1, lookup_table[(accum & 0x000FC0) >>  6]);
			base64_str.append(1, lookup_table[(accum & 0x00003F)]);
		}
		idx += 3;

		switch (str.size() % 3)
		{
		case 1:
			accum = str[idx];
			accum <<= 4;

			base64_str.append(1, lookup_table[(accum & 0xFC0) >> 6]);
			base64_str.append(1, lookup_table[(accum & 0x03F)]);
			base64_str.append(2, padding_char);

			break;

		case 2:
			accum = str[idx] << 8;
			accum += str[idx + 1];
			accum <<= 2;

			base64_str.append(1, lookup_table[(accum & 0x3F000) >> 12]);
			base64_str.append(1, lookup_table[(accum & 0x00FC0) >> 6]);
			base64_str.append(1, lookup_table[(accum & 0x0003F)]);
			base64_str.append(1, padding_char);

			break;
		}

		return base64_str;
	}


	/**
	 * Returns the ASCII string that is hex encoded in the given string view.
	 */
	std::string hex_to_str(std::string_view hex_str)
	{
		std::string ascii_str;
		ascii_str.reserve(hex_str.size() / 2);

		for (size_t i = 0; i < hex_str.size(); i += 2)
		{
			std::string aux { hex_str.substr(i, 2) };
			ascii_str.append(1, stoul(aux, 0, 16));
		}

		return ascii_str;
	}
}