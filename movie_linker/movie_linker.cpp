#include "movie_linker.h"

const std::set<std::string> movie_linker::filetypes = {
    ".mov",
    ".mp4",
    ".mkv"
};

std::list<std::string> movie_linker::getMovieFilesInDirectory(boost::filesystem::path path) {
	boost::filesystem::directory_iterator endIttr;
	std::list<std::string> movieList;
	for (boost::filesystem::directory_iterator itt(path); itt != endIttr; ++itt) {
		if (boost::filesystem::is_directory(itt->status())) {
			std::list<std::string> subDirectoryList = getMovieFilesInDirectory(itt->path());
			for (std::string add : subDirectoryList) {
				movieList.push_back(add);
			};
		}
		else {
			for (auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(path), {})) {
                // Check if movie file
                std::string extension = entry.path().extension().string();
                if(movie_linker::filetypes.find(extension) != movie_linker::filetypes.end()){
				    movieList.push_back(entry.path().string());
                }
			};
		};
	};
	return movieList;
};

std::list<std::string> movie_linker::splitString(std::string str, std::string del) {
	std::list<std::string> words;
	int location = 0;
	std::size_t found = str.find(del, location);
	while (found != std::string::npos) {
		std::size_t findTo = str.find(del, found + 1);
		std::string word = str.substr(found, findTo);
		words.push_back(word);
	};
	return words;
}

bool movie_linker::checkIfExists(boost::filesystem::path path) {
	return boost::filesystem::exists(path);
};

int main(int argc, char** argv)
{
	std::cout << "Hello CMake." << std::endl;
	if (argc < 3) {
		std::cerr << "movie_linker: missing input file" << std::endl;
		std::cerr << "Usage: movie_linker <target_path> <link_path>" << std::endl;
		return 0;
	};
	std::string pathString = argv[1];
	std::string linkPathString = argv[2];

	if (!boost::filesystem::exists(pathString)) {
		std::cerr << "movie_linker: Path does not exist" << std::endl;
		return 0;
	};

	boost::filesystem::path relativePath(pathString);
    boost::filesystem::path path = boost::filesystem::absolute(relativePath);
	

	std::list<std::string> movies = movie_linker::getMovieFilesInDirectory(path);
	for (std::string movie : movies) {
		std::cout << std::endl;
		std::cout << "[*] Found movie file: " << movie << std::endl;
		std::cout << "[*] Checking if already linked..." << std::endl;

		boost::filesystem::path moviePath(movie);
		std::string filename = moviePath.filename().string();
		boost::filesystem::path relativeLinkPath(linkPathString);
        relativeLinkPath.append(filename);
        boost::filesystem::path linkPath = boost::filesystem::absolute(relativeLinkPath);

		if (movie_linker::checkIfExists(linkPath)) {
			std::cout << "[!] Already linked" << std::endl;
			continue;
		};

		std::cout << "[*] Not linked, creating link..." << std::endl;
		boost::filesystem::create_hard_link(moviePath, linkPath);
	};

	return 0;
};