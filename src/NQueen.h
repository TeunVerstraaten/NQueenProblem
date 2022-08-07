//
// Created by pc on 4-8-22.
//

#ifndef NQUEEN_NQUEEN_H
#define NQUEEN_NQUEEN_H

#include "PartialBoard.h"

#include <vector>

template <size_t N>
class NQueen {

    typedef typename std::vector<PartialBoard<N>>::const_iterator Iterator;

  public:
    static size_t numberOfSolutionsToNQueenProblem();

    // Count all valid ways to extend a valid partial board to a full N Queen solution
    static size_t countCompatibleConfigurations_DFS(const PartialBoard<N>& root);

    // Sum number of valid extensions of partial boards for all partial boards in the iterator range
    static size_t sumCompatibleConfigurations(Iterator start, Iterator end);

    // Parallel version of NQueen::sumCompatibleConfigurations(2)
    static size_t countCompatibleConfigurations_parallel(Iterator start, Iterator end);
};

#include "NQueen.hxx"

#endif // NQUEEN_NQUEEN_H
