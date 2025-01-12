#include "Services.h"
#include <qlayout.h>
#include <qlabel.h>
#include <qwidget.h>
#include <qmainwindow.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>

using namespace std;

Services::Services() = default;

Services::Services(Repository* repo, RepositoryWL* repoWL) {
	this->repo = repo;
	this->repoWL = repoWL;
}

bool Services::addMovie(const string& title, const string& genre, int year, int likes, const string& trailerLink) {
	Movie movie = Movie(title, genre, year, likes, trailerLink);
	return this->repo->addMovieRepo(movie);
}

bool Services::removeMovie(const string& title)
{
	return this->repo->removeMovieRepo(title);
}

bool Services::updateMovie(Movie movie, Movie newMovie)
{
	return this->repo->updateMovieRepo(movie, newMovie);
}

vector<Movie> Services::get_movies()
{
	return this->repo->getMoviesRepo();
}

vector<Movie> Services::get_moviesByGenre(const string& genre)
{
	vector<Movie> movies;
	for (auto& movie : this->repo->getMoviesRepo()) {
		if (movie.get_genre() == genre) {
			movies.push_back(movie);
		}
	}
	if (genre == "")
		return this->repo->getMoviesRepo();
	return movies;
}

Movie Services::get_movie(int index)
{
	return this->repo->getMovie(index);
}

int Services::getWatchListsize()
{
	return 0;
}

vector<Movie> Services::get_watchList()
{
	return this->repoWL->get_watchList();
}

bool Services::addToWL(Movie movie)
{
	return this->repoWL->addToWL(movie);
}

bool Services::deleteFromWL(string title) {

	return this->repoWL->deleteFromWL(title);
}

int Services::search_movie(string title) {

	return this->repo->search_movie(title);
}

void Services::incLikesWL(string title)
{
	this->repo->incLikesRepo(title);
}

void Services::read_from_file(string file_name)
{
	this->repo->read_from_file(file_name);
}

void Services::write_to_file(string file_name)
{
	this->repo->write_to_file(file_name);
}

void Services::read_from_fileWL()
{
	this->repoWL->read_from_file();
}

void Services::write_to_fileWL()
{
	this->repoWL->write();
}

void Services::write_to_fileWLTEMPORAR(string file_name)
{
	this->repoWL->write_to_file(file_name);
}


void Services::setRepoWL(RepositoryWL* _repoWL) {
	this->repoWL = move(_repoWL);
}

const RepositoryWL* Services::getRepoWL() const {
	return repoWL;
}

void Services::printWatchlist() {
	for (const auto& movie : this->repoWL->get_watchList()) {
		qDebug() << "Movie in watchlist: " << QString::fromStdString(movie.get_title());
	}
}

Services::~Services()
{
	delete this->repo;
}


