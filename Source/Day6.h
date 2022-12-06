#pragma once

#include <bitset>
#include <iostream>

#include "Utils.h"

namespace Day6
{
    inline uint8_t CharIndex(char Char)
    {
        return Char - 'a';
    }

    inline std::size_t UniqueScan(uint8_t WindowWidth)
    {
        //std::string Input = "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg"; // For this expected is Part 1: 10 and Part 2: 29
        std::string Input;
        TryReadWholeFile("Inputs/day6.txt", Input);

        while (std::isspace(Input.back()))
        {
            Input.pop_back();
        }

        uint8_t CharCounts[26] = {0};
        uint8_t CharCountsEqualTo1 = 0;

        for (std::size_t i = 0; i < WindowWidth; ++i)
        {
             const uint8_t EnteringCharIndex = CharIndex(Input[i]);

            if (CharCounts[EnteringCharIndex] == 1)
            {
                --CharCountsEqualTo1;
            }

            ++CharCounts[EnteringCharIndex];

            if (CharCounts[EnteringCharIndex] == 1)
            {
                ++CharCountsEqualTo1;
            }
        }

        for (std::size_t i = WindowWidth; i < Input.size(); ++i)
        {
            if (CharCountsEqualTo1 == WindowWidth)
            {
                return i;
            }

            const uint8_t EnteringCharIndex = CharIndex(Input[i]);

            if (CharCounts[EnteringCharIndex] == 1)
            {
                --CharCountsEqualTo1;
            }

            ++CharCounts[EnteringCharIndex];

            if (CharCounts[EnteringCharIndex] == 1)
            {
                ++CharCountsEqualTo1;
            }

            const uint8_t ExitingCharIndex = CharIndex(Input[i - WindowWidth]);

            if (CharCounts[ExitingCharIndex] == 1)
            {
                --CharCountsEqualTo1;
            }

            --CharCounts[ExitingCharIndex];

            if (CharCounts[ExitingCharIndex] == 1)
            {
                ++CharCountsEqualTo1;
            }
        }

        return std::numeric_limits<std::size_t>::max();
    }

    inline void Part1()
    {
        std::cout << "Part 1: " << UniqueScan(4) << std::endl;
    }

    inline void Part2()
    {
        std::cout << "Part 2: " << UniqueScan(14) << std::endl;
    }
}
