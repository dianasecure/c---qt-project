#include "USERGUI.h"
#include <qlayout.h>
#include <qlabel.h>
#include <cstdlib> // For system()

USERGUI::USERGUI(Services* services) : services{ services } {
	this->services->read_from_file("movies.txt");
	this->buildUSERGUI();
	this->index_movie = 0;

	qDebug() << "Constructor";

	QObject::connect(this->setRepoHtml, &QPushButton::clicked, this, &USERGUI::FsetRepoHtml);
	QObject::connect(this->setRepoCsv, &QPushButton::clicked, this, &USERGUI::FsetRepoCsv);
	QObject::connect(this->addMovie, &QPushButton::clicked, this, &USERGUI::FaddMovie);
	QObject::connect(this->next, &QPushButton::clicked, this, &USERGUI::Fnext);
	QObject::connect(this->deleteMovie, &QPushButton::clicked, this, &USERGUI::FdeleteMovie);
	QObject::connect(this->showByGenre, &QPushButton::clicked, this, &USERGUI::FshowByGenre);
	QObject::connect(this->html, &QPushButton::clicked, this, &USERGUI::FshowWatchListHTML);
	QObject::connect(this->csv, &QPushButton::clicked, this, &USERGUI::FshowWatchListCSV);
	QObject::connect(this->txt, &QPushButton::clicked, this, &USERGUI::FshowWatchListTXT);
	QObject::connect(this->like, &QPushButton::clicked, this, &USERGUI::FLike);

}

USERGUI::~USERGUI() {

}

void USERGUI::buildUSERGUI() {

	QHBoxLayout* mainLayout = new QHBoxLayout{ this };

	// movies
	this->moviesWidget = new QListWidget{};
	mainLayout->addWidget(moviesWidget);

	QGridLayout* rightLayout = new QGridLayout{};
	this->showByGenre = new QPushButton{ "Show movies by genre" };
	this->addMovie = new QPushButton{ "Add" };
	this->next = new QPushButton{ "Next" };
	this->html = new QPushButton{ "Show watchlist in Html" };
	this->csv = new QPushButton{ "Show watchlist in Csv" };
	this->txt = new QPushButton{ "Show watchlist in TXT" };
	this->deleteMovie = new QPushButton{ "Delete movie" };
	this->like = new QPushButton{ "Like deleted movie" };
	this->back = new QPushButton{ "Back" };

	QLabel* repoLabel = new QLabel{ "Please select repo first" };
	this->setRepoHtml = new QPushButton{ "HTML" };
	this->setRepoCsv = new QPushButton{ "CSV" };

	QLabel* genreLabel = new QLabel{ "Genre" };
	this->genreLine = new QLineEdit{};
	this->deleteLine = new QLineEdit{};

	rightLayout->addWidget(repoLabel, 0, 0);
	rightLayout->addWidget(setRepoHtml, 1, 0);
	rightLayout->addWidget(setRepoCsv, 1, 1);
	rightLayout->addWidget(genreLine, 2, 1);
	rightLayout->addWidget(showByGenre, 2, 0);
	rightLayout->addWidget(addMovie, 3, 0);
	rightLayout->addWidget(next, 3, 1);
	rightLayout->addWidget(deleteMovie, 4, 0);
	rightLayout->addWidget(deleteLine, 4, 1);
	rightLayout->addWidget(like, 5, 0);
	rightLayout->addWidget(html, 6, 0);
	rightLayout->addWidget(csv, 6, 1);
	//rightLayout->addWidget(txt, 5, 2);
	rightLayout->addWidget(back, 7, 3);

	mainLayout->addLayout(rightLayout);

	QWidget* mainWindow = new QWidget{ this };
	mainWindow->resize(500, 250);
	mainWindow->setLayout(mainLayout);

}

auto USERGUI::getByGenre(QString genre) {
	return this->services->get_moviesByGenre(genre.toStdString());
}

