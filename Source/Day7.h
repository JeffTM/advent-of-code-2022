#pragma once

#include <iostream>
#include <unordered_map>

#include "Utils.h"

namespace Day7
{
    inline void PathPopBack(std::string& Path)
    {
        if (Path.size() == 0)
        {
            return;
        }

        if (Path.back() == '/')
        {
            Path.pop_back();
        }

        while (Path.size() > 0 && Path.back() != '/')
        {
            Path.pop_back();
        }
    }

    inline std::unordered_map<std::string, uint32_t> GetFileSizes(const char* InputFileName)
    {
        std::unordered_map<std::string, uint32_t> FileSizes;

        std::string CurrentWorkingDirectory;

        bool bIsInLSMode = false; //remove??

        ForEachFileLine(InputFileName, [&](const std::string& InputLine)
        {
            if (InputLine.starts_with("$ cd"))
            {
                bIsInLSMode = false; //remove??

                if (InputLine == "$ cd /")
                {
                    CurrentWorkingDirectory = '/';
                }
                else if (InputLine == "$ cd ..")
                {
                    PathPopBack(CurrentWorkingDirectory);
                }
                else
                {
                    const std::string DirectoryName = InputLine.substr(5); // remove "$ cd" and a space

                    CurrentWorkingDirectory += DirectoryName;
                    CurrentWorkingDirectory += '/';
                }
            }
            else if (InputLine == "$ ls")
            {
                bIsInLSMode = true; //remove??
            }
            else if (bIsInLSMode)
            {
                if (!InputLine.starts_with("dir "))
                {
                    const StringSplitSingleResult FileSplit = StringSplitSingle(InputLine, " ");

                    const std::string FullFileName = CurrentWorkingDirectory + std::string(FileSplit.Second);

                    FileSizes[FullFileName] = std::stol(std::string(FileSplit.First));
                }
            }
        });

        return FileSizes;
    }

    inline std::unordered_map<std::string, uint32_t> GetDirectorySizes(const char* InputFileName)
    {
        std::unordered_map<std::string, uint32_t> DirectorySizes;

        for (const std::pair<const std::string, uint32_t>& File : GetFileSizes(InputFileName))
        {
            std::string DirectoryName = File.first;
            PathPopBack(DirectoryName); // Get rid of the file name

            while (DirectoryName.size() > 0)
            {
                DirectorySizes[DirectoryName] += File.second;

                PathPopBack(DirectoryName);
            }
        }

        return DirectorySizes;
    }

    inline void Part1()
    {
        uint32_t Answer = 0;

        for (const std::pair<const std::string, uint32_t>& DirectorySize : GetDirectorySizes("Inputs/day7.txt"))
        {
            if (DirectorySize.second <= 100000)
            {
                //std::cout << DirectorySize.first << ": " << DirectorySize.second << std::endl;

                Answer += DirectorySize.second;
            }
        }

        std::cout << "Part 1: " << Answer << std::endl;
    }

    inline void Part2()
    {
        constexpr uint32_t TotalSpaceAvailable   = 70000000; 
        constexpr uint32_t UpdateFreeSpaceNeeded = 30000000;

        std::unordered_map<std::string, uint32_t> DirectorySizes = GetDirectorySizes("Inputs/day7.txt");

        const uint32_t FreeSpace                 = TotalSpaceAvailable - DirectorySizes["/"];
        const uint32_t AdditionalFreeSpaceNeeded = UpdateFreeSpaceNeeded - FreeSpace;

        //std::cout << "Additional free space needed: " << AdditionalFreeSpaceNeeded << std::endl;

        uint32_t Answer = std::numeric_limits<uint32_t>::max();

        //std::string AnswerDirectoryName;

        for (const std::pair<const std::string, uint32_t>& DirectorySize : DirectorySizes)
        {
            //std::cout << "Considering " << DirectorySize.first << ": " << DirectorySize.second;

            if (DirectorySize.second < Answer && DirectorySize.second >= AdditionalFreeSpaceNeeded)
            {
                //std::cout << " <- new best";

                Answer = DirectorySize.second;

                //AnswerDirectoryName = DirectorySize.first;
            }

            //std::cout << std::endl;
        }

        //std::cout << "Part 2: " << Answer << " (" << AnswerDirectoryName << ')' << std::endl;
        std::cout << "Part 2: " << Answer << std::endl;
    }
}
