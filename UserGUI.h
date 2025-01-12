#pragma once
#include <qwidget.h>
#include <qmainwindow.h>
#include "Services.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class USERGUI : public QWidget {

private:
	Services* services;
	QListWidget* moviesWidget;

	QPushButton* showByGenre;
	QPushButton* deleteMovie;
	QPushButton* back;
	QPushButton* addMovie;
	QPushButton* next;
	QPushButton* html;
	QPushButton* csv;
	QPushButton* txt;
	QPushButton* like;
	QPushButton* setRepoHtml;
	QPushButton* setRepoCsv;

	QLineEdit* genreLine;
	QLineEdit* deleteLine;
	QLineEdit* addLine;

	QString genre;

	int index_movie;


public:
	USERGUI(Services* services);
	~USERGUI();

private:
	void buildUSERGUI();

	void FshowByGenre();
	void FaddMovie();
	void Fnext();
	void FdeleteMovie();
	void FshowWatchListHTML();
	void FshowWatchListCSV();
	void FshowWatchListTXT();
	void FsetRepoHtml();
	void FsetRepoCsv();
	void FLike();

	auto getByGenre(QString genre);
	auto getMovieByIndex(int);
	int get_size(QString genre);

};