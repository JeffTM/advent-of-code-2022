#pragma once

#include <iostream>
#include <unordered_set>

#include "Utils.h"

namespace Day10
{
    inline void UpdatePart1Answer(int CycleCounter, int Register, long long& Answer)
    {
        if (CycleCounter % 40 == 20)
        {
            Answer += CycleCounter * Register;
            //std::cout << CycleCounter << "th * " << Register << " = " << CycleCounter * Register << std::endl;
        }
    }

    inline void Part1()
    {
        long long Answer = 0;

        int CycleCounter = 1;
        int Register     = 1;

        ForEachFileLine("Inputs/day10.txt", [&Answer, &CycleCounter, &Register](const std::string& FileLine)
        {
            if (FileLine.starts_with("addx"))
            {
                UpdatePart1Answer(CycleCounter, Register, Answer);
                ++CycleCounter;

                UpdatePart1Answer(CycleCounter, Register, Answer);
                Register += std::stoi(FileLine.substr(5));
                ++CycleCounter;
            }
            else
            {
                UpdatePart1Answer(CycleCounter, Register, Answer);
                ++CycleCounter;
            }
        });

        std::cout << "Part 1: " << Answer << std::endl;
    }

    inline void UpdatePart2Answer(int CycleCounter, int Register, std::string& Answer)
    {
        const int LineIndex   = (CycleCounter - 1) % 40;
        const int SpriteStart = Register - 1;
        const int SpriteEnd   = Register + 1;

        Answer += (LineIndex >= SpriteStart && LineIndex <= SpriteEnd) ? '#' : '.';

        if (LineIndex + 1 == 40) // Equivalent to if (CycleCounter % 40 == 0)
        {
            Answer += '\n';
        }
    }

    inline void Part2()
    {
        std::string Answer;
        Answer.reserve(256);

        int CycleCounter = 1;
        int Register     = 1;

        ForEachFileLine("Inputs/day10.txt", [&Answer, &CycleCounter, &Register](const std::string& FileLine)
        {
            if (FileLine.starts_with("addx"))
            {
                UpdatePart2Answer(CycleCounter, Register, Answer);
                ++CycleCounter;

                UpdatePart2Answer(CycleCounter, Register, Answer);
                Register += std::stoi(FileLine.substr(5));
                ++CycleCounter;
            }
            else
            {
                UpdatePart2Answer(CycleCounter, Register, Answer);
                ++CycleCounter;
            }
        });

        std::cout << "Part 2:\n" << Answer << std::flush;
    }
}
