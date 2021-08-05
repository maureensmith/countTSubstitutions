#include "reference.hpp"


namespace ref
{

void reference::add(const nucleotide::nucleobase base)
{
    this->data.push_back(base);
}

void reference::add_at(const size_type index,
                       const nucleotide::nucleobase base)
{
    if (size() <= index)
    {
        data.resize(index);
    }

    data[index - 1] = base;
}

}

