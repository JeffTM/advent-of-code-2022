#pragma once

#include <algorithm>
#include <iostream>
#include <numeric>

#include "Utils.h"

namespace Day1
{
    inline void Part1()
    {
        //std::string Input = "1000\n2000\n3000\n\n4000\n\n5000\n6000\n\n7000\n8000\n9000\n\n10000";
        std::string Input;
        if (!TryReadWholeFile("Inputs/day1.txt", Input))
        {
            std::cout << "Error: could not read file" << std::endl;

            return;
        }

        int Max = 0;

        ForEachStringSplit(Input, "\n\n", [&Max](std::string_view Elf)
        {
            int Sum = 0;

            ForEachStringSplit(Elf, "\n", [&Sum](std::string_view ElfItem)
            {
                Sum += std::stoi(std::string(ElfItem));
            });

            if (Sum > Max)
            {
                Max = Sum;
            }
        });

        std::cout << "Part 1: " << Max << std::endl;
    }

    inline void Part2()
    {
        //std::string Input = "1000\n2000\n3000\n\n4000\n\n5000\n6000\n\n7000\n8000\n9000\n\n10000";
        std::string Input;
        if (!TryReadWholeFile("Inputs/day1.txt", Input))
        {
            std::cout << "Error: could not read file" << std::endl;

            return;
        }

        std::vector<int> ElfSums;

        ForEachStringSplit(Input, "\n\n", [&ElfSums](std::string_view Elf)
        {
            int Sum = 0;

            ForEachStringSplit(Elf, "\n", [&Sum](std::string_view ElfItem)
            {
                Sum += std::stoi(std::string(ElfItem));
            });

            ElfSums.push_back(Sum);
        });

        if (ElfSums.size() < 3)
        {
            std::cout << "Error: less than 3 total elfs" << std::endl;
        }

        std::partial_sort(ElfSums.begin(), ElfSums.begin() + 3, ElfSums.end(), std::greater());

        std::cout << "Part 2: " << std::accumulate(ElfSums.begin(), ElfSums.begin() + 3, 0) << std::endl;
    }
}
