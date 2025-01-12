#pragma once

#include <iostream>
#include <string>
using namespace std;

class Movie {
private:
	string _title;
	string _genre;
	int _year;
	int _likes;
	string _trailerLink;

public:
	//constructor:
	Movie();

	Movie(const string&, const string&, int, int, const string&);

	//operations:
	Movie& operator=(Movie);
	bool operator==(Movie&);

	friend ostream& operator<<(ostream&, Movie&);
	friend istream& operator>>(istream&, Movie&);

	//getters:
	string get_title() const { return _title; }
	string get_genre() const { return _genre; }
	int get_year() { return _year;}
	int get_likes() { return _likes; }
	string get_trailerLink() const { return _trailerLink; }


	//setters: (name, genre, year, trailer must not be modified)
	void set_title(string& title) { this->_title = title; }
	void set_genre(string& genre) { this->_genre = genre;}
	void set_year(int year) { this->_year = year; }
	void set_likes(int likes) { this->_likes = likes; }
	void set_trailerLink(string& trailerLink) { this->_trailerLink = trailerLink; }

	//converts the movie to string
	string toString();

	//destructor:
	~Movie();

};

