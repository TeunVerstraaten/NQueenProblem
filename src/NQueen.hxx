#include "NumberOfCores.h"

#include <cassert>
#include <future>
#include <iostream>
#include <numeric>
#include <vector>

// Implementations of template functions defined in NQueen.h

template <size_t N>
size_t NQueen<N>::numberOfSolutionsToNQueenProblem() {
    // Make a vector of valid partial boards
    std::vector<PartialBoard<N>> boards;

    // All possibilities for the first two rows where the queen in the first row is in a larger column than the queen in the second row. By
    // symmetry, we can count all ways to finish these boards and then multiply the result by 2
    for (size_t i = 2; i != N; ++i)
        for (size_t j = 0; j <= i - 2; ++j)
            boards.emplace_back(PartialBoard<N>{}.setNextRow(i).setNextRow(j));

    std::cout << "Split into " << boards.size() << " boards\n";
    return 2 * countCompatibleConfigurations_parallel(boards.begin(), boards.end());
}

template <size_t N>
size_t NQueen<N>::countCompatibleConfigurations_DFS(const PartialBoard<N>& root) {
    // We never search in invalid boards, so if every row has a queen this is a valid N Queen configuration
    if (root.allColumnsFull())
        return 1;

    // DFS. Look at all possible places for a queen on the next row, place it and count recursively.
    size_t totalCount = 0;
    for (size_t k : root.possibleNumbers()) {
        auto copy = root.copyAndSetNextRow(k);
        totalCount += countCompatibleConfigurations_DFS(copy);
    }
    return totalCount;
}

template <size_t N>
size_t NQueen<N>::sumCompatibleConfigurations(NQueen<N>::Iterator start, NQueen<N>::Iterator end) {
    return std::accumulate(
        start, end, 0, [](size_t a, const PartialBoard<N>& b) { return a + NQueen::countCompatibleConfigurations_DFS(b); });
}

template <size_t N>
size_t NQueen<N>::countCompatibleConfigurations_parallel(NQueen<N>::Iterator start, NQueen<N>::Iterator end) {
    const auto length = end - start;

    assert(static_cast<long long>(numCores) < end - start);

    const size_t                     jump = length / NUMBER_OF_CORES;
    std::vector<std::future<size_t>> futures;
    // Split the iterator range into numCores roughly equal components
    for (size_t i = 0; i != NUMBER_OF_CORES - 1; ++i)
        futures.push_back(std::async(
            std::launch::async, &NQueen::sumCompatibleConfigurations, std::next(start, i * jump), std::next(start, (i + 1ul) * jump)));

    // The last future has (possibly) slightly larger iterator range than the other ones.
    futures.push_back(
        std::async(std::launch::async, &NQueen::sumCompatibleConfigurations, std::next(start, (NUMBER_OF_CORES - 1) * jump), end));

    // Accumulate the result over all futures in futures vector.
    return std::accumulate(futures.begin(), futures.end(), 0ul, [](size_t p, auto& f) { return p + f.get(); });
}
