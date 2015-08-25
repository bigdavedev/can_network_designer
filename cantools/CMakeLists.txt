project ( cantools )

##---------------------------------------------------------------------------##
# library dependencies
# ====================
# We use the following libraries:
# * sqlite3
##---------------------------------------------------------------------------##
set ( LIBRARIES sqlite3 )

include_directories ( include )

set ( SOURCES source/dbc_parser.cpp )

add_library ( ${PROJECT_NAME} ${SOURCES} )
target_link_libraries ( ${PROJECT_NAME} ${LIBRARIES} )
