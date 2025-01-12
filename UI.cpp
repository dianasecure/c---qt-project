#include <iostream>
#include <limits>
#include <fstream>
#include <cstdlib> // For system()
#include "UI.h"
#include "Exceptions.h"

using namespace std;

UI::UI(Services* _services) : services{ _services } {}

string UI::readString() {
    string input;
    getline(cin, input);
    return input;
}

void UI::run() {
    this->services->read_from_file("movies.txt");
    RepositoryWL* repoCsv = new RepositoryWLCsv();
    RepositoryWL* repoHtml = new RepositoryWLHtml();
    while (true) {
        cout << "Choose a mode(html/csv/0): ";
        string mode;
        mode = readString();
        if (mode == "csv") {
            this->services->setRepoWL(repoCsv);
            this->runAU();
            continue;
        }
        else if (mode == "html") {
            this->services->setRepoWL(repoHtml);
            this->runAU();
            continue;
        }
        else if (mode == "0") {
            break;
        }
        cout << "Wrong mode!\n";
    }

}

void UI::runAU() {
    while (true) {
        cout << "Choose a mode(admin/user/0): ";
        string mode;
        mode = readString();
        if (mode == "admin") {
            this->runAdministrator();
            continue;
        }
        else
            if (mode == "user") {
                this->runUser();
                continue;
            }
            else
                if (mode == "0")
                    break;
                else
                    cout << "Wrong mode!\n";
    }
}

void UI::printMenuAdministrator() {
    string menu =
        " 1. Add a new movie\n"
        " 2. Delete a movie\n"
        " 3. Update a movie\n"
        " 4. See all movies\n"
        " 0. Exit\n";

    cout << menu;

}

void UI::runAdministrator() {
    bool ok = true;
    while (ok) {
        this->printMenuAdministrator();
        cout << ">>> ";
        string option;
        option = readString();
        if (option == "0") {
            ok = false;
            continue;
        }
        if (option == "1") {
            this->addMovieUi();
            continue;
        }
        if (option == "2") {
            this->removeMovieUi();
            continue;
        }
        if (option == "3") {
            this->updateMovieUi();
            continue;
        }
        if (option == "4") {
            this->listMoviesUi();
            continue;
        }
        cout << "\nWrong command!\n";
    }
}

void UI::addMovieUi() {
    string title, genre, trailerLink;
    int year, likes;
    cout << "Title: ";
    title = readString();

    cout << "Genre: ";
    genre = readString();

    cout << "Year: ";
    cin >> year;

    cout << "Likes: ";
    cin >> likes;

    cout << "TrailerLink: ";
    cin >> trailerLink;

    if (this->services->addMovie(title, genre, year, likes, trailerLink)) {
        this->services->write_to_file("movies.txt");
    }

}

void UI::removeMovieUi() {
    string title;
    cout << "Name of the existing movie: ";
    title = readString();

    try {
        this->services->removeMovie(title);
        cout << "Movie removed! \n";
    }
    catch (Exceptions& serviceAdminException) {
        cout << serviceAdminException.get_msg();
    }
}

void UI::listMoviesUi() {
    auto movies = this->services->get_movies();
    for (int i = 0; i < movies.size(); i++) {
        cout << movies.at(i);
    }

}

void UI::updateMovieUi() {
    string title, genre, trailerLink;
    int year, likes;
    cout << "Name of the existing movie: ";
    title = readString();

    cout << "New genre: ";
    cin >> genre;

    cout << "New year: ";
    while (!(cin >> year)) {
        cout << "Invalid numerical value (year)!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "New year: ";
    }

    cout << "New likes: ";
    while (!(cin >> likes)) {
        cout << "Invalid numerical value (likes)!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "New likes: ";
    }

    cout << "Trailer link: "; cin >> trailerLink;


    try {
        this->services->updateMovie(Movie(title, genre, year, likes, trailerLink), Movie(title, genre, year, likes, trailerLink));
        cout << "Movie updated!\n";
    }
    catch (Exceptions& serviceAdminException) {
        cout << serviceAdminException.get_msg();
    }
}

