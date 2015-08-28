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

#include <cantools/devices/can_socket.hpp>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>
#include <string.h>
#include <unistd.h>

 #include <iostream>

namespace devices
{

    can_socket::can_socket()
    {
    }

    can_socket::~can_socket()
    {
        std::cout << "Closing CAN socket\n";
        close_socket();
    }

    int can_socket::read_frame(can::frame & frame)
    {
        can_frame tmp;
        int bytes_read = read(socket_handle, (void*)&tmp, sizeof(can_frame));

        frame.id = tmp.can_id;
        frame.dlc = tmp.can_dlc;
        memcpy(frame.data, tmp.data, tmp.can_dlc);

        return bytes_read;
    }

    int can_socket::write_frame(can::frame & frame)
    {
        can_frame tmp = {
            .can_id = frame.id,
            .can_dlc = frame.dlc
        };

        memcpy(tmp.data, frame.data, frame.dlc);

        int bytes_sent = write(socket_handle, (void const*)&tmp, sizeof(can_frame));
        return bytes_sent;
    }

    void can_socket::init(const char* if_name, int protocol)
    {
        socket_handle = socket(PF_CAN, SOCK_RAW, protocol);

        ifreq ifr;
        strncpy(ifr.ifr_name, if_name, IF_NAMESIZE);

        ioctl(socket_handle, SIOCGIFINDEX, &ifr);

        sockaddr_can const addr = {
            .can_family = AF_CAN,
            .can_ifindex = ifr.ifr_ifindex
        };

        bind(socket_handle, (sockaddr *)&addr, sizeof(addr));
    }
    void can_socket::close_socket() const
    {
        std::cout << "Closing CAN socket\n";
        close(socket_handle);
    }
}
