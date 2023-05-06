# CMakeList.txt : CMake project for movie_linker, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package(Boost COMPONENTS regex filesystem)

include_directories(${Boost_INCLUDE_DIRS})

# Add source to this project's executable.
add_executable (movie_linker "movie_linker.cpp" "movie_linker.h")

target_link_libraries(movie_linker ${Boost_LIBRARY_DIRS} Boost::regex Boost::filesystem)
