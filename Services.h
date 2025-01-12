#pragma once

using namespace std;
#include <string>
#include "Repository.h"
#include "RepositoryWL.h"
#include "Movie.h"

class Services {
private:
	Repository* repo;
	RepositoryWL* repoWL;

public:
	//constructor
	Services();

	//explicit constructor
	Services(Repository* repo, RepositoryWL* repoWL);

	//add movie to database (repository)
	bool addMovie(const string&, const string&, int, int, const string&);

	//remove movie from database
	bool removeMovie(const string& title);

	//update movie in database
	bool updateMovie(Movie movie, Movie newMovie);

	//returns all movies from repo
	vector<Movie> get_movies();

	//returns movies from repo with a given genre, if empty, returns all
	vector<Movie> get_moviesByGenre(const string& genre);

	//get a movie from repository
	Movie get_movie(int index);

	//add movie to watch list
	bool addToWL(Movie movie);

	//delete movie from watch list
	bool deleteFromWL(string title);

	//returns index of a movie in watch list
	int search_movie(string title);

	//increases movie's likes number by 1
	void incLikesWL(string title);

	//returns size of watch list
	int getWatchListsize();

	//returns the watch list
	vector<Movie> get_watchList();

	//reads movies from file and adds them to repo
	void read_from_file(string file_name);

	//writes movies from repo to file
	void write_to_file(string file_name);
	void write_to_fileWLTEMPORAR(string file_name);

	//reads movies from watch list file and adds them to repoWL
	void read_from_fileWL();

	//writes movies from watch list repo to fileWL
	void write_to_fileWL();

	void setRepoWL(RepositoryWL* _repoWL);

	const RepositoryWL* getRepoWL() const;

	//for qt
	void printWatchlist();


	//desturctor
	~Services();

};
