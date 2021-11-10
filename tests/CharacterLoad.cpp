#include "Creator/Character.hpp"
#include <Creator/Base/LoggingTools.hpp>
#include <Creator/EntityList.hpp>
#include <string>
std::shared_ptr<spdlog::logger> Logfile::m_instance = nullptr;

int main()
{
    using namespace Creator;
    using namespace std::string_literals;
    EntityList entityList;
    entityList.LoadFromParentDirectory(R"(C:\Users\boats\OneDrive\Surface Documents\5e Character Builder\custom)");
    auto tmp = entityList.GetWhere(SearchType::NAME, "Warlock");
    for (auto item : tmp)
    {
        std::cout << item << '\n';
    }
    return 0;
}