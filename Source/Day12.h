#pragma once

#include <algorithm>
#include <iostream>
#include <queue>

#include "Utils.h"

namespace Day12
{
    struct PathNode
    {
        PathNode()
            : Height(0), GScore(std::numeric_limits<int16_t>::max()), FScore(std::numeric_limits<int16_t>::max()), CameFromIndex(-1)
        {}

        explicit PathNode(int8_t InHeight)
            : Height(InHeight), GScore(std::numeric_limits<int16_t>::max()), FScore(std::numeric_limits<int16_t>::max()), CameFromIndex(-1)
        {}

        int8_t Height;
        int16_t GScore;
        int16_t FScore;
        int16_t CameFromIndex;
    };

    inline void GetInput(Matrix2D<PathNode>& OutMap, int16_t& OutStartIndex, int16_t& OutEndIndex)
    {
        OutMap.Clear();
        OutStartIndex = -1;
        OutEndIndex = -1;

        std::string InputText;

        if (!TryReadWholeFile("Inputs/Day12.txt", InputText))
        {
            return;
        }

        OutMap.SetDimensioner(InputText.find('\n'));

        int16_t ValuesAppended = 0;

        for (char InputChar : InputText)
        {
            if (InputChar >= 'a' && InputChar <= 'z')
            {
                OutMap.Append(PathNode(InputChar - 'a'));
                ++ValuesAppended;
            }
            else if (InputChar == 'S')
            {
                OutStartIndex = ValuesAppended;
                OutMap.Append(PathNode(0));
                ++ValuesAppended;
            }
            else if (InputChar == 'E')
            {
                OutEndIndex = ValuesAppended;
                OutMap.Append(PathNode(25));
                ++ValuesAppended;
            }

            // Indexes are limited in size to save a bunch of memory. Ignore any input that would add move points than we can handle
            if (ValuesAppended == std::numeric_limits<int16_t>::max())
            {
                return;
            }
        }
    }

    inline int16_t ManhattanDistance(const Matrix2D<PathNode>& Map, int16_t FromIndex, int16_t ToIndex)
    {
        int64_t FromRow, FromCol, ToRow, ToCol;
        Map.IndexToRowCol(FromIndex, FromRow, FromCol);
        Map.IndexToRowCol(ToIndex, ToRow, ToCol);

        return llabs(ToRow - FromRow) + llabs(ToCol - FromCol);
    }

    inline bool CanClimbNeighbor(const Matrix2D<PathNode>& Map, int8_t PointHeight, int16_t NeighborRow, int16_t NeighborCol, bool bReverse)
    {
        if (!Map.IsValidRowCol(NeighborRow, NeighborCol))
        {
            return false;
        }

        int8_t HeightDelta = Map.Get(NeighborRow, NeighborCol).Height - PointHeight;

        if (bReverse)
        {
            HeightDelta *= -1;
        }

        return HeightDelta <= 1;
    }

    inline std::vector<int16_t> GetNeighbors(const Matrix2D<PathNode>& Map, int16_t PointIndex, bool bReverse)
    {
        std::vector<int16_t> Neighbors;
        Neighbors.reserve(4);

        int8_t Height = Map.Get(PointIndex).Height;

        int64_t Row, Col;
        Map.IndexToRowCol(PointIndex, Row, Col);

        if (CanClimbNeighbor(Map, Height, Row + 1, Col, bReverse))
        {
            Neighbors.push_back(Map.RowColToIndex(Row + 1, Col));
        }
        if (CanClimbNeighbor(Map, Height, Row - 1, Col, bReverse))
        {
            Neighbors.push_back(Map.RowColToIndex(Row - 1, Col));
        }
        if (CanClimbNeighbor(Map, Height, Row, Col + 1, bReverse))
        {
            Neighbors.push_back(Map.RowColToIndex(Row, Col + 1));
        }
        if (CanClimbNeighbor(Map, Height, Row, Col - 1, bReverse))
        {
            Neighbors.push_back(Map.RowColToIndex(Row, Col - 1));
        }

        return Neighbors;
    }

