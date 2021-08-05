#ifndef NUCLEOBASE_HPP_
#define NUCLEOBASE_HPP_

#include <string>
#include <array>
#include <cstdint>


namespace nucleotide
{
     constexpr unsigned numberOfBasicSymbols = 4;
     constexpr unsigned numberOfAmbigSymbols = 15;

    class nucleobase final
    {
      private:
        static const std::array<char, 17> bases;
        //static const std::vector<char> bases;
        // id (index) of the current base_id in array (initial the last element = X = invalid)
        uint8_t base_id{static_cast<uint8_t>(bases.size() - 1)};

      public:
        nucleobase() = default;
        ~nucleobase() = default;

        // standard copy constructor
        nucleobase(const nucleobase&) = default;
        // standard assignment operator
        nucleobase& operator= (const nucleobase&) = default;

        explicit nucleobase(char base);
        //only used for the reading the reference, which if not in fasta might be given as pos,nucl_id (= 1,2,3,4)
        explicit nucleobase(const int base_id);


        char get() const noexcept
        {
            return nucleobase::bases[base_id];
        }

        uint8_t to_id() const
        {
            return base_id;
        }

        bool operator==(const nucleobase& rhs) const noexcept
        {
            return to_id() == rhs.to_id();
        }
    };

    bool isValidNucl(const char nucl, const bool ambig);

    unsigned numberOfValidSymbols(const bool ambig);
}

#endif
