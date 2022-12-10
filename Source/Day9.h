#pragma once

#include <iostream>
#include <unordered_set>

#include "Utils.h"

namespace Day9
{
    using CoordType  = int32_t;
    using VectorType = Vector2<CoordType>;

    inline VectorType DirectionCodeToVector(char DirectionCode)
    {
        switch (DirectionCode)
        {
            case 'R': return VectorType(1, 0);
            case 'U': return VectorType(0, 1);
            case 'L': return VectorType(-1, 0);
            case 'D': return VectorType(0, -1);
        }

        return VectorType();
    }

    inline void SimulateMove(const VectorType& MoveDirection, std::vector<VectorType>& Rope)
    {
        Rope.front() += MoveDirection;

        for (std::size_t RopeIndex = 1; RopeIndex < Rope.size(); ++RopeIndex)
        {
            const VectorType Delta       = Rope[RopeIndex - 1] - Rope[RopeIndex];
            const CoordType  DeltaSizeSq = Delta.SizeSquared();

            if (DeltaSizeSq >= 4)
            {
                Rope[RopeIndex] += (Delta + Delta.Signum()) / 2;
            }
            else
            {
                return;
            }
        }
    }

    inline std::size_t RunSimulation(const char* FileName, int RopeLength)
    {
        if (RopeLength <= 0)
        {
            return 0;
        }

        std::vector<VectorType> Rope(RopeLength);

        std::unordered_set<VectorType, VectorType::Hash> TailVisited;

        TailVisited.insert(VectorType());

        ForEachFileLine(FileName, [&Rope, &TailVisited](const std::string& FileLine)
        {
            const VectorType MoveDirection = DirectionCodeToVector(FileLine[0]);
            const int        NumMoves      = std::stoi(FileLine.substr(2));

            for (int MoveCounter = 0; MoveCounter < NumMoves; ++MoveCounter)
            {
                SimulateMove(MoveDirection, Rope);
                TailVisited.insert(Rope.back());
            }
        });

        return TailVisited.size();
    }

    inline void Part1()
    {
        std::cout << "Part 1: " << RunSimulation("Inputs/day9.txt", 2) << std::endl;
    }

    inline void Part2()
    {
        std::cout << "Part 2: " << RunSimulation("Inputs/day9.txt", 10) << std::endl;
    }
}
