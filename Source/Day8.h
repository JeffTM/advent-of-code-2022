#pragma once

#include <iostream>

#include "Utils.h"

namespace Day8
{
    using IndexType = Matrix2D<uint8_t>::IndexType;

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

    inline bool IsTreeVisible(const Matrix2D<uint8_t>& Trees, IndexType Row, IndexType Col)
    {
        const uint8_t CurrentTreeHeight = Trees.Get(Row, Col);

        if (Row == 0 || Col == 0 || Row == Trees.GetRowSize() - 1 || Col == Trees.GetColSize() - 1)
        {
            return true;
        }

        // Scan right
        bool bRightHit = false;

        for (IndexType i = Row + 1; i < Trees.GetRowSize(); ++i)
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

        for (IndexType i = Col + 1; i < Trees.GetColSize(); ++i)
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

        for (IndexType i = Row - 1; i >= 0; --i)
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

        for (IndexType i = Col - 1; i >= 0; --i)
        {
            if (Trees.Get(Row, i) >= CurrentTreeHeight)
            {
                bUpHit = true;
                break;
            }
        }

        return !bUpHit;
    }

    inline IndexType TreeScenicScore(const Matrix2D<uint8_t>& Trees, IndexType Row, IndexType Col)
    {
        const uint8_t CurrentTreeHeight = Trees.Get(Row, Col);

        // Scan right
        IndexType RightScore = 1;

        while (Row + RightScore < Trees.GetRowSize() - 1 && Trees.Get(Row + RightScore, Col) < CurrentTreeHeight)
        {
            ++RightScore;
        }

        // Scan down
        IndexType DownScore = 1;

        while (Col + DownScore < Trees.GetColSize() - 1 && Trees.Get(Row, Col + DownScore) < CurrentTreeHeight)
        {
            ++DownScore;
        }

        // Scan left
        IndexType LeftScore = 1;

        while (Row - LeftScore != 0 && Trees.Get(Row - LeftScore, Col) < CurrentTreeHeight)
        {
            ++LeftScore;
        }

        // Scan up
        IndexType UpScore = 1;

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

        for (IndexType Col = 0; Col < Trees.GetRowSize(); ++Col)
        {
            for (IndexType Row = 0; Row < Trees.GetRowSize(); ++Row)
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

        IndexType Answer = 0;

        //IndexType AnswerRow = 0;
        //IndexType AnswerCol = 0;

        for (IndexType Col = 1; Col < Trees.GetRowSize() - 1; ++Col)
        {
            for (IndexType Row = 1; Row < Trees.GetRowSize() - 1; ++Row)
            {
                IndexType Score = TreeScenicScore(Trees, Row, Col);

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
