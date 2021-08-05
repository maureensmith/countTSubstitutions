#ifndef COUNT_HPP_
#define COUNT_HPP_

#include "reference.hpp"
#include "ref_map.hpp"
#include "utils.hpp"
#include "nucleobase.hpp"

#include <array>
#include <string>
#include <vector>
#include <utility>

namespace count
{
class counter_1 final
{
  public:
    using count_type = unsigned;

    ~counter_1() = default;


//    counter_1(const ref::reference& ref)
//    : nucleobase_count(nucleotide::numberOfValidSymbols(false)), data(ref.size(), std::vector<count_type>(nucleobase_count))
//    {
//    }

    counter_1(): nucleobase_count(nucleotide::numberOfValidSymbols(false))
    {
    }

    void count(const ref::ref_map& read);

    void count(const ref::ref_map& read, const unsigned times);

//    void count(const char base)
//    {
//        ++T_data.back()[nucleotide::nucleobase{base}.to_id()];
//        //++data[index][nucleotide::nucleobase{base}.to_id()];
//    }

    void count(const char base);


    void add_read();

    void write_to_file(const std::string& out_file);

  private:
    //counting Ts and the respective mutations for each read
    //std::vector<std::array<count_type, nucleobase_count>> data;
    const bool ambig{false};
    const unsigned nucleobase_count;
    //std::vector<std::vector<count_type>> data;
    // vector containing A, C, G, T
    std::vector<std::vector<count_type>> T_data;
//    std::vector<count_type> num_T;
//    std::vector<count_type> num_TtoA;
//    std::vector<count_type> num_TtoC;
//    std::vector<count_type> num_TtoG;
//    std::vector<count_type> total_T;
};



}

#endif
