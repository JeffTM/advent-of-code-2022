#pragma once

#include <iostream>

#include "Utils.h"

namespace Day13
{
    bool IsRightOrder(std::string_view Left, std::string_view Right)
    {
        
    }

    inline void Part1()
    {
        std::string InputText;
        TryReadWholeFile("Inputs/day13.txt", InputText);

        std::vector<std::string_view> Pairs = StringSplit(InputText, "\n\n");

        size_t IndexSum = 0;

        for (size_t i = 0; i < Pairs.size(); ++i)
        {
            StringSplitSingleResult PairSplit = StringSplitSingle(Pairs[i], "\n");
            if (IsRightOrder(PairSplit.first, PairSplit.second))
            {
                IndexSum += (i + 1);
            }
        }

        std::cout << "Part 1: " << "WIP" << std::endl;
    }

    inline void Part2()
    {
        std::cout << "Part 2: " << "WIP" << std::endl;
    }
}
