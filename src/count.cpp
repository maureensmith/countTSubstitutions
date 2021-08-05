#include "count.hpp"

#include <algorithm>
#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <cassert>

namespace count
{

    void counter_1::count(const ref::ref_map& read) {
        counter_1::count(read,1);
    }
    void counter_1::count(const ref::ref_map& read, const unsigned times)
    {
        std::for_each(read.begin(), read.end(), [this, times](const auto& entry)
        {
            //if(entry.second.get() not_eq 'N')
            if(nucleotide::isValidNucl(entry.second.get(), this->ambig))
            {
                assert(not T_data.empty());
                //data[entry.first - 1][entry.second.to_id()] += times;
                T_data.back()[entry.second.to_id()] += times;
            }
        });
    }

    void counter_1::count(const char base)
    {
        assert(not T_data.empty());
        assert(nucleotide::nucleobase{base}.to_id() < nucleotide::numberOfValidSymbols(false));
        ++T_data.back()[nucleotide::nucleobase{base}.to_id()];
    }

    void counter_1::add_read(const std::string& name) {
        read_names.emplace_back(name);
        T_data.emplace_back(std::vector<count_type>(nucleobase_count));
    }

void counter_1::write_to_file(const std::string& out_file)
{
    std::cout << "\nWriting counts to " << out_file << std::endl;
    std::ofstream outfile(out_file);

    if (outfile.good())
    {
        //iterate header through valid symbols (also for ambiguous)
        outfile << "readName";
        for(int i = 0; i<nucleotide::numberOfValidSymbols(ambig); ++i) {
            outfile << "\t" << nucleotide::nucleobase{i}.get();
        }
        outfile << "\n";
        std::cout << "number of sequences " << T_data.size() << std::endl;
        for (unsigned i = 0; i < T_data.size(); ++i)
        {
            outfile << read_names[i];
            //std::for_each(data[i].cbegin(), data[i].cend(), [&outfile](const auto& entry)
            std::for_each(T_data[i].cbegin(), T_data[i].cend(), [&outfile](const auto& entry)
            {
                outfile << '\t' << entry;
            });
            outfile << '\n';
        }
    }
}

}

