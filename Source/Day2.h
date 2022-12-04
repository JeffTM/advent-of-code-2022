#pragma once

#include <algorithm>
#include <iostream>
#include <numeric>

#include "Utils.h"

namespace Day2
{
    inline int8_t ScoreRoundResultPart1(int8_t OpponentHandIndex, int8_t MyHandIndex)
    {
        int8_t Delta = MyHandIndex - OpponentHandIndex;

        // -2, -1, 0, 1, 2 -> win, loss, draw, win, loss -> 6, 0, 3, 6, 0 (I made a table)
        // To avoid modulus consider 0 to be a draw (3), -2 and 1 to be a win (6), and anything else (including bad parameters) to be a loss (0)
        return Delta == 0 ? 3 : Delta == -2 || Delta == 1 ? 6 : 0;
    }

    inline int8_t ScoreRoundPart1(char Opponent, char Me)
    {
        const int8_t OpponentHandIndex = static_cast<int8_t>(Opponent - 'A');
        const int8_t MyHandIndex       = static_cast<int8_t>(Me - 'X');

        // 0, 1, 2 -> rock, paper, scissors -> 1, 2, 3 and bad input is just whatever
        const int8_t MyHandScore = MyHandIndex + 1;

        return MyHandScore + ScoreRoundResultPart1(OpponentHandIndex, MyHandIndex);
    }

    inline int8_t ScoreMyHandPart2(int8_t OpponentHandIndex, int8_t MatchResultIndex)
    {
        int8_t Sum = MatchResultIndex + OpponentHandIndex;

        // 0, 1, 2, 3, 4 -> scissors, rock, paper, scissors, rock -> 3, 1, 2, 3, 1 (I made a table)
        // To avoid modulus consider 2 to be a paper (2), 0 and 3 to be scissors (3), and anything else (including bad parameters) to be rock (1)
        return Sum == 2 ? 2 : Sum == 0 || Sum == 3 ? 3 : 1;
    }

    inline int8_t ScoreRoundPart2(char Opponent, char MatchResult)
    {
        const int8_t OpponentHandIndex = static_cast<int8_t>(Opponent - 'A');
        const int8_t MatchResultIndex  = static_cast<int8_t>(MatchResult - 'X');

        // 0, 1, 2 -> loss, draw, win -> 0, 3, 6 and bad input is just whatever
        const int8_t MatchScore = MatchResultIndex * 3;

        return MatchScore + ScoreMyHandPart2(OpponentHandIndex, MatchResultIndex);
    }

    inline int CalculateTotalScore(std::function<int8_t(char, char)> ScoreFunc)
    {
        int32_t TotalScore = 0;

        const bool bFileReadError = !ForEachFileLine("Inputs/day2.txt", [&TotalScore, ScoreFunc](const std::string& Line)
        {
            const int8_t RoundScore = ScoreFunc(Line[0], Line[2]);
            TotalScore += RoundScore;

            //std::cout << Line << " = " << static_cast<int32_t>(RoundScore) << std::endl;
        });

        if (bFileReadError)
        {
            std::cout << "Error: could not read file" << std::endl;
        }

        return TotalScore;
    }

    inline void Part1()
    {
        std::cout << "Part 1: " << CalculateTotalScore(ScoreRoundPart1) << std::endl;
    }

    inline void Part2()
    {
        std::cout << "Part 2: " << CalculateTotalScore(ScoreRoundPart2) << std::endl;
    }
}
