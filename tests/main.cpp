#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <string_view>

#include "Utils.hpp"

using namespace cryptopals;
using namespace std::string_view_literals;

namespace
{
	constexpr std::string_view s1c01_hex_str = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"sv;

	constexpr std::string_view s1c02_in1 = "1c0111001f010100061a024b53535009181c"sv;
	constexpr std::string_view s1c02_in2 = "686974207468652062756c6c277320657965"sv;
	constexpr std::string_view s1c02_out = "746865206b696420646f6e277420706c6179"sv;
}

TEST_CASE("String is encoded to base64", "[base64_encode]")
{
	CHECK(base64_encode("any carnal pleasure."sv) == "YW55IGNhcm5hbCBwbGVhc3VyZS4=");
	CHECK(base64_encode("any carnal pleasure"sv)  == "YW55IGNhcm5hbCBwbGVhc3VyZQ==");
	CHECK(base64_encode("any carnal pleasur"sv)   == "YW55IGNhcm5hbCBwbGVhc3Vy");
	CHECK(base64_encode("any carnal pleasu"sv)    == "YW55IGNhcm5hbCBwbGVhc3U=");
	CHECK(base64_encode("any carnal pleas"sv)     == "YW55IGNhcm5hbCBwbGVhcw==");
}

TEST_CASE("Hex string is decoded to ASCII", "[hex_to_ascii]")
{
	CHECK(hex_to_ascii(s1c01_hex_str) == "I'm killing your brain like a poisonous mushroom");
}

TEST_CASE("ASCII string is encoded to hex", "[ascii_to_hex]")
{
	CHECK(ascii_to_hex("I'm killing your brain like a poisonous mushroom") == s1c01_hex_str);
}

TEST_CASE("Hex string is encoded to base64", "[challenges][s1c01]")
{
	CHECK(base64_encode(hex_to_ascii(s1c01_hex_str)) == "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t");
}

TEST_CASE("Fixed XOR of two hex strings is computed", "[challenges][s1c02]")
{
	CHECK(ascii_to_hex(fixed_xor(hex_to_ascii(s1c02_in1), hex_to_ascii(s1c02_in2))) == s1c02_out);
}
