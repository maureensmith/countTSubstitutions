#ifndef TMUT_IO_HPP_
#define TMUT_IO_HPP_

#include <string>

namespace tmut_io_paired
{
    void analyse_positions(const std::string& ref,
                                  const std::string& sam_a,
                                  const std::string& sam_b,
                                  const std::string& out_file,
                                  const int qualityThreshold);

}

#endif
