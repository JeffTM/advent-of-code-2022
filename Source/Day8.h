#pragma once

#include <iostream>

#include "Utils.h"

namespace Day8
{
    inline Matrix2D<uint8_t> GetInput(const char* FileName)
    {
        std::string FileText;
        TryReadWholeFile(FileName, FileText);

        std::size_t FirstNewlineOffset = FileText.find('\n');

        Matrix2D<uint8_t> Input(FirstNewlineOffset == std::string::npos ? 0 : FirstNewlineOffset);

        for (auto Char : FileText)
        {
            if (Char >= '0' && Char <= '9')
            {
                Input.Append(static_cast<uint8_t>(Char - '0'));
            }
        }

        return Input;
    }

    inline bool IsTreeVisible(const Matrix2D<uint8_t>& Trees, std::size_t Row, std::size_t Col)
    {
        const uint8_t CurrentTreeHeight = Trees.Get(Row, Col);

        if (Row == 0 || Col == 0 || Row == Trees.GetRowSize() - 1 || Col == Trees.GetColSize() - 1)
        {
            return true;
        }

        // Scan right
        bool bRightHit = false;

        for (std::size_t i = Row + 1; i < Trees.GetRowSize(); ++i)
        {
            if (Trees.Get(i, Col) >= CurrentTreeHeight)
            {
                bRightHit = true;
                break;
            }
        }

        if (!bRightHit)
        {
            return true;
        }

        // Scan down
        bool bDownHit = false;

        for (std::size_t i = Col + 1; i < Trees.GetColSize(); ++i)
        {
            if (Trees.Get(Row, i) >= CurrentTreeHeight)
            {
                bDownHit = true;
                break;
            }
        }

        if (!bDownHit)
        {
            return true;
        }

        // Scan left
        bool bLeftHit = false;

        for (std::size_t i = Row - 1; i != std::numeric_limits<std::size_t>::max(); --i)
        {
            if (Trees.Get(i, Col) >= CurrentTreeHeight)
            {
                bLeftHit = true;
                break;
            }
        }

        if (!bLeftHit)
        {
            return true;
        }

        // Scan up
        bool bUpHit = false;

        for (std::size_t i = Col - 1; i != std::numeric_limits<std::size_t>::max(); --i)
        {
            if (Trees.Get(Row, i) >= CurrentTreeHeight)
            {
                bUpHit = true;
                break;
            }
        }

        return !bUpHit;
    }

    inline std::size_t TreeScenicScore(const Matrix2D<uint8_t>& Trees, std::size_t Row, std::size_t Col)
    {
        const uint8_t CurrentTreeHeight = Trees.Get(Row, Col);

        // Scan right
        std::size_t RightScore = 1;

        while (Row + RightScore < Trees.GetRowSize() - 1 && Trees.Get(Row + RightScore, Col) < CurrentTreeHeight)
        {
            ++RightScore;
        }

        // Scan down
        std::size_t DownScore = 1;

        while (Col + DownScore < Trees.GetColSize() - 1 && Trees.Get(Row, Col + DownScore) < CurrentTreeHeight)
        {
            ++DownScore;
        }

        // Scan left
        std::size_t LeftScore = 1;

        while (Row - LeftScore != 0 && Trees.Get(Row - LeftScore, Col) < CurrentTreeHeight)
        {
            ++LeftScore;
        }

        // Scan up
        std::size_t UpScore = 1;

        while (Col - UpScore != 0 && Trees.Get(Row, Col - UpScore) < CurrentTreeHeight)
        {
            ++UpScore;
        }

        //std::cout << UpScore << ' ' << LeftScore << ' ' << DownScore << ' ' << RightScore << std::endl;

        return RightScore * DownScore * LeftScore * UpScore;
    }

    inline void Part1()
    {
        Matrix2D<uint8_t> Trees = GetInput("Inputs/day8.txt");

        std::size_t Answer = 0;

        for (std::size_t Col = 0; Col < Trees.GetRowSize(); ++Col)
        {
            for (std::size_t Row = 0; Row < Trees.GetRowSize(); ++Row)
            {
                if (IsTreeVisible(Trees, Row, Col))
                {
                    ++Answer;
                    //std::cout << 'V';
                }
                else
                {
                    //std::cout << 'I';
                }
            }
            //std::cout << std::endl;
        }

        std::cout << "Part 1: " << Answer << std::endl;
    }

    inline void Part2()
    {
        Matrix2D<uint8_t> Trees = GetInput("Inputs/day8.txt");

        std::size_t Answer = 0;

        //std::size_t AnswerRow = 0;
        //std::size_t AnswerCol = 0;

        for (std::size_t Col = 1; Col < Trees.GetRowSize() - 1; ++Col)
        {
            for (std::size_t Row = 1; Row < Trees.GetRowSize() - 1; ++Row)
            {
                std::size_t Score = TreeScenicScore(Trees, Row, Col);

                if (Score > Answer)
                {
                    Answer = Score;

                    //AnswerRow = Row;
                    //AnswerCol = Col;
                }

                //std::cout << Score << ' ';
            }
            //std::cout << std::endl;
        }

        //TreeScenicScore(Trees, 2, 3);

        //std::cout << "Part 2: " << Answer << " (" << AnswerRow << ", " << AnswerCol << ')' <<  std::endl;
        std::cout << "Part 2: " << Answer << std::endl;
    }
}
