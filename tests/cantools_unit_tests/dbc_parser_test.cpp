#include <gtest/gtest.h>
#include <cantools/parsers/dbc_parser.h>

#include <string>

namespace
{
    std::string const valid_message = "2301234567 TestMessageName: 8 Vector__XXX";
}

TEST(DbcParserTest, ParseValidMessage)
{
    dbc_message message = dbc::on_parse_message(valid_message);
    EXPECT_EQ(message.name, "TestMessageName");
    EXPECT_EQ(message.id, 2301234567);
    EXPECT_EQ(message.length, 8);
    EXPECT_EQ(message.sender, "Vector__XXX");
}
