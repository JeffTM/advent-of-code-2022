#pragma once

#include <algorithm>
#include <iostream>
#include <numeric>

#include "Utils.h"

namespace Day2
{
    inline int ScoreRoundPart1(char Opponent, char Me)
    {
        switch(Opponent)
        {
            case 'A':
                switch(Me)
                {
                    case 'X': return 3 + 1;
                    case 'Y': return 6 + 2;
                    case 'Z': return 0 + 3;
                }
            case 'B':
                switch(Me)
                {
                    case 'X': return 0 + 1;
                    case 'Y': return 3 + 2;
                    case 'Z': return 6 + 3;
                }
            case 'C':
                switch(Me)
                {
                    case 'X': return 6 + 1;
                    case 'Y': return 0 + 2;
                    case 'Z': return 3 + 3;
                }
        }

        std::cout << "Error: one or both letters is invalid: " << Opponent << ' ' << Me << std::endl;

        return 0;
    }

    inline int ScoreRoundPart2(char Opponent, char Me)
    {
        switch(Opponent)
        {
            case 'A':
                switch(Me)
                {
                    case 'X': return 0 + 3;
                    case 'Y': return 3 + 1;
                    case 'Z': return 6 + 2;
                }
            case 'B':
                switch(Me)
                {
                    case 'X': return 0 + 1;
                    case 'Y': return 3 + 2;
                    case 'Z': return 6 + 3;
                }
            case 'C':
                switch(Me)
                {
                    case 'X': return 0 + 2;
                    case 'Y': return 3 + 3;
                    case 'Z': return 6 + 1;
                }
        }

        return 0;
    }

    inline int CalculateTotalScore(std::function<int(char, char)> ScoreFunc)
    {
        int TotalScore = 0;

        const bool bFileReadError = !ForEachFileLine("Inputs/day2.txt", [&TotalScore, ScoreFunc](const std::string& Line)
        {
            const int RoundScore = ScoreFunc(Line[0], Line[2]);
            TotalScore += RoundScore;
            //std::cout << Line << " = " << RoundScore << std::endl;
        });

        if (bFileReadError)
        {
            std::cout << "Error: could not read file" << std::endl;
        }

        return TotalScore;
    }

    inline void Part1()
    {
        std::cout << "Part 1 score: " << CalculateTotalScore(ScoreRoundPart1) << std::endl;
    }

    inline void Part2()
    {
        std::cout << "Part 2 score: " << CalculateTotalScore(ScoreRoundPart2) << std::endl;
    }
}
