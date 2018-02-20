cmake_minimum_required(VERSION 3.9)
project(TiffReader)

set(CMAKE_CXX_STANDARD 14)

find_package( Boost REQUIRED COMPONENTS filesystem system)

find_library(TIFF_LIB tiff /usr/local/lib)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(TiffReader main.cpp MyTagReader.h MyTagWriter.h TagStruct.cpp TagStruct.h CustomTiffTags.cpp CustomTiffTags.h TagViewData.cpp TagViewData.h)
target_link_libraries(TiffReader ${TIFF_LIB} m)