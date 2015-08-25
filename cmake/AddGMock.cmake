##========================================================================
## Copyright (c) 2015, Dave Brown
## All rights reserved.
##
## Redistribution and use in source and binary forms, with or without
## modification, are permitted provided that the following conditions are met:
##
## 1. Redistributions of source code must retain the above copyright notice, this
##    list of conditions and the following disclaimer.
##
## 2. Redistributions in binary form must reproduce the above copyright notice,
##    this list of conditions and the following disclaimer in the documentation
##    and/or other materials provided with the distribution.
##
## 3. Neither the name of the copyright holder nor the names of its contributors
##    may be used to endorse or promote products derived from this software
##    without specific prior written permission.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
## AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
## IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
## ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR *CONTRIBUTORS BE
## LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
## CONSEQUENTIAL *DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
## SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
## INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
## CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
## ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
## THE POSSIBILITY OF SUCH DAMAGE.
##========================================================================

include ( ExternalProject )

## Add googlemock framework to project
##====================================
##
function ( add_gmock DESTINATION )
    find_package ( Threads REQUIRED )

    ExternalProject_Add ( gmock
                          GIT_REPOSITORY https://github.com/bigdavedev/googlemock.git
                          PREFIX ${DESTINATION}/gmock
                          # Disable install step
                          INSTALL_COMMAND "" )

    # Set gmock properties
    ExternalProject_Get_Property ( gmock source_dir binary_dir )

    # Create a libgmock target to be used as a dependency by test programs
    add_library ( libgmock IMPORTED STATIC GLOBAL )
    add_dependencies ( libgmock gmock )
    set_target_properties ( libgmock PROPERTIES
                            "IMPORTED_LOCATION" "${binary_dir}/libgmock.a"
                            "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}" )

    # Create a libgmock_main target to be used as a dependency by test programs
    add_library ( libgmock_main IMPORTED STATIC GLOBAL )
    add_dependencies ( libgmock_main gmock_main )
    set_target_properties ( libgmock_main PROPERTIES
                            "IMPORTED_LOCATION" "${binary_dir}/libgmock_main.a"
                            "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}" )
    include_directories ( "${source_dir}/include" )
endfunction ()
