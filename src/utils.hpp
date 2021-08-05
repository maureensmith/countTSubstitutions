#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <string>
#include <cctype> 

namespace utils
{
inline unsigned string_to_unsigned(std::string::iterator& it)
{
    unsigned ret = 0;
    do
    {
        const auto val = *it;
        if (not std::isdigit(val))
        {
            return ret;
        }
        ret *= 10;
        ret += val - '0';
        ++it;
    }
    while (true);
}

template <int N>
std::string::iterator find_tab_in_string(std::string::iterator it)
{
    int i = 0;
    while (i != N)
    {
        if (*it == '\t')
        {
            ++i;
        }
        ++it;
    }
    return it;
}

    std::string extract_read_name(const std::string& line);

inline bool check_readpair_names(std::string::iterator it_a, std::string::iterator it_b) {
    while(*it_a != '\t') {
        if(*it_a != *it_b) {
            return false;
        }
        ++it_a;
        ++it_b;
    }
    return true;
}

unsigned long choose(const int n, const int k);

}



#endif

