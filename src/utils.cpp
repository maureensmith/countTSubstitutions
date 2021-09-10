#include "utils.hpp"
namespace utils
{
    unsigned long choose(const int n, const int k)
    {
        if(k == 0)
        {
            return(1);
        } else {
            return((n * choose(n - 1, k - 1)) / k);
        }
    }

    char to_upper(const char in)
    {
        static char offsets[] = {32, 0};
        return in - offsets[in <= 'Z'];
    }

    std::string extract_read_name(const std::string& line) {
        std::size_t tabPos = line.find('\t');
        return(line.substr(0,tabPos));
    }


}

