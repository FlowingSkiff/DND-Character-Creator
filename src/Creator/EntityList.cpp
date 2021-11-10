#include <Creator/EntityList.hpp>
#include <Creator/Base/SQObject.hpp>
#include <Creator/Base/PathingTools.hpp>
#include <Creator/Base/XMLTools.hpp>
#include <tinyxml2.h>
#include <Creator/Base/LoggingTools.hpp>
#include <thirdparty/magic_enum.hpp>
#include <string>
namespace Creator
{

int operator&(const SearchType& lhs, const SearchType& rhs)
{
    return static_cast<int>(lhs) & static_cast<int>(rhs);
}
int operator|(const SearchType& lhs, const SearchType& rhs)
{
    return static_cast<int>(lhs) | static_cast<int>(rhs);
}
EntityList::EntityList() : m_items{}, m_item_map{}
{
}

EntityList::~EntityList() {}

std::vector<std::shared_ptr<Entity::SQObject>> EntityList::GetWhere(SearchType type, std::string_view value) const
{
    if (type == SearchType::ALL) return m_items;
    std::vector<std::shared_ptr<Entity::SQObject>> result;
    if (type & SearchType::NAME)
    {
        for (const auto& item : m_items)
            if (item->name == value)
                result.push_back(item);
    }
    if (type & SearchType::SOURCE)
    {
        for (const auto& item : m_items)
            if (item->source == value)
                result.push_back(item);
    }
    if (type & SearchType::TYPE)
    {
        for (const auto& item : m_items)
            if (magic_enum::enum_name(item->type) == value)
                result.push_back(item);
    }
    if (type & SearchType::EXTERNAL_ID)
    {
        if (m_map_is_built)
        {
            if (m_item_map.find(std::string(value)) != m_item_map.end())
                result.push_back(m_item_map.at(std::string(value)));
        }
        for (const auto& item : m_items)
        {
            if (magic_enum::enum_name(item->type) == value)
            {
                result.push_back(item);
                break;
            }
        }
    }
    return result;
}
bool EntityList::LoadFromFile(std::string_view name, bool build_map)
{
    bool is_okay = true;
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(name.data()) != tinyxml2::XML_SUCCESS)
    {
        LogError("Could not loading file {}", name);
        is_okay = false;
    }
    if (is_okay)
    {
        auto first_element = doc.FirstChildElement("elements")->FirstChildElement("element");
        GetAllElements(m_items, first_element);
        m_map_is_built = false;
    }
    if (build_map)
        BuildMap();
    return is_okay;
}
bool EntityList::LoadFromFileList(const std::vector<std::string>& filenames, bool build_map)
{
    bool is_okay = true;
    for (auto f : filenames)
        is_okay &= LoadFromFile(f, false);
    if (build_map)
        BuildMap();
    return is_okay;
}
bool EntityList::LoadFromParentDirectory(const std::string& dir, bool build_map)
{
    std::vector<std::string> filenames;
    ExplorePath(dir, filenames);
    return LoadFromFileList(filenames, build_map);
}
void EntityList::BuildMap()
{
    if (!m_map_is_built)
    {
        for (const auto& item : m_items)
            m_item_map[item->external_id] = item;
        m_map_is_built = true;
    }
}
}// namespace Creator