auto USERGUI::getMovieByIndex(int index) {
	int i = 0;
	for (auto m : this->services->get_moviesByGenre(this->genre.toStdString())) {
		if (i == index)
			return m;
		i++;
	}
		
}

void USERGUI::FshowByGenre() {

	this->moviesWidget->clear();
	this->genre = this->genreLine->text();

	this->index_movie = 0;

	for (auto m : this->services->get_moviesByGenre(genre.toStdString())) {
		this->moviesWidget->addItem(QString::fromStdString(m.get_title()));
		string s = m.get_genre() + "," + to_string(m.get_year()) + "," + to_string(m.get_likes()) + "," + m.get_trailerLink();
		this->moviesWidget->addItem(QString::fromStdString(s));
		// opening trailer
		auto _link = m.get_trailerLink();
		const char* _command = "start";
		system((string(_command) + " " + _link).c_str());
		break;
	}

}

int USERGUI::get_size(QString genre) {
	int size = 0;
	for (auto m : this->services->get_moviesByGenre(genre.toStdString())) {
		size++;
	}
	return size;
}
 
void USERGUI::Fnext() {
	this->moviesWidget->clear();
	this->index_movie++;

	if (this->index_movie == this->get_size(this->genre)) {
		this->index_movie = 0;
	}

	auto m = getMovieByIndex(this->index_movie);

	this->moviesWidget->addItem(QString::fromStdString(m.get_title()));
	string s = m.get_genre() + "," + to_string(m.get_year()) + "," + to_string(m.get_likes()) + "," + m.get_trailerLink();
	this->moviesWidget->addItem(QString::fromStdString(s));
	// opening trailer
	auto _link = m.get_trailerLink();
	const char* _command = "start";
	system((string(_command) + " " + _link).c_str());


}

void USERGUI::FaddMovie() {

	qDebug() << "Add Movie button clicked";
	QList<QListWidgetItem*> selectedItems = this->moviesWidget->selectedItems();
	if (selectedItems.isEmpty()) {
		qDebug() << "No movie selected to add.";
		return;
	}

	for (auto& item : selectedItems) {
		QString title = item->text();
		qDebug() << "Selected movie title:" << title;

		int index = this->services->search_movie(title.toStdString());
		if (index == -1) {
			qDebug() << "Movie not found in repository.";
			continue;
		}

		auto m = this->services->get_movie(index);
		qDebug() << "Movie found:" << QString::fromStdString(m.get_title());

		bool added = this->services->addToWL(m);
		if (added) {
			qDebug() << "Movie added to watchlist:" << QString::fromStdString(m.get_title());
		}
		else {
			qDebug() << "Failed to add movie to watchlist.";
		}
	}
	
}

void USERGUI::FdeleteMovie() {

	QString title = deleteLine->text();
	this->services->deleteFromWL(title.toStdString());
	
}


void USERGUI::FshowWatchListHTML() {

	this->services->write_to_fileWL();
	const char* command = "start";
	const char* link = "watchList.html";
	system((string(command) + " " + link).c_str());
}

void USERGUI::FshowWatchListCSV() {

	this->services->write_to_fileWL();
	const char* command = "start";
	const char* link = "watchList.csv";
	system((string(command) + " " + link).c_str());
}

void USERGUI::FshowWatchListTXT() {

	this->services->write_to_fileWLTEMPORAR("watchList.txt");
	const char* command = "start";
	const char* link = "watchList.txt";
	system((string(command) + " " + link).c_str());
}

void USERGUI::FsetRepoHtml()
{   
	//set repo html
	RepositoryWL* repoHtml = new RepositoryWLHtml();
	this->services->setRepoWL(repoHtml);

}

void USERGUI::FsetRepoCsv() {

	// set repo csv
	RepositoryWL* repoCsv = new RepositoryWLCsv();
	this->services->setRepoWL(repoCsv);
}

void USERGUI::FLike()
{
	QString title = deleteLine->text();
	this->services->incLikesWL(title.toStdString());

}