//FOR USER MODE
void UI::printMenuUser() {
    string menu =
        " 1. See movies by genre\n"
        " 2. Delete a movie from watch list\n"
        " 3. See watch list\n"
        " 4. Open html watch list\n"
        " 5. Open csv watch list\n"
        " 0. Exit\n";

    cout << menu;

}

void UI::runUser() {
    int _ok = 1;
    while (_ok) {
        this->printMenuUser();
        cout << ">>> ";
        string option;
        option = readString();
        if (option == "0") {
            _ok = false;
            continue;
        }
        if (option == "1") {
            this->startOperationUI();
            continue;
        }
        if (option == "2") {
            this->deleteFromWatchlistUI();
            continue;
        }
        if (option == "3") {
            this->seeWatchlistUI();
            continue;
        }
        if (option == "4") {
            this->openHtmlwatchlistUI();
            continue;
        }
        if (option == "5") {
            this->openCsvwatchlistUI();
            continue;
        }
        cout << "\nWrong command!\n";
    }
    this->services->write_to_fileWL();
}

void UI::startOperationUI() {
    string genre;
    cout << "Genre: ";
    genre = readString();

    while (true) {
        int _ok = 1;
        auto movies = this->services->get_moviesByGenre(genre);
        int numberOfMovies = movies.size();
        if (numberOfMovies == 0) {
            cout << "Movie with given genre does not exist! \n\n";
            break;
        }
        for (int i = 0; i < numberOfMovies; i++) {
            auto movie = movies.at(i);
            cout << movie;
            string _link = movie.get_trailerLink();
            // opening the link
            const char* _command = "start";
            system((string(_command) + " " + _link).c_str());

            while (true) {
                string _menu = "   Actions: \n"
                    "     add: Add movie to watch list\n"
                    "     next: Go to the next movie \n"
                    "     0: Go back to commands \n";
                cout << _menu;
                cout << "\n   Command: ";
                string command;
                command = readString();
                cout << "\n";
                if (command == "add") {
                    if (this->services->addToWL(movie)) {
                        this->services->write_to_file("watch list.txt");
                    }
                    cout << "\nNext movie: \n";
                    break;
                }
                else
                    if (command == "next") {
                        cout << "Next movie: \n";
                        break;
                    }
                    else
                        if (command == "0") {
                            _ok = 0;
                            break;
                        }
                        else
                            cout << "Wrong command! \n";
            }
            if (_ok == 0) {
                break;
            }
        }
        if (_ok == 0) {
            break;
        }
    }

}

void UI::deleteFromWatchlistUI() {
    string title;
    cout << "Name of the existing movie: ";
    title = readString();

    try {
        this->services->deleteFromWL(title);
        cout << "Movie deleted!\n";
        cout << "Did you like the movie? Rate it(like or no)\n";
        string action;
        while (true) {
            action = readString();

            if (action == "like") {
                incLikesUI(title);
                break;
            }
            else
                if (action == "no") {
                    break;
                }
                else
                    cout << "Wrong command! \n";
        }
    }
    catch (Exceptions& serviceUserException) {
        cout << serviceUserException.get_msg();
    }

}

void UI::incLikesUI(const string& title) {
    this->services->incLikesWL(title);
}

void UI::seeWatchlistUI() {
    cout << "\nWATCH LIST: \n";
    auto movies = this->services->get_watchList();
    int numberOfMovies = movies.size();
    for (int i = 0; i < numberOfMovies; i++) {
        cout << movies.at(i);
    }
}

void UI::openHtmlwatchlistUI() {
    const char* command = "start";
    const char* link = "watchList.html";
    system((string(command) + " " + link).c_str());
}

void UI::openCsvwatchlistUI() {
    const char* command = "start";
    const char* link = "watchList.csv";
    system((string(command) + " " + link).c_str());
}

UI::~UI() = default;
