/*
*  autor: Ricardo Rodríguez Medina
*  fecha: September 2025
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // for tempporal sort
#include <fstream>
#include <sstream>

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

    void saveToCSV(const std::string& filename) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Could not open file for writing: " << filename << "\n";
            return;
        }

        for (const auto& m : movies) {
            outFile << m.title << "," << m.rating << "," << m.watched << "\n";
        }

        outFile.close();
        std::cout << "Library saved to " << filename << "\n";
    }

    void loadFromCSV(const std::string& filename) {
        std::ifstream inFile(filename);
        if (!inFile.is_open()) {
            std::cout << "No existing library file found. Starting fresh.\n";
            return;
        }

        std::string line;
        while (std::getline(inFile, line)) {
            std::stringstream ss(line);

            std::string title, rating_str, watched_str;
            int rating;
            bool watched;

            std::getline(ss, title, ',');
            std::getline(ss, rating_str, ',');
            std::getline(ss, watched_str, ',');

            try {
                rating = std::stoi(rating_str);
                watched = (watched_str == "1");
                movies.push_back({title, rating, watched});
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error parsing line: " << line << " - " << e.what() << "\n";
            }
        }
        inFile.close();
        std::cout << "Library loaded from " << filename << "\n";
    }
};

int main() {
    MovieLibrary library;
    library.loadFromCSV("movies.csv");
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
            library.saveToCSV("movies.csv");
        } else if (choice == 2) {
            library.showMovies();
        }
    } while (choice != 0);

    std::cout << "Goodbye!\n";
    return 0;
}

