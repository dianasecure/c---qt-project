#pragma once
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
#include "Movie.h"

class Repository {
private:
	vector<Movie> _movies;

public:
	//constructor
	Repository();

	bool addMovieRepo(Movie movie);
	bool removeMovieRepo(string title);
	bool updateMovieRepo(Movie, Movie);
	vector<Movie> getMoviesRepo();
	int search_movie(string title);
	Movie getMovie(int index);

	//increases movie's likes number by 1
	void incLikesRepo(string title);


	void read_from_file(string);
	void write_to_file(string);


	//desturctor
	~Repository();


};
