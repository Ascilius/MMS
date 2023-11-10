// v0.1

#include <cstdio> // for renaming file
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// metadata editing stuff
#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <locale>
#include <codecvt>

const bool debug = false;

// chatgpt my beloved
int main(int argc, char* argv[]) {
    const std::string tsv_file_path = argv[2];
    std::ifstream tsv_file(tsv_file_path);

    if (!tsv_file.is_open()) {
        std::cerr << "Error opening the TSV file." << std::endl;
        return 1;
    }

    std::vector<std::vector<std::string>> data; // 2D vector to store TSV data

    std::string line;
    int n = 0;
    while (std::getline(tsv_file, line)) {
        std::vector<std::string> row;
        std::istringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, '\t')) {
            row.push_back(cell);
        }

        data.push_back(row);
        n++;
    }

    // Now 'data' contains the TSV data in a 2D vector
    // You can access individual elements using data[row_index][col_index]

    // Example: Print the TSV data
    data.erase(data.begin()); // removing column headers
    std::cout << --n << " rows read:" << std::endl;
    for (const auto& row : data) {
        std::cout << row[0] << std::endl;
        const int size = row.size();
        for (int i = 1; i < size; ++i)
            std::cout << "\t" << row[i] << std::endl;
    }

    tsv_file.close();

    // -------------------------
    // editing files

    const std::string directory_path = argv[1];
    std::cout << "\nEditing files in \"" << directory_path << "\"...\n" << std::endl;

    // metadata
    n = 0;
    int m = 0;
    for (const auto& row : data) {
        const std::string mp3_file_name = row[0];
        std::string mp3_file_path = directory_path + mp3_file_name;
        std::cout << "\033[0mEditing \"" << mp3_file_path << "\"..." << std::endl;

        try {
            TagLib::FileRef file(mp3_file_path.c_str());

            // std::cout << "Debug: file.tag(): " << file.tag() << std::endl;
            if (file.tag()) {

                // modify the number
                file.tag()->setTrack(std::stoi(row[3]));

                // modify the title
                std::string new_title = row[5]; // use english title bc for some reason japanese doesnt work on this specific metadata
                if (debug) {
                    std::cout << "\tDebug: new_title: " << new_title << std::endl; 
                }
                file.tag()->setTitle(new_title);

                // modify the contributing artists
                file.tag()->setArtist(row[6]);

                // modify the album
                file.tag()->setAlbum(row[7]);

                /*
                // modify the album artist
                file.tag()->setAlbumArtist(row[7]); // theres no album artist modifying method???
                */

                // modify the genre
                file.tag()->setGenre(row[9]);

                // modify the year
                file.tag()->setYear(std::stoi(row[10]));

                // Save changes
                file.save();
                std::cout << "\t\033[32mMetadata modified successfully.\033[0m" << std::endl;
                n++;
            } else {
                std::cerr << "\t\033[31mERROR: Missing tag not available in the file.\033[0m" << std::endl;
            }
        } catch (const std::exception& ex) {
            std::cerr << "\tError: " << ex.what() << std::endl;
        }

        // renaming file
        std::string new_file_name = directory_path + row[1];
        if (debug) {
            std::cout << "\tDebug: mp3_file_path: " << mp3_file_path << std::endl;
            std::cout << "\tDebug: new_file_name: " << new_file_name << std::endl;
        }
        if (std::rename(mp3_file_path.c_str(), new_file_name.c_str()) == 0) { // actually renaming
            std::cout << "\t\033[32mFile renamed successfully.\033[0m" << std::endl;
            m++;
        } else {
            std::perror("\t\033[31mERROR");
        }
    }
    std::cout << "\n\033[0m" << n << " files' metadata edited." << std::endl;
    std::cout << m << " file(s) renamed." << std::endl;

    return 0;
}
