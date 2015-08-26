/*************************************************************************
 * Copyright (c) 2015, Dave Brown
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR *CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL *DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 ************************************************************************/
#ifndef __dbc_parser_h__
#define __dbc_parser_h__

#include <cantools/parsers/types.h>
#include <sstream>

namespace dbc
{
    struct dbc_file
    {
        std::vector< dbc_message > messages;
    };

    dbc_file parse_dbc(std::stringstream && stream);
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
