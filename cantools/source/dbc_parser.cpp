#include <cantools/parsers/dbc_parser.h>

#include <sstream>

namespace dbc
{

    dbc_message on_parse_message(std::string message_to_parse)
    {
        dbc_message result;
        std::stringstream message_stream(message_to_parse);
        message_stream >> result.id;
        message_stream >> result.name;
        message_stream >> result.length;
        message_stream >> result.sender;

        // Quickly trim off the colon at the end of the name...
        result.name.erase(result.name.end()-1);
        return result;
    }
}
