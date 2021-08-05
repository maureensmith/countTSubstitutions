#ifndef ALIGNER_HPP_
#define ALIGNER_HPP_

#include "count.hpp"
#include "reference.hpp"
#include "ref_map.hpp"

#include <string>

namespace aligner
{
class aligner final
{
  public:
    aligner() = delete;

    aligner(const ref::reference& ref,
            ref::ref_map& read,
            const int qualityThreshold) noexcept
        : ref{ref}, read{read}, quality_threshold{qualityThreshold}, qualiCheck{checkQuali()}
    {
    }

    aligner(const ref::reference& ref,
            ref::ref_map& read,
            const int qualityThreshold, const bool a) noexcept
            : ref{ref}, read{read}, quality_threshold{qualityThreshold}, ambig{a}, qualiCheck{checkQuali()}
    {
    }

    // aligns the first of the paired end read
    void align(count::counter_1& count_obj);

    // aligns the second paired read and counts the nucleotides per position
    void align_1(count::counter_1& count_obj);


    //for the case of paired read SAM files
    bool prepare(std::string& line_a,
                 std::string& line_b);

    //for the case of a single SAM file
    bool prepare(std::string& line);

  private:
    const ref::reference& ref;
    ref::ref_map& read;
    unsigned posinref_a{0};
    std::string::iterator cigar_it_a{};
    std::string::iterator cigar_end_a{};
    std::string::iterator read_seq_a{};
    std::string::iterator quality_seq_a{};
    unsigned posinref_b{0};
    std::string::iterator cigar_it_b{};
    std::string::iterator cigar_end_b{};
    std::string::iterator read_seq_b{};
    std::string::iterator quality_seq_b{};
    bool aligning_started{false};

    const int quality_threshold{0};

    const bool ambig{false};
    bool qualiCheck{false};

    bool checkQuali();
};
}

#endif
