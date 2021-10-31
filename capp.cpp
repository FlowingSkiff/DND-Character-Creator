#include "capp.hpp"
#include "primativeDesign.hpp"
#include "XMLTools.hpp"
#include <tinyxml2.h>
#include <string>
#include <vector>
#include <filesystem>
#include "LoggingTools.hpp"
#include "PathingTools.hpp"
wxIMPLEMENT_APP(cApp);

std::shared_ptr<spdlog::logger> Logfile::m_instance = nullptr;

cApp::cApp()
{

}

cApp::~cApp()
{

}

bool cApp::OnInit()
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)        
        SetConsoleOutputCP(CP_UTF8);
    #endif
    const std::string path = R"(C:\Users\boats\OneDrive\Surface Documents\5e Character Builder\custom)";
    std::vector<std::string> paths;
    ExplorePath(path, paths);
    auto* tmp = new TmpDisplay();
    // Load all items
    for (const auto& p : paths)
    {
        tinyxml2::XMLDocument xmlDoc;
        if (xmlDoc.LoadFile(p.c_str()) != tinyxml2::XML_SUCCESS)
        {
            LogWarn("Could not load file {}", p);
            continue;
        }
        auto firstElement = xmlDoc.FirstChildElement("elements")->FirstChildElement("element");
        GetAllElements(tmp->m_item_map, firstElement);
    }
    // update m_items vector for lookup
    tmp->m_items.reserve(tmp->m_item_map.size());
    std::vector<wxString> all_element_names;
    all_element_names.reserve(tmp->m_item_map.size());
    std::for_each(std::begin(tmp->m_item_map), std::end(tmp->m_item_map), 
            [&](const auto& v){tmp->m_items.push_back(v.second);});
    // sort the list by name, then by id
    std::sort(std::begin(tmp->m_items), std::end(tmp->m_items),
            [](const auto& first, const auto& second)
            {
                if (first->name != second->name)
                    return first->name < second->name;
                return first->external_id < second->external_id;
            });
    // update the choice box with the names
    std::for_each(std::begin(tmp->m_items), std::end(tmp->m_items),
            [&](const auto& v){all_element_names.emplace_back(v->name);});
    tmp->m_choice1->Set(all_element_names);
    tmp->Show(true);
    return true;
}