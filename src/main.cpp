#include <iostream>
#include <string>
#include "tmut_io_paired.hpp"
#include "io_tools.hpp"

void printUsage(const std::string& progName) {
    std::cout << "Usage:" << std::endl;
    std::cout << progName << " -r reffile -s1 samfile1 [-s2 samfile2] -o outfile -d dimension [-q qualityTrehsold] [-a]\n" << std::endl;
    std::cout << "Parameters: " << std::endl;
    std::cout << "-r, -ref <reffile>\t reference file in fasta format" << std::endl;
    std::cout << "-s1, -sam1 <samfile1>\t sam file to read in" << std::endl;
    std::cout << "-s2, -sam2 <samfile2>\t (optional) second sam file ro read in, if paired end reads are given" << std::endl;
    std::cout << "-o, -out <outfile>\t output file where there counts is written to" << std::endl;
    //std::cout << "-d, -dimension <dimension> \t 1, 2 or 3,  to count single, double or triple nucleotide occurrences" << std::endl;
    std::cout << "-q, -quality <qualityThreshold>\t (optional) filtering quality of each nucleotide to reach the given threshold" << std::endl;
    std::cout << "-a, -ambig \t (optional) by default only the nucleotides are counted and any ambiguity is ignored. "
                 "If this flag ist set, also all ambiguity symbols according to the IUPAC notation are counted."
                 "For now, this option is only enabled for dimension 1 and for single read SAM." << std::endl;
}

int main(int argc,
         char** argv)
{
    std::string ref_file; //{argv[1]};
    std::string sam_file_A; //{argv[2]};
    std::string sam_file_B; //{argv[3]};
    std::string out_file;
   // int dimension; // = std::stoi(argv[5]);
    int qualityThreshold = 0; //std::stoi(argv[6]);

    bool oFlag = false;
    bool sFlag = false;
    bool s2Flag = false;
    bool rFlag = false;
    bool aFlag = false;


    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if(arg == "-o" || arg == "-outfile") {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                out_file = argv[++i]; // Increment 'i' so we don't get the argument as the next argv[i].
                oFlag = true;
            } else {
                std::cerr << argv[i] << " option requires one argument." << std::endl;
                return 1;
            }
        } else if(arg == "-q" || arg == "-qualityThreshold") {
            if (i + 1 < argc) {
                std::cout << "-q " << argv[i+1] << std::endl;
                qualityThreshold = std::stoi(argv[++i]);
            } else {
                std::cerr << argv[i] << " option requires one argument." << std::endl;
                return 1;
            }
        } else if(arg == "-s1" || arg == "-sam1") {
            if (i + 1 < argc) {
                sam_file_A = argv[++i];
                sFlag = true;
            } else {
                std::cerr << argv[i] << " option requires one argument." << std::endl;
                return 1;
            }
        } else if(arg == "-s2" ||arg == "-sam2") {
            if (i + 1 < argc) {
                sam_file_B = argv[++i];
                s2Flag = true;
            } else {
                std::cerr << argv[i] << " option requires one argument." << std::endl;
                return 1;
            }
        } else if(arg == "-r" || arg == "-ref") {
            if (i + 1 < argc) {
                ref_file = argv[++i];
                rFlag = true;
            } else {
                std::cerr << argv[i] << " option requires one argument." << std::endl;
                return 1;
            }
        }else if(arg == "-a" || arg == "-ambig") {
            aFlag = true;
        }else if(arg == "-h" || arg == "-help") {
            printUsage(argv[0]);
            return 0;
        }
    }

    // the mandatory arguments have to be set (samfile, outputfile, dimension)
    // dimension has to be 1, 2 or 3
    //TODO the counting for the ambiguous symbols is only possible for 1D not. klären ob auch für 2D und 3D
    if(argc < 9 || !sFlag || !oFlag || !rFlag){
        std::cerr << "There has been something wrong with the arguments." << std::endl;
        printUsage(argv[0]);
        return 1;
    }

//    if(aFlag && dimension != 1) {
//        std::cout << "Ambiguous nucleotides are only counted for single occurrences. The dimension is set to 1." << std::endl;
//        dimension = 1;
//    }



    std::cout << "Sam1: " << sam_file_A << std::endl;
    if(s2Flag)
        std::cout << "Sam2: " << sam_file_B << std::endl;
    std::cout << "Reffile: " << ref_file << std::endl;
    std::cout << "Outfile: " << out_file << std::endl;
    if(qualityThreshold > 0)
        std::cout << "Quality threshold: " << qualityThreshold << std::endl;
    if(aFlag)
        std::cout << "Counting nucleotides and ambiguities" << std::endl;

    // Check already in the beginning, if the directory exists and if not, create it
    io_tools::check_and_create_output_directory(out_file);

    // call for paired end reads
    if(s2Flag) {
        tmut_io_paired::analyse_positions(ref_file,
                                                 sam_file_A,
                                                 sam_file_B,
                                                 out_file,
                                                 qualityThreshold);
    }
    return 0;
}