    inline int16_t AStarDistance(Matrix2D<PathNode>& Map, int16_t StartIndex, int16_t EndIndex)
    {
        std::vector<int16_t> OpenHeap;

        OpenHeap.push_back(StartIndex);

        Map.Get(StartIndex).GScore = 0;
        Map.Get(StartIndex).FScore = ManhattanDistance(Map, StartIndex, EndIndex);

        auto FScoreGreaterThan = [&Map](int16_t First, int16_t Second) -> bool
        {
            return Map.Get(First).FScore > Map.Get(Second).FScore;
        };

        while (!OpenHeap.empty())
        {
            std::pop_heap(OpenHeap.begin(), OpenHeap.end(), FScoreGreaterThan);
            int16_t CurrentIndex = OpenHeap.back();
            OpenHeap.pop_back();

            PathNode& Current = Map.Get(CurrentIndex);

            if (CurrentIndex == EndIndex)
            {
                /*
                while (CurrentIndex >= 0)
                {
                    int64_t Row, Col;
                    Map.IndexToRowCol(CurrentIndex, Row, Col);

                    std::cout << '(' << Row << ", " << Col << ')' << std::endl;

                    CurrentIndex = Map.Get(CurrentIndex).CameFromIndex;
                }
                */

                return Current.GScore;
            }

            for (int16_t NeighborIndex : GetNeighbors(Map, CurrentIndex, false))
            {
                PathNode& Neighbor = Map.Get(NeighborIndex);
                int16_t TentativeGScore = Current.GScore + 1;

                if (TentativeGScore < Neighbor.GScore)
                {
                    Neighbor.CameFromIndex = CurrentIndex;
                    Neighbor.GScore = TentativeGScore;
                    Neighbor.FScore = TentativeGScore + ManhattanDistance(Map, CurrentIndex, NeighborIndex);

                    // Because the heuristic is admissable and consistent
                    // we do not have to worry about adding a duplicate
                    OpenHeap.push_back(NeighborIndex);
                    std::push_heap(OpenHeap.begin(), OpenHeap.end(), FScoreGreaterThan);
                }
            }
        }

        return std::numeric_limits<int16_t>::max();
    }

    // Faster than just using the above AStar algorithm on each 0 elevation by about 20 ms
    inline void BFSAllToEnd(Matrix2D<PathNode>& Map, int16_t EndIndex)
    {
        std::queue<int16_t> OpenQueue;

        OpenQueue.push(EndIndex);

        Map.Get(EndIndex).GScore = 0;
        Map.Get(EndIndex).FScore = 0;

        while (!OpenQueue.empty())
        {
            int16_t CurrentIndex = OpenQueue.front();
            OpenQueue.pop();

            PathNode& Current = Map.Get(CurrentIndex);

            for (int16_t NeighborIndex : GetNeighbors(Map, CurrentIndex, true))
            {
                PathNode& Neighbor = Map.Get(NeighborIndex);
                int16_t TentativeGScore = Current.GScore + 1;

                if (TentativeGScore < Neighbor.GScore)
                {
                    Neighbor.CameFromIndex = CurrentIndex;
                    Neighbor.GScore = TentativeGScore;
                    Neighbor.FScore = TentativeGScore;

                    OpenQueue.push(NeighborIndex);
                }
            }
        }
    }

    inline void Part1()
    {
        Matrix2D<PathNode> Map;
        int16_t StartIndex, EndIndex;

        GetInput(Map, StartIndex, EndIndex);

        std::cout << "Part 1: " << AStarDistance(Map, StartIndex, EndIndex) << std::endl;
    }

    inline void Part2()
    {
        Matrix2D<PathNode> Map;
        int16_t StartIndex, EndIndex;

        // Just ignoring StartIndex is easier than writing a whole new function that doesn't take it
        GetInput(Map, StartIndex, EndIndex);

        BFSAllToEnd(Map, EndIndex);

        int16_t MinDistance = std::numeric_limits<int16_t>::max();

        for (StartIndex = 0; StartIndex < Map.GetTotalSize(); ++StartIndex)
        {
            if (Map.Get(StartIndex).Height == 0)
            {
                const int16_t Distance = Map.Get(StartIndex).FScore;

                if (Distance < MinDistance)
                {
                    MinDistance = Distance;
                }
            }
        }

        std::cout << "Part 2: " << MinDistance << std::endl;
    }
}
