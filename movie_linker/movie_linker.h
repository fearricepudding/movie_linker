#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <set>

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

class movie_linker {
public:
    static std::list<std::string> getMovieFilesInDirectory(boost::filesystem::path);
    static bool checkIfExists(boost::filesystem::path);
    static std::list<std::string> splitString(std::string, std::string);
    static const std::set<std::string> filetypes; 
};

