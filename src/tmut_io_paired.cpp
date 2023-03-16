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


        unsigned readCount = 0;

        do {
            read.clear();
            const auto is_prepared = aligner.prepare(line_a, line_b);

            if (is_prepared) {
                aligner.align(counter);

                aligner.align_1(counter);

                counter.count(read);
            }

            // status of processed reads
            ++readCount;
            if (readCount % 100000 == 0)
                std::cout << readCount << " processed reads " << std::endl;

            std::getline(input_a, line_a);
            std::getline(input_b, line_b);
        } while (input_a.good() and input_b.good());
        

        std::cout << "Total read count: " << readCount << std::endl;

        counter.write_to_file(out_file);
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

