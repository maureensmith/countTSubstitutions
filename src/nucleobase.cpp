#include "nucleobase.hpp"

#include <stdexcept>
#include <utility>


namespace nucleotide
{


    const std::array<char, 17> nucleobase::bases{'A', 'C', 'G', 'T', 'N' ,'R', 'Y', 'K', 'M', 'S', 'W', 'B', 'D', 'H', 'V', 'Z', 'X'};

    nucleobase::nucleobase(char base)
    {

        //mapping of the nucleotide bases to IDs (eg A-A/2 = 0, C-A/2 = 1 etc)
        //A=0, C=1, G=2, T=3, N=4, X=5
        switch(base)
        {
            case 'A': this->base_id = 0; break;
            case 'C': this->base_id = 1; break;
            case 'G': this->base_id = 2; break;
            case 'T': this->base_id = 3; break;
            case 'N': this->base_id = 4; break;
            case 'R': this->base_id = 5; break;
            case 'Y': this->base_id = 6; break;
            case 'K': this->base_id = 7; break;
            case 'M': this->base_id = 8; break;
            case 'S': this->base_id = 9; break;
            case 'W': this->base_id = 10; break;
            case 'B': this->base_id = 11; break;
            case 'D': this->base_id = 12; break;
            case 'H': this->base_id = 13; break;
            case 'V': this->base_id = 14; break;
            //Z=Zero, X does not exist
            default: this->base_id = 15; break;
        }
    }
    nucleobase::nucleobase(const int id)
    {
        //check if the id is between 0 and max valid symbol
        if (std::max(std::min(nucleobase::bases.size()-1, static_cast<unsigned long>(id)), 0ul) != id)
        {
            throw std::invalid_argument(std::to_string(id) + std::string{" is not a valid base_id id"});
        }
        base_id = id;
    }

    //TODO used to be called when we had no fasta file... weg mit der possibility
//    nucleobase::nucleobase(const int base_id_from1)
//    {
//        // could be set back to 5, since it is there only for reading reference which is usually only ACGT (=1,2,3,4)
//        if (std::max(std::min(nucleobase::bases.size(), static_cast<unsigned long>(base_id_from1)), 1ul) != base_id_from1)
//        {
//            throw std::invalid_argument(std::to_string(base_id_from1) + std::string{" is not a valid base_id id"});
//        }
//        base_id = base_id_from1 - 1;
//    }

    bool isValidNucl(const char nucl, const bool ambig) {
        if(ambig)
            return nucleobase{nucl}.to_id() < numberOfAmbigSymbols;
        else
            return nucleobase{nucl}.to_id() < numberOfBasicSymbols;
    }

     unsigned numberOfValidSymbols(const bool ambig) {
        if(ambig)
            return numberOfAmbigSymbols;
        else
            return numberOfBasicSymbols;
    }

}

