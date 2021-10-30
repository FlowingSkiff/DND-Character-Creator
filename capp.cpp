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
    const std::string path = R"(C:\Users\boats\OneDrive\Surface Documents\5e Character Builder\custom)";
    std::vector<std::string> paths;
    ExplorePath(path, paths);
    auto* tmp = new TmpDisplay();
    for (const auto& p : paths)
    {
        tinyxml2::XMLDocument xmlDoc;
        if (xmlDoc.LoadFile(p.c_str()) != tinyxml2::XML_SUCCESS)
        {
            LogWarn("Could not load file {}", p);
            continue;
        }
        auto firstElement = xmlDoc.FirstChildElement("elements")->FirstChildElement("element");
        GetAllElements(tmp->m_objects, firstElement);
    }
    std::vector<wxString> all_element_names;
    all_element_names.reserve(tmp->m_objects.size());
    std::for_each(std::begin(tmp->m_objects), std::end(tmp->m_objects), [&](const auto& v){all_element_names.emplace_back(v.second->external_id);});
    tmp->m_choice1->Set(all_element_names);
    tmp->Show(true);
    return true;
}