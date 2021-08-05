#include "tmut_io_paired.hpp"
#include "io_tools.hpp"
#include "count.hpp"
#include "reference.hpp"
#include "aligner.hpp"


#include <algorithm>
#include <iostream>
#include <chrono>


namespace tmut_io_paired
{

namespace
{
    void processReads(const ref::reference& reference,
                      std::ifstream& input_a,
                      std::ifstream& input_b,
                      const std::string& out_file,
                      const int qualityThreshold) {
        std::string line_a = io_tools::get_first_data_line(input_a);
        std::string line_b = io_tools::get_first_data_line(input_b);

        //count::counter_1 counter{reference};
        count::counter_1 counter;
        ref::ref_map read;

        aligner::aligner aligner{reference, read, qualityThreshold};

        // record to time for each step
        unsigned prep = 0;
        unsigned align_a = 0;
        unsigned align_b = 0;
        unsigned count = 0;

        unsigned readCount = 0;

        while (input_a.good() and input_b.good()) {
            read.clear();
            auto now = std::chrono::high_resolution_clock::now();
            const auto is_prepared = aligner.prepare(line_a, line_b);
            auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now() - now);
            prep += diff.count();
            if (is_prepared) {
                now = std::chrono::high_resolution_clock::now();

                aligner.align(counter);

                diff = std::chrono::duration_cast<std::chrono::nanoseconds>(
                        std::chrono::high_resolution_clock::now() - now);
                align_a += diff.count();

                now = std::chrono::high_resolution_clock::now();

                aligner.align_1(counter);

                diff = std::chrono::duration_cast<std::chrono::nanoseconds>(
                        std::chrono::high_resolution_clock::now() - now);
                align_b += diff.count();

                now = std::chrono::high_resolution_clock::now();

                counter.count(read);

                diff = std::chrono::duration_cast<std::chrono::nanoseconds>(
                        std::chrono::high_resolution_clock::now() - now);
                count += diff.count();
            }

            // status of processed reads
            ++readCount;
            if (readCount % 100000 == 0)
                std::cout << readCount << " processed reads " << std::endl;

            std::getline(input_a, line_a);
            std::getline(input_b, line_b);
        }

        counter.write_to_file(out_file);
        std::cout << "Total read count: " << readCount << std::endl;
        std::cout << "Time to Prepare: " << prep << std::endl;
        std::cout << "Time to Align A: " << align_a << std::endl;
        std::cout << "Time to Align B: " << align_b << std::endl;
        std::cout << "Time Counting: " << count << std::endl;
    }

}

    void analyse_positions(const std::string& ref,
                           const std::string& sam_a,
                           const std::string& sam_b,
                           const std::string& out_file,
                           const int qualityThreshold)
    {
        const auto ref_map = io_tools::read_reference(ref);

        std::ifstream input_a(sam_a);
        std::ifstream input_b(sam_b);

        std::cout << "\nStart counting" << std::endl;
        processReads(ref_map, input_a, input_b, out_file, qualityThreshold);
    }
}

