#include "AdminGUI.h"
#include <qlayout.h>
#include <qlabel.h>

ADMINGUI::ADMINGUI(Services* services) : services{ services }
{
	qDebug() << "Constructor";

	this->services->read_from_file("movies.txt");
	this->buildADMINGUI();
	this->populateList();

	QObject::connect(this->addButton, &QPushButton::clicked, this, &ADMINGUI::addButtonHandler);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &ADMINGUI::deleteButtonHandler);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &ADMINGUI::updateButtonHandler);

}

ADMINGUI::~ADMINGUI() {
	this->services->write_to_file("movies.txt");  // Write the list to file when the program ends
}

void ADMINGUI::buildADMINGUI() {


	QHBoxLayout* mainLayout = new QHBoxLayout{ this };
	//movie list:
	this->moviesWidget = new QListWidget{};
	mainLayout->addWidget(moviesWidget);

	//commands:
	QGridLayout* rightLayout = new QGridLayout{};

	QLabel* titleLabel = new QLabel{ "Title" };
	this->titleEdit = new QLineEdit{};

	QLabel* genreLabel = new QLabel{ "Genre" };
	this->genreEdit = new QLineEdit{};

	QLabel* yearLabel = new QLabel{ "Year" };
	this->yearEdit = new QLineEdit{};

	QLabel* likesLabel = new QLabel{ "Likes" };
	this->likesEdit = new QLineEdit{};

	QLabel* linkLabel = new QLabel{ "Link" };
	this->linkEdit = new QLineEdit{};

	rightLayout->addWidget(titleLabel, 0, 0);
	rightLayout->addWidget(this->titleEdit, 0, 1);

	rightLayout->addWidget(genreLabel, 1, 0);
	rightLayout->addWidget(this->genreEdit, 1, 1);

	rightLayout->addWidget(yearLabel, 2, 0);
	rightLayout->addWidget(this->yearEdit, 2, 1);

	rightLayout->addWidget(likesLabel, 3, 0);
	rightLayout->addWidget(this->likesEdit, 3, 1);

	rightLayout->addWidget(linkLabel, 4, 0);
	rightLayout->addWidget(this->linkEdit, 4, 1);

	this->addButton = new QPushButton{ "Add" };
	this->deleteButton = new QPushButton{ "Delete" };
	this->updateButton = new QPushButton{ "Update" };

	rightLayout->addWidget(addButton, 5, 0);
	rightLayout->addWidget(deleteButton, 6, 0);
	rightLayout->addWidget(updateButton, 7, 0);

	mainLayout->addLayout(rightLayout);

	QWidget* mainWindow = new QWidget{ this };
	mainWindow->resize(500, 250);
	mainWindow->setLayout(mainLayout);

}

void ADMINGUI::populateList() {
	this->moviesWidget->clear();

	for (auto m : this->services->get_movies()) {
		this->moviesWidget->addItem(QString::fromStdString(m.get_title()));
	}
}

void ADMINGUI::addButtonHandler() {
	QString title = this->titleEdit->text();
	QString genre = this->genreEdit->text();
	QString year = this->yearEdit->text();
	QString likes = this->likesEdit->text();
	QString link = this->linkEdit->text();

	this->services->addMovie(title.toStdString(), genre.toStdString(), year.toInt(), likes.toInt(), link.toStdString());
	this->populateList();
}

void ADMINGUI::deleteButtonHandler() {

	QList<QListWidgetItem*> selectedItems = this->moviesWidget->selectedItems();
	for (auto& item : selectedItems) {
		QString title = item->text();
		this->services->removeMovie(title.toStdString());
	}
	this->populateList();

}

void ADMINGUI::updateButtonHandler() {
	QString new_title = this->titleEdit->text();
	QString new_genre = this->genreEdit->text();
	QString new_year = this->yearEdit->text();
	QString new_likes = this->likesEdit->text();
	QString new_link = this->linkEdit->text();
	Movie newMovie = Movie(new_title.toStdString(), new_genre.toStdString(), new_year.toInt(), new_likes.toInt(), new_link.toStdString());

	QList<QListWidgetItem*> selectedItems = this->moviesWidget->selectedItems();
	for (auto item : selectedItems) {
		QString title = item->text();
		QString genre = item->text();
		QString year = item->text();
		QString likes = item->text();
		QString link = item->text();
		Movie movie = Movie(title.toStdString(), genre.toStdString(), year.toInt(), likes.toInt(), link.toStdString());
		this->services->updateMovie(movie, newMovie);
	}

	this->populateList();
}

