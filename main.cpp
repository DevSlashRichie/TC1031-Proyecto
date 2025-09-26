/*
*  autor: Ricardo Rodríguez Medina
*  fecha: September 2025
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // for tempporal sort

struct Movie {
    std::string title;
    int rating;
    bool watched;
};

class MovieLibrary {
private:
    std::vector<Movie> movies;

public:
    void addMovie(const std::string& title, int rating) {
        Movie m {title, rating, true};
        movies.push_back(m);
        std::cout << "Movie added: " << title << " with rating " << rating << "\n";
    }

    void showMovies() {
        if (movies.empty()) {
            std::cout << "No movies in library.\n";
            return;
        }

        // sort movies by rating (high → low) - TODO: implement this algorithm manually.
        std::sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
            return a.rating > b.rating;
        });

        std::cout << "\n--- Movie Library (Top Rated First) ---\n";
        for (const auto& m : movies) {
            std::cout << "Title: " << m.title
                      << " | Rating: " << m.rating
                      << " | Watched: " << (m.watched ? "Yes" : "No")
                      << "\n";
        }
        std::cout << "--------------------------------------\n";
    }
};

int main() {
    MovieLibrary library;
    int choice;

    do {
        std::cout << "\nMovie Library Menu:\n";
        std::cout << "1. Add movie\n";
        std::cout << "2. Show all movies (sorted by rating)\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;
        std::cin.ignore(); // clear buffer

        if (choice == 1) {
            std::string title;
            int rating;
            std::cout << "Enter movie title: ";
            std::getline(std::cin, title);
            std::cout << "Enter rating (1-10): ";
            std::cin >> rating;
            library.addMovie(title, rating);
        } else if (choice == 2) {
            library.showMovies();
        }
    } while (choice != 0);

    std::cout << "Goodbye!\n";
    return 0;
}

