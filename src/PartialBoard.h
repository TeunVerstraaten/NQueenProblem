//
// Created by pc on 3-8-22.
//

#ifndef NQUEEN_PARTIALBOARD_H
#define NQUEEN_PARTIALBOARD_H

#include <cstddef>
#include <cstdint>
#include <vector>

// This class contains the information of a partial board. That is, a board where the first couple of rows have queens placed on them but
// not necessarily all N rows. We store which column already has a queen in it and which diagonals are blocked.

template <size_t N>
class PartialBoard {

  public:
    PartialBoard() = default;

    // Check if all columns are set
    [[nodiscard]] bool allColumnsFull() const;

    // Set queen in given column on the next row and return reference to result. Assumes (and does not check) that column is a valid
    // position for next queen
    PartialBoard& setNextRow(uint8_t column);

    // Return reference to vector all columns on the next row where a valid queen may be placed
    [[nodiscard]] const std::vector<uint8_t>& possibleNumbers() const;

    // Copy the current PartialBoard and place a queen on the next row in the given column.
    [[nodiscard]] PartialBoard copyAndSetNextRow(uint8_t column) const;

    // Initialize some static lookup arrays
    static void init();

  private:
    // Constructor. Private because it is easy for a user to enter three numbers that do not constitute any realizable board
    PartialBoard(uint32_t missingBitMask, uint32_t freeUpwardDiagonals, uint32_t freeDownwardDiagonals);

    // This return the upward diagonal bitmask for the next row. The mask is ~(1u << column) where column is the column being set
    static uint32_t updateUpwardDiagonal(uint32_t upwardDiagonal, uint32_t mask);

    // This returns the downward diagonal bitmask for the next row. The mask is ~(1u << column) where column is the column being set
    static uint32_t updateDownwardDiagonal(uint32_t downwardDiagonal, uint32_t mask);

    // Static lookup array. possibleNumbersArray[k] contains exactly those numbers b for which bit b of k is a 1
    static std::vector<uint8_t> possibleNumbersArray[1 << N];

    // Mask indicating which columns are unoccupied
    uint32_t m_freeColumnBitMask = (1u << N) - 1u;

    // Mask indicating which upward diagonals are unoccupied
    uint32_t m_freeUpwardDiagonals = (1u << N) - 1u;

    // Mask indicating which downward diagonals are unoccupied
    uint32_t m_freeDownwardDiagonals = (1u << N) - 1u;
};

#include "PartialBoard.hxx"

#endif // NQUEEN_PARTIALBOARD_H
