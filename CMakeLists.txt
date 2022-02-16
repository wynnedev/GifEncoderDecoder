cmake_minimum_required(VERSION 3.21)
project(GifEncoderDecoder)

set(CMAKE_CXX_STANDARD 14)
set(SOURCES lib/gif_font.c
        lib/gifalloc.c
        lib/gif_hash.h
        lib/egif_lib.c
        lib/gif_lib_private.h
        lib/gif_lib.h
        lib/gif_err.c
        lib/dgif_lib.c
        lib/gif_hash.c
        lib/quantize.c lib/giflib_to_opencv.h GifDecoder.cpp GifDecoder.h)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} lib .)

add_executable(GifEncoderDecoder main.cpp ${SOURCES})
target_link_libraries( GifEncoderDecoder ${OpenCV_LIBS} )