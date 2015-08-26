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
    dbc_signal on_parse_signal(std::string signal_to_parse);

    namespace detail
    {
        std::pair< unsigned int, unsigned int > extract_bit_start_and_length_from_string(std::string signal);

        Endianness extract_endianness_from_string(std::string signal);

        Signedness extract_signedness_from_string(std::string signal);

        std::pair< double, double > extract_scale_and_offset_from_string(std::string signal);

        std::pair< double, double > extract_min_and_max_from_string(std::string signal);

        std::string extract_unit_from_string(std::string signal);
    }
}

#endif
