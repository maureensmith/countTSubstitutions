#ifndef IO_TOOLS_HPP_
#define IO_TOOLS_HPP_

#include "reference.hpp"

#include <fstream>
#include <string>


namespace io_tools
{
ref::reference read_reference(const std::string& file_name);

std::string get_first_data_line(std::ifstream& stream);

void check_and_create_output_directory(const std::string& output_file);
}

#endif

