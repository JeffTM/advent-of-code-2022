#pragma once

#include <algorithm>
#include <iostream>

#include "Utils.h"

namespace Day12
{
    struct FPoint
    {
        FPoint()
            : Height(0), GScore(std::numeric_limits<int16_t>::max()), FScore(std::numeric_limits<int16_t>::max())
        {}

        explicit FPoint(int16_t InHeight)
            : Height(InHeight), GScore(std::numeric_limits<int16_t>::max()), FScore(std::numeric_limits<int16_t>::max())
        {}

        friend std::ostream& operator<<(std::ostream& OutStream, const FPoint& Point)
        {
            OutStream << Point.Height;
            return OutStream;
        }

        int16_t Height;
        int16_t GScore;
        int16_t FScore;
    };

    inline void GetInput(Matrix2D<FPoint>& OutMap, int32_t& OutStartRow, int32_t& OutStartCol, int32_t& OutEndRow, int32_t& OutEndCol)
    {
        OutMap.Clear();
        OutStartRow = -1;
        OutStartCol = -1;
        OutEndRow = -1;
        OutEndCol = -1;

        std::string InputText;

        if (!TryReadWholeFile("Inputs/Day12.txt", InputText))
        {
            return;
        }

        OutMap.SetDimensioner(InputText.find('\n'));

        int64_t ValuesAppended = 0;

        for (char InputChar : InputText)
        {
            if (InputChar >= 'a' && InputChar <= 'z')
            {
                OutMap.Append(FPoint(InputChar - 'a'));
                ++ValuesAppended;
            }
            else if (InputChar == 'S')
            {
                OutStartRow = ValuesAppended % OutMap.GetDimensioner();
                OutStartCol = ValuesAppended / OutMap.GetDimensioner();

                OutMap.Append(FPoint(0));
                ++ValuesAppended;
            }
            else if (InputChar == 'E')
            {
                OutEndRow = ValuesAppended % OutMap.GetDimensioner();
                OutEndCol = ValuesAppended / OutMap.GetDimensioner();

                OutMap.Append(FPoint(25));
                ++ValuesAppended;
            }
        }
    }

    inline void Part1()
    {
        Matrix2D<FPoint> Map;
        int32_t StartRow;
        int32_t StartCol;
        int32_t EndRow;
        int32_t EndCol;

        GetInput(Map, StartRow, StartCol, EndRow, EndCol);

        std::cout << Map << std::endl;
        std::cout << '(' << StartRow << ", " << StartCol << ") (" << EndRow << ", " << EndCol << ')' << std::endl;
        std::cout << "Part 1: " << "WIP" << std::endl;
    }

    inline void Part2()
    {
        std::cout << "Part 2: " << "WIP" << std::endl;
    }
}
