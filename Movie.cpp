#include "Movie.h"

using namespace std;
Movie::Movie() = default;

Movie::Movie(const string& title, const string& genre, int year, int likes, const string& trailerLink) {
	this->_title = title;
	this->_genre = genre;
	this->_year = year;
	this->_likes = likes;
	this->_trailerLink = trailerLink;
}

Movie& Movie::operator=(Movie other) {
	if (this != &other) {
		this->_title = other._title;
		this->_genre = other._genre;
		this->_year = other._year;
		this->_likes = other._likes;
		this->_trailerLink = other._trailerLink;
	}
	return *this;
}

bool Movie::operator==(Movie& other) {
	return this->_title == other._title;
}

ostream& operator<<(ostream& _cout, Movie& m) {
	_cout << "\n ~~~ MOVIE ~~~";
	_cout << "\n   Title: " << m._title;
	_cout << "\n   Genre: " << m._genre;
	_cout << "\n   Year: " << m._year;
	_cout << "\n   Likes: " << m._likes;
	_cout << "\n   Trailer link: " << m._trailerLink;
	_cout << "\n ~~~~~~~~~~~~~\n\n";
	return _cout;
}

istream& operator>>(istream& _cin, Movie& m) {
	cout << "Title: "; _cin >> m._title;
	cout << "Genre: "; _cin >> m._genre;
	cout << "Year: "; _cin >> m._year;
	cout << "Likes: "; _cin >> m._likes;
	cout << "Trailer Link: "; _cin >> m._trailerLink;
	return _cin;
}


string Movie::toString() {
	return this->_title + "\n" + this->_genre + "\n" + to_string(this->_year) + "\n" + to_string(this->_likes) + "\n" + this->_trailerLink + "\n";
}

Movie::~Movie() = default;

