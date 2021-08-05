#ifndef REF_MAP_HPP
#define REF_MAP_HPP

#include <utility>
#include "nucleobase.hpp"

#include <iterator>
#include <cstring>


namespace ref
{
class ref_map final
{
  public:
    using pos_nucl = std::pair<unsigned, nucleotide::nucleobase>;
    using size_type = std::size_t;

    ref_map() = default;

    ~ref_map()
    {
        delete[] data;
    }

    auto begin()
    {
        return data;
    }

    auto begin() const
    {
        return data;
    }

    auto end() const
    {
        return fake_end;
    }

    auto end()
    {
        return fake_end;
    }

    void remove(pos_nucl* pos)
    {
        --fake_end;
        *pos = *fake_end;
    }

    void reserve(const size_type size)
    {
        if (size >= capacity)
        {
            capacity = size + 1;
            auto tmp = data;
            const auto ns = this->size();
            data = new pos_nucl[capacity];
            //TODO: work around: seit gcc8 compile fehler
            std::memcpy(reinterpret_cast<char*> (data), reinterpret_cast<char*> (tmp), sizeof (pos_nucl) * ns);
            fake_end = data + ns;
            delete[] tmp;
        }
    }

    void clear()
    {
        fake_end = data;
    }

    void add(std::pair<unsigned, nucleotide::nucleobase>&& pair)
    //void add(const unsigned p, const char n)
    {
        *fake_end = pair;
        ++fake_end;
        //*(fake_end - 1) = std::make_pair(p, nucleobase{n});
    }

    size_type size() const noexcept
    {
        return std::distance(begin(), end());
    }

  private:
    size_type capacity{0};
    pos_nucl* data{nullptr};
    pos_nucl* fake_end{nullptr};
};
}

#endif

