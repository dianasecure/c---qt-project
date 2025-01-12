#include "RepositoryWL.h"
#include <sstream>
#include <string>
#include <QDebug>
#include <QString>


RepositoryWL::RepositoryWL() {
	this->watchList;
}

vector<Movie> RepositoryWL::get_watchList()
{
	return this->watchList;
}

bool RepositoryWL::addToWL(Movie movie) {
	qDebug() << "Adding movie to watchlist:" << QString::fromStdString(movie.get_title());
	this->watchList.push_back(movie);
	return true;
}

bool RepositoryWL::deleteFromWL(string title) {

	int index = this->search_movie(title);
	if (index == -1) {
		return false;
	}
	else {
		this->watchList.erase(this->watchList.begin() + index);
		return true;
	}
	return false;
}

int RepositoryWL::search_movie(string title) {
	for (int i = 0; i < this->watchList.size(); i++) {
		if (this->watchList.at(i).get_title() == title)
			return i;
	}
	return -1;
}


void RepositoryWL::read_from_file() {
	ifstream file("watchList.csv");
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
		this->addToWL(movie);
	}
	file.close();
}

void RepositoryWLCsv::write() {
	remove("watchList.csv");
	ofstream fout("watchList.csv", ios::app);

	for (auto movie : this->watchList) {
		fout << movie.get_title() << "," << movie.get_genre() << "," << movie.get_year() << "," << movie.get_likes() << "," << movie.get_trailerLink() << "\n";
	}
	fout.close();
}

void RepositoryWLCsv::display() {
	system("start watchList.csv");
}

void RepositoryWLHtml::write() {
	//remove("watchList.html");
	ofstream fout("watchList.html", ios::trunc);
	if (!fout.is_open()) {
		throw runtime_error("The file could not be opened!");
	}
	fout << "<!DOCTYPE html>" << endl;
	fout << "<html>" << endl;
	fout << "<head>" << endl;
	fout << "    <title>Watch List</title>" << endl;
	fout << "</head>" << endl;
	fout << "<body>" << endl;
	fout << "<table border=\"1\">" << endl;

	for (auto i : this->watchList) {
		fout << "    <tr>" << endl;
		fout << "        <td>" + i.get_title() + "</td>" << endl;
		fout << "        <td>" + i.get_genre() + "</td>" << endl;
		fout << "        <td>" << i.get_year() << "</td>" << endl;
		fout << "        <td>" << i.get_likes() << "</td>" << endl;
		fout << "        <td><a href=\"" + i.get_trailerLink() + "\">Link</a></td>" << endl;
		fout << "    </tr>" << endl;
	}

	fout << "</table>" << endl;
	fout << "</body>" << endl;
	fout << "</html>" << endl;
	fout.close();
}

void RepositoryWLHtml::display() {
	system("start watchList.html");
}


void RepositoryWL::write_to_file(string file_name) {

	qDebug() << "Adding...";
	ofstream file(file_name, ios::trunc);
	if (!file.is_open()) {
		throw runtime_error("The file could not be opened!");
	}
	for (auto movie : this->watchList) {
		file << movie.get_title() << "," << movie.get_genre() << "," << movie.get_year() << "," << movie.get_likes()
			<< "," << movie.get_trailerLink() << "\n";
		qDebug() << "Added to watchlist.txt!";
	}
	file.close();
}
