#include <iostream>

// Implementations of template functions defined in PartialBoard.h

template <size_t N>
std::vector<uint8_t> PartialBoard<N>::possibleNumbersArray[1 << N];

template <size_t N>
bool PartialBoard<N>::allColumnsFull() const {
    // No free columns remaining?
    return not(m_freeColumnBitMask);
}

template <size_t N>
PartialBoard<N>& PartialBoard<N>::setNextRow(uint8_t column) {
    const auto mask = ~(1u << column); // This column will now longer be available
    m_freeColumnBitMask &= mask;
    m_freeUpwardDiagonals   = updateUpwardDiagonal(m_freeUpwardDiagonals, mask);
    m_freeDownwardDiagonals = updateDownwardDiagonal(m_freeDownwardDiagonals, mask);
    return *this;
}

template <size_t N>
const std::vector<uint8_t>& PartialBoard<N>::possibleNumbers() const {
    return possibleNumbersArray[m_freeColumnBitMask & m_freeUpwardDiagonals & m_freeDownwardDiagonals];
}

template <size_t N>
PartialBoard<N> PartialBoard<N>::copyAndSetNextRow(uint8_t column) const {
    const auto mask = ~(1u << column);
    return {m_freeColumnBitMask & mask,
            updateUpwardDiagonal(m_freeUpwardDiagonals, mask),
            updateDownwardDiagonal(m_freeDownwardDiagonals, mask)};
}

template <size_t N>
void PartialBoard<N>::init() {
    for (size_t i = 0; i != (1 << N); ++i)
        for (size_t b = 0; b != N; ++b)
            if (i & (1u << b))
                possibleNumbersArray[i].push_back(b);

    std::cout << "Init done\n";
}

template <size_t N>
PartialBoard<N>::PartialBoard(uint32_t missingBitMask, uint32_t freeUpwardDiagonals, uint32_t freeDownwardDiagonals)
    : m_freeColumnBitMask(missingBitMask), m_freeUpwardDiagonals(freeUpwardDiagonals), m_freeDownwardDiagonals(freeDownwardDiagonals) {
}

template <size_t N>
uint32_t PartialBoard<N>::updateUpwardDiagonal(uint32_t upwardDiagonal, uint32_t mask) {
    // When moving to the next row, the upward diagonals shift one the right. That is, if a queen blocks the third column by an upward
    // diagonal on the current row, then it will block the second column on the next row
    upwardDiagonal &= mask;
    upwardDiagonal >>= 1u;
    // The highest column corresponding to column N - 1 cannot yet contain a queen, so we set its bit to a 1 to indicate that its a free
    // column
    upwardDiagonal |= (1u << (N - 1));
    return upwardDiagonal;
}

template <size_t N>
uint32_t PartialBoard<N>::updateDownwardDiagonal(uint32_t downwardDiagonal, uint32_t mask) {
    // similar to PartialBoard<N>::updateUpwardDiagonal(2)
    downwardDiagonal &= mask;
    downwardDiagonal <<= 1u;
    downwardDiagonal |= 1u;
    downwardDiagonal &= ~(1u << N);
    return downwardDiagonal;
}
