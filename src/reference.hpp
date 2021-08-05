#ifndef REFERENCE_HPP_
#define REFERENCE_HPP_

#include "nucleobase.hpp"

#include <vector>


namespace ref
{
class reference final
{
  public:
    using size_type = std::size_t;

    reference() = default;
    ~reference() = default;

    void add(const nucleotide::nucleobase base);
    void add_at(const size_type index,
                const nucleotide::nucleobase base);

    const nucleotide::nucleobase& get(const size_type index) const noexcept
    {
        return data[index];
    }

    size_type size() const noexcept
    {
        return data.size();
    }

  private:
    std::vector<nucleotide::nucleobase> data{};
};
}

#endif

