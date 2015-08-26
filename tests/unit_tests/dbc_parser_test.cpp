#include <gtest/gtest.h>
#include <cantools/parsers/dbc_parser.h>

#include <string>

namespace
{
    std::string const valid_message = "2301234567 TestMessageName: 8 Vector__XXX";
    std::string const valid_signal  = "TestSignalName : 0|8@1+ (1,0) [0|256] \"deg C\" Vector__XXX";
}

TEST(DbcParserTest, ParseValidMessage)
{
    dbc_message message = dbc::on_parse_message(valid_message);
    EXPECT_EQ(message.name, "TestMessageName");
    EXPECT_NE(message.name, "TestMessageName:");
    EXPECT_EQ(message.id, 2301234567);
    EXPECT_EQ(message.length, 8);
    EXPECT_EQ(message.sender, "Vector__XXX");
}

TEST(DbcParserTest, ExtractBitStartAndBitLengthFromSignal)
{
    auto result = dbc::detail::extract_bit_start_and_length_from_string(valid_signal);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 8);
}

TEST(DbcParserTest, ExtractEndiannessFromSignal)
{
    auto result = dbc::detail::extract_endianness_from_string(valid_signal);
    EXPECT_EQ(result, CAN_LITTLE_ENDIAN);
}

TEST(DbcParserTest, ExtractSignednessFromSignal)
{
    auto result = dbc::detail::extract_signedness_from_string(valid_signal);
    EXPECT_EQ(result, UNSIGNED);
}

TEST(DbcParserTest, ExtractScaleAndOffsetFromSignal)
{
    auto result = dbc::detail::extract_scale_and_offset_from_string(valid_signal);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 0);
}

TEST(DbcParserTest, ExtractMinAndMaxFromSignal)
{
    auto result = dbc::detail::extract_min_and_max_from_string(valid_signal);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 256);
}

TEST(DbcParserTest, ExtractUnitFromSignal)
{
    auto result = dbc::detail::extract_unit_from_string(valid_signal);
    EXPECT_EQ(result, "deg C");
}

TEST(DbcParserTest, ParseValidSignal)
{
    dbc_signal signal = dbc::on_parse_signal(valid_signal);
    EXPECT_EQ(signal.name, "TestSignalName");
    EXPECT_EQ(signal.start_bit, 0);
    EXPECT_EQ(signal.bit_length, 8);
    EXPECT_EQ(signal.endianness, CAN_LITTLE_ENDIAN);
    EXPECT_EQ(signal.signedness, UNSIGNED);
    EXPECT_DOUBLE_EQ(signal.scale, 1);
    EXPECT_DOUBLE_EQ(signal.offset, 0);
    EXPECT_DOUBLE_EQ(signal.min, 0);
    EXPECT_DOUBLE_EQ(signal.max, 256);
    EXPECT_EQ(signal.unit, "deg C");
}
