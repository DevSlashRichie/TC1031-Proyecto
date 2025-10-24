/*
 *  autor: Ricardo Rodríguez Medina
 *  fecha: September 2025
 */

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

struct Movie {
  std::string title;
  int rating;
  bool watched;
  std::tm seen_date;

  bool operator<(const Movie &other) const { return rating < other.rating; }

  std::string toCsv() const {
    std::ostringstream s;
    s << title << "," << rating << "," << watched << ","
      << std::put_time(&seen_date, "%Y-%m-%d");
    return s.str();
  }
};

std::ostream &operator<<(std::ostream &os, const Movie &m) {
  std::ostringstream seen_date_stream;
  seen_date_stream << std::put_time(&m.seen_date, "%Y-%m-%d");

  os << "Title: " << m.title << " | Rating: " << m.rating
     << " | Watched: " << (m.watched ? "Yes" : "No")
     << " | Seen Date: " << seen_date_stream.str();
  return os;
}

class MovieLibrary {
private:
  std::multiset<Movie> movies;

public:
  void addMovie(const std::string &title, int rating) {
    std::time_t t = std::time(nullptr);
    std::tm now = *std::localtime(&t);
    Movie m{title, rating, true, now};
    movies.insert(m);

    std::cout << "\n";
    std::cout << "Movie added: " << title << " with rating " << rating << "\n";
  }

  void showMovies() {
    if (movies.empty()) {
      std::cout << "No movies in library.\n";
      return;
    }

    std::cout << "\n--- Movie Library (Top Rated First) ---\n";
    for (auto it = movies.rbegin(); it != movies.rend(); ++it) {
      const auto &m = *it;
      std::ostringstream seen_date_stream;
      seen_date_stream << std::put_time(&m.seen_date, "%Y-%m-%d");

      std::cout << m << "\n";
    }
    std::cout << "--------------------------------------\n";
  }

  void showMoviesByDate() {
    if (movies.empty()) {
      std::cout << "No movies in library.\n";
      return;
    }

    std::vector<Movie> sorted_movies(movies.begin(), movies.end());
    std::sort(sorted_movies.begin(), sorted_movies.end(),
              [](const Movie &b, const Movie &a) {
                return std::mktime(const_cast<std::tm *>(&a.seen_date)) <
                       std::mktime(const_cast<std::tm *>(&b.seen_date));
              });

    std::cout << "\n--- Movie Library (Sorted by Seen Date) ---\n";
    for (const auto &m : sorted_movies) {
      std::ostringstream seen_date_stream;
      seen_date_stream << std::put_time(&m.seen_date, "%Y-%m-%d");

      std::cout << m << "\n";
    }
    std::cout << "-------------------------------------------\n";
  }

  void showMoviesByRating(int rating) {
    if (movies.empty()) {
      std::cout << "No movies in library.\n";
      return;
    }

    // we use this to order by the rating given. But we need a dummy because
    // it's how we compare.
    Movie dummy{"", rating, false, {}};

    auto lower = movies.lower_bound(dummy);
    auto upper = movies.upper_bound(dummy);

    std::cout << "\n--- Movies with rating " << rating << " ---\n";

    if (lower == upper) {
      std::cout << "No movies found with that rating.\n";
    } else {
      for (auto it = lower; it != upper; ++it) {
        const auto &m = *it;

        std::cout << m << "\n";
      }
    }

    std::cout << "-------------------------------------\n";
  }

  void saveToCSV(const std::string &filename) {
    if (movies.empty()) {
      std::cout << "You are trying to save 0 movies !!!";
      return;
    }

    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
      std::cerr << "Could not open file for writing: " << filename << "\n";
      return;
    }

    outFile << "MovieName,Grade,Seen,SeenDate\n";

    for (const auto &m : movies) {
      outFile << m.toCsv();
    }

    outFile.close();
    std::cout << "Library saved to " << filename << "\n";
  };

  void loadFromCSV(const std::string &filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
      std::cout << "No existing library file found. Starting fresh.\n";
      return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
      std::stringstream ss(line);

      std::string title, rating_str, watched_str, seen_date_str;
      int rating;
      bool watched;
      std::tm seen_date = {};

      std::getline(ss, title, ',');

      if (title == "MovieName") {
        continue;
      }

      std::getline(ss, rating_str, ',');
      std::getline(ss, watched_str, ',');
      std::getline(ss, seen_date_str, ',');

      try {
        rating = std::stoi(rating_str);
        watched = (watched_str == "1");

        std::istringstream sds(seen_date_str);
        sds >> std::get_time(&seen_date, "%Y-%m-%d");

        movies.insert({title, rating, watched, seen_date});
      } catch (const std::invalid_argument &e) {
        std::cerr << "Error parsing line: " << line << " - " << e.what()
                  << "\n";
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
    std::cout << "3. Show all movies (sorted by seen date)\n";
    std::cout << "4. Show movies by specific rating\n";
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
    } else if (choice == 3) {
      library.showMoviesByDate();
    } else if (choice == 4) {
      int rating;
      std::cout << "Enter rating to search for: ";
      std::cin >> rating;
      library.showMoviesByRating(rating);
    }
  } while (choice != 0);

  std::cout << "Goodbye!\n";
  return 0;
}
