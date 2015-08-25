#ifndef __dbc_typed_h__
#define __dbc_typed_h__

#include <vector>
#include <string>

typedef enum
{
    CAN_LITTLE_ENDIAN,
    CAN_BIG_ENDIAN
} Endianness;

typedef enum
{
    SIGNED,
    UNSIGNED
} Signedness;

struct dbc_signal
{
    std::string name;
    unsigned char start_bit;
    unsigned char end_bit;
    unsigned char bit_length;
    Endianness endian;
    Signedness signedness;
    double scale;
    double offset;
    double min;
    double max;
    char* unit;
};

typedef std::vector< dbc_signal > dbc_signal_list_type;

struct dbc_message
{
    unsigned int id;
    std::string name;
    unsigned int length;
    std::string sender;
    dbc_signal_list_type signals;
};

#endif
