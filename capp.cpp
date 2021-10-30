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
    std::vector<std::shared_ptr<Creator::Entity::SQObject>> allElements;
    ExplorePath(path, paths);
    for (const auto& p : paths)
    {
        tinyxml2::XMLDocument xmlDoc;
        if (xmlDoc.LoadFile(p.c_str()) != tinyxml2::XML_SUCCESS)
        {
            LogWarn("Could not load file {}", p);
            continue;
        }
        auto firstElement = xmlDoc.FirstChildElement("elements")->FirstChildElement("element");
        GetAllElements(allElements, firstElement);
    }
    auto* tmp = new TmpDisplay();
    for (const auto& o : allElements)
        tmp->m_choice1->AppendString(o->name);
    tmp->Show(true);
    return true;
}