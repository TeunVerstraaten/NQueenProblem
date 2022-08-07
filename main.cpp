#include "src/NQueen.h"

#include <chrono>
#include <iostream>

using namespace std::chrono;

int main() {
    const size_t N = 18;
    PartialBoard<N>::init();
    auto start  = high_resolution_clock::now();
    auto result = NQueen<N>::numberOfSolutionsToNQueenProblem();
    std::cout << "Nr of configurations:\t" << result << '\n';
    std::cout << "Time taken:\t" << duration_cast<microseconds>(high_resolution_clock::now() - start).count() / 1000000.0f << "\n";
}

// # of solutions. From Wikipedia
//
//    n 	fundamental 	        all
//    7 	6 	                40
//    8 	12 	                92
//    9 	46 	                352
//    10 	92 	                724
//    11 	341 	                2,680
//    12 	1,787 	                14,200
//    13 	9,233 	                73,712
//    14 	45,752 	                365,596
//    15 	285,053 	        2,279,184
//    16 	1,846,955 	        14,772,512
//    17 	11,977,939 	        95,815,104
//    18 	83,263,591 	        666,090,624
//    19 	621,012,754 	        4,968,057,848
//    20 	4,878,666,808 	        39,029,188,884
//    21 	39,333,324,973 	        314,666,222,712
//    22 	336,376,244,042 	2,691,008,701,644
//    23 	3,029,242,658,210 	24,233,937,684,440
//    24 	28,439,272,956,934 	227,514,171,973,736
//    25 	275,986,683,743,434 	2,207,893,435,808,352
//    26 	2,789,712,466,510,289 	22,317,699,616,364,044
//    27 	29,363,495,934,315,694 	234,907,967,154,122,528