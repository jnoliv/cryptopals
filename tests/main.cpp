#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <string_view>

#include "Utils.hpp"

using namespace cryptopals;
using namespace std::string_view_literals;

namespace
{
	constexpr std::string_view s1c1_hex_str = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"sv;
}

TEST_CASE("String is encoded to base64", "[base64_encode]")
{
	CHECK(base64_encode("any carnal pleasure."sv) == "YW55IGNhcm5hbCBwbGVhc3VyZS4=");
	CHECK(base64_encode("any carnal pleasure"sv)  == "YW55IGNhcm5hbCBwbGVhc3VyZQ==");
	CHECK(base64_encode("any carnal pleasur"sv)   == "YW55IGNhcm5hbCBwbGVhc3Vy");
	CHECK(base64_encode("any carnal pleasu"sv)    == "YW55IGNhcm5hbCBwbGVhc3U=");
	CHECK(base64_encode("any carnal pleas"sv)     == "YW55IGNhcm5hbCBwbGVhcw==");
}

TEST_CASE("Hex string is decoded to ASCII", "[hex_to_str]")
{
	CHECK(hex_to_str(s1c1_hex_str) == "I'm killing your brain like a poisonous mushroom");
}

TEST_CASE("Hex string is encoded to base64", "[challenges][set1]")
{
	CHECK(base64_encode(hex_to_str(s1c1_hex_str)) == "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t");
}
