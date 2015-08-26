cmake_minimum_required ( VERSION 2.8 )

##---------------------------------------------------------------------------##
# General Configuration
# =====================
##---------------------------------------------------------------------------##
list ( APPEND CMAKE_CXX_FLAGS "-std=c++1y" )
enable_testing()
add_subdirectory ( cantools )
add_subdirectory ( tests )
