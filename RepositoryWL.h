#pragma once
#include <vector>
#include "Movie.h"
#include "Repository.h"

class RepositoryWL {
protected:
	vector<Movie> watchList;
public:

	//constructor
	RepositoryWL();

	//returns the watch list
	vector<Movie> get_watchList();

	//add movie to watch list
	bool addToWL(Movie movie);

	//delete movie from watch list
	bool deleteFromWL(string title);

	//returns index of a movie in watch list
	int search_movie(string title);

	void read_from_file();

	void write_to_file(string file_name);

	virtual void write() {}

	virtual void display() {}
};

class RepositoryWLCsv : public RepositoryWL {

	void write() override;

	void display() override;

};

class RepositoryWLHtml : public RepositoryWL {

	void write() override;

	void display() override;

};
