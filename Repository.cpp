#include "Repository.h"
#include <sstream>
#include <string>
#include <QDebug>
#include <QString>

using namespace std;

Repository::Repository() {
	this->_movies;
}

bool Repository::addMovieRepo(Movie movie) {
	this->_movies.push_back(movie);
	return true;
}

bool Repository::updateMovieRepo(Movie movie, Movie new_movie) {
	int index = this->search_movie(movie.get_title());
	if (index == -1) {
		return false;
	}
	else {
		this->_movies.at(index) = new_movie;
		return true;
	}
}

bool Repository::removeMovieRepo(string title) {
	int index = this->search_movie(title);
	if (index == -1) {
		return false;
	}
	else {
		this->_movies.erase(this->_movies.begin() + index);
		return true;
	}
	return false;

}

vector<Movie> Repository::getMoviesRepo() {
	return this->_movies;
}


int Repository::search_movie(string title) {
	for (int i = 0; i < this->_movies.size(); i++) {
		if (this->_movies.at(i).get_title() == title) {
			qDebug() << "Movie found at index:" << i;
			return i;
		}
	}
	qDebug() << "Movie not found:" << QString::fromStdString(title);
	return -1;
}

Movie Repository::getMovie(int index) {
	if (index < 0 || index >= this->_movies.size()) {
		qDebug() << "Invalid index for movie retrieval:" << index;
		return Movie(); // Return an empty movie or handle error appropriately
	}
	qDebug() << "Retrieving movie at index:" << index;
	return this->_movies.at(index);
}

void Repository::incLikesRepo(string title)
{
	int index = search_movie(title);
	this->_movies.at(index).set_likes(this->_movies.at(index).get_likes() + 1);
}


void Repository::read_from_file(string file_name) {
	this->_movies.clear();
	ifstream file(file_name);
	if (!file.is_open()) {
		throw runtime_error("The file could not be opened!");
	}
	Movie movie;
	string line;
	while (getline(file, line)) {
		vector<string> tokens;
		stringstream stream(line);
		string token;
		while (getline(stream, token, ',')) {
			tokens.push_back(token);
			if (tokens.size() < 5) {
				continue;
			}
			break;
		}
		movie.set_title(tokens[0]);
		movie.set_genre(tokens[1]);
		movie.set_year(stoi(tokens[2]));
		movie.set_likes(stoi(tokens[3]));
		movie.set_trailerLink(tokens[4]);
		this->addMovieRepo(movie);
	}
	file.close();
}



void Repository::write_to_file(string file_name) {
	ofstream file(file_name, std::ios::trunc);
	if (!file.is_open()) {
		throw runtime_error("The file could not be opened!");
	}
	for (auto& movie : this->_movies) {
		file << movie.get_title() << "," << movie.get_genre() << "," << movie.get_year() << "," << movie.get_likes()
			<< "," << movie.get_trailerLink() << "\n";
	}
	file.close();
}


Repository::~Repository() = default;


