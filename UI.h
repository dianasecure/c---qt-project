#pragma once

using namespace std;
#include "Services.h"
#include "Repository.h"
#include "RepositoryWL.h"
#include "Movie.h"
#include <vector>

class UI {

private:
	//Validator validator;
	Services* services;
public:
	//constructor
	UI(Services* _services);

	void run();
	void runAU();
	// for reading string with spaces
	string readString();

	static void printMenuAdministrator();
	static void printMenuUser();
	void runAdministrator();
	void runUser();


	//for admin
	void addMovieUi();
	void removeMovieUi();
	void listMoviesUi();
	void updateMovieUi();

	//for user
	void startOperationUI();
	void deleteFromWatchlistUI();
	void seeWatchlistUI();
	void incLikesUI(const string& title);
	void openHtmlwatchlistUI();
	void openCsvwatchlistUI();

	//destructor
	~UI();
};

