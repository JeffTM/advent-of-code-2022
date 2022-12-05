#pragma once

#include <iostream>

#include "Utils.h"

namespace Day5
{
    using ContainerStackType = std::vector<char>;

    struct MoveInstruction
    {
        uint16_t Count;
        uint16_t FromStackIndex;
        uint16_t ToStackIndex;

        MoveInstruction()
            : Count(0), FromStackIndex(0), ToStackIndex(0)
        {}

        friend std::ostream& operator<<(std::ostream& OutStream, const MoveInstruction& MovIns)
        {
            return OutStream << "(move " << MovIns.Count << " from " << MovIns.FromStackIndex << " to " << MovIns.ToStackIndex << ')';
        }
    };

    std::vector<ContainerStackType> ParseContainers(std::string_view ContainersInput)
    {
        std::vector<std::string_view> Lines = StringSplit(ContainersInput, "\n");
        std::size_t LineLength = Lines[0].size();
        std::size_t NumStacks = (LineLength + 1) / 4;

        std::vector<ContainerStackType> ContainerStacks(NumStacks);

        for (auto it = Lines.rbegin(); it != Lines.rend(); ++it)
        {
            for (std::size_t i = 1; i < LineLength; i += 4)
            {
                if (std::isupper(it->at(i)))
                {
                    ContainerStacks[(i - 1) / 4].push_back(it->at(i));
                }
            }
        }

        return ContainerStacks;
    }

    std::vector<MoveInstruction> ParseMoveInstructions(std::string_view MoveInstructionInput)
    {
        std::vector<MoveInstruction> MoveInstructions;

        ForEachStringSplit(MoveInstructionInput, "\n", [&MoveInstructions](std::string_view Line)
        {
            MoveInstructions.push_back(MoveInstruction());

            Line.remove_prefix(5); // Get rid of "move "

            auto CountSplit = StringSplitSingle(Line, " from ");

            MoveInstructions.back().Count = std::stoi(std::string(CountSplit.First));

            auto FromToSplit = StringSplitSingle(CountSplit.Second, " to ");

            MoveInstructions.back().FromStackIndex = std::stoi(std::string(FromToSplit.First)) - 1;
            MoveInstructions.back().ToStackIndex   = std::stoi(std::string(FromToSplit.Second)) - 1;
        });

        return MoveInstructions;
    }

    void ParseInput(std::vector<ContainerStackType>& ContainerStacks, std::vector<MoveInstruction>& MoveInstructions)
    {
        std::string Input;
        TryReadWholeFile("Inputs/day5.txt", Input);

        StringSplitSingleResult InputSplit = StringSplitSingle(Input, "\n\n");

        ContainerStacks  = ParseContainers(InputSplit.First);
        MoveInstructions = ParseMoveInstructions(InputSplit.Second);

        /*
        std::cout << "Stack bottom-top: ";
        for (const ContainerStackType& Stack : ContainerStacks)
        {
            std::cout << Stack.front() << '-' << Stack.back() << ' ';
        }
        std::cout << std::endl;

        std::cout << "First instruction: " << MoveInstructions.front() << " last instruction: " << MoveInstructions.back() << std::endl;
        */
    }

    inline std::string RunSimulation(std::function<void(ContainerStackType&, ContainerStackType&, uint16_t)> CraneFunction)
    {
        std::vector<ContainerStackType> ContainerStacks;
        std::vector<MoveInstruction>    MoveInstructions;

        ParseInput(ContainerStacks, MoveInstructions);

        for (const MoveInstruction& Instruction : MoveInstructions)
        {
            ContainerStackType& FromStack = ContainerStacks[Instruction.FromStackIndex];
            ContainerStackType& ToStack   = ContainerStacks[Instruction.ToStackIndex];

            CraneFunction(FromStack, ToStack, Instruction.Count);
        }

        std::string StackTops("\"");
        StackTops.reserve(ContainerStacks.size() + 2);
        for (const ContainerStackType& Stack : ContainerStacks)
        {
            StackTops += Stack.back();
        }
        StackTops += '\"';

        return StackTops;
    }

    inline void CrateMover9000(ContainerStackType& FromStack, ContainerStackType& ToStack, uint16_t Count)
    {
        ToStack.insert(ToStack.end(), FromStack.rbegin(), FromStack.rbegin() + Count);
        FromStack.erase(FromStack.end() - Count, FromStack.end());
    }

    inline void CrateMover9001(ContainerStackType& FromStack, ContainerStackType& ToStack, uint16_t Count)
    {
        ToStack.insert(ToStack.end(), FromStack.end() - Count, FromStack.end());
        FromStack.erase(FromStack.end() - Count, FromStack.end());
    }

    inline void Part1()
    {
        std::cout << "Part 1: " << RunSimulation(CrateMover9000) << std::endl;
    }

    inline void Part2()
    {
        std::cout << "Part 2: " << RunSimulation(CrateMover9001) << std::endl;
    }
}
