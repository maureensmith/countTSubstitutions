#include "io_tools.hpp"

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
namespace io_tools {

    ref::reference read_reference(const std::string &file_name) {
        std::cout << "\nReading reference file " << file_name << std::endl;

        std::ifstream infile(file_name);
        if (not infile.good()) {
            throw std::runtime_error("Reference file " + file_name + std::string{" not found!"});
        }

        const auto is_comment = [](const std::string &line) {
            return line[0] == '>';
        };

        ref::reference ref;
        std::string line;
        std::getline(infile, line);
        const bool is_fasta = is_comment(line);

        if (is_fasta) {
            while (not infile.eof()) {
                std::getline(infile, line);
                if (is_comment(line)) {
                    continue;
                }

                std::for_each(line.cbegin(), line.cend(), [&ref](char c) {
                    c = static_cast<char> (std::toupper(c));
                    //fasta may contain breakline which is ignored on Macs but interpreted on linux. Only read valid
                    //nucleotide, as we expect this from a reference sequence
                    if(nucleotide::isValidNucl(c, false))
                        ref.add(nucleotide::nucleobase{c});
                });
            }
        } else {
            while (not infile.eof()) {
                if (not line.empty()) {
                    std::stringstream ss;
                    ss.str(line);
                    std::string pos;
                    std::string base;
                    std::getline(ss, pos, ',');
                    std::getline(ss, base);
                    ref.add_at(stoi(pos), nucleotide::nucleobase{std::stoi(base)});
                }
                std::getline(infile, line);
            }
        }

        return ref;
    }


    std::string get_first_data_line(std::ifstream &stream) {
        std::string line;
        do { 
            if(stream.good()) {
                std::getline(stream, line);
            }
        } while (line[0] == '@');

        return line;
    }

    void check_and_create_output_directory(const std::string &output_file) {
        fs::path file = fs::absolute(output_file);
        fs::path dir = file.parent_path();
        if (!fs::exists(dir)) {
            std::cout << "Creating output directory " << dir << std::endl;
            fs::create_directories(dir);
        }
    }

}


