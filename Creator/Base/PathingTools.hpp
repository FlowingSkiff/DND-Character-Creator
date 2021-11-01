#pragma once
#include <string>
#include <vector>
#include <filesystem>

// Given a directory path, pushes all xml filepaths into the supplied vector
void ExplorePath(const std::string& path,
                 std::vector<std::string>& filepaths)
{
    for (const auto& e : std::filesystem::directory_iterator(path))
    {
        if (e.is_directory())
        {
            ExplorePath(e.path().string(), filepaths);
        }
        else
        {
            if (e.path().string().find(".xml") != std::string::npos)
            {
                filepaths.push_back(e.path().string());
            }
        }
    }
}