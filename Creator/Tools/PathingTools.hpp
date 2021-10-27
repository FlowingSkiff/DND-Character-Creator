#pragma once
#include <string>
#include <vector>
#include <filesystem>

// Given a directory path, pushes all xml filepaths into the supplied vector
void ExplorePath(const std::string& path,
                 std::vector<std::string>& filepaths)
{
    using namespace std::filesystem;
    for (const auto& e : directory_iterator(path))
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