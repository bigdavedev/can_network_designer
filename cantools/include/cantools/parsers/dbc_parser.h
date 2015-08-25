#ifndef __dbc_parser_h__
#define __dbc_parser_h__

#include <cantools/parsers/types.h>

namespace dbc
{
    struct dbc_file
    {
        std::vector< dbc_message > messages;
    };

    dbc_message on_parse_message(std::string message_to_parse);
}

#endif
