#include <array>
#include <cassert>
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
	std::string hex_to_ascii(std::string_view hex_str)
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

	/**
	 * Returns the hex string that is ASCII encoded in the given string view.
	 */
	std::string ascii_to_hex(std::string_view ascii_str)
	{
		std::string hex_str;
		hex_str.reserve(ascii_str.size() * 2);

		// Turns 4 bits received as an int into the corresponding hex char
		auto nibble_to_hex = [](const int& nibble)
			{
				if (nibble < 10)
					return '0' + nibble;
				else
					return 'a' + (nibble - 10);
			};

		for(const char& c : ascii_str)
		{
			hex_str.append(1, nibble_to_hex((c & 0xF0) >> 4));
			hex_str.append(1, nibble_to_hex( c & 0x0F));
		}

		return hex_str;
	}

	/**
	 * Returns the fixed XOR of the two given strings.
	 * 
	 * The input strings must be of equal size, or an assert is triggered.
	 */
	std::string fixed_xor(std::string_view in1, std::string_view in2)
	{
		assert(in1.size() == in2.size());

		std::string out;
		out.reserve(in1.size());

		for(size_t i = 0; i < in1.size(); i++)
			out.append(1, in1[i] ^ in2[i]);

		return out;
	}
}
