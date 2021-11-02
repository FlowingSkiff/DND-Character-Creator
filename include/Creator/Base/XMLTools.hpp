#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
#include <tinyxml2.h>
#include "StringTools.hpp"
#include "SQObject.hpp"

/**
 * @brief Depreciated 
 * 
 */
struct Xmlelement
{
    std::string m_value;
    std::unordered_map<std::string, std::unordered_set<std::string>> m_attributes;
    void InsertAttribute(const std::string& name, const std::string& val);
    std::string GetAttribute(const std::string& name) const;
    bool operator==(const Xmlelement& rhs);
    bool operator!=(const Xmlelement& rhs);
};

// For each element type find all child values
void RecursiveSieveElementTypes(    std::unordered_map<std::string, std::unordered_set<std::string>>& smap,
                                    tinyxml2::XMLElement* node);

// For all element, find the basic information
void RecursiveAddElements(std::unordered_map<std::string, std::vector<Xmlelement>>& gmap,
                            tinyxml2::XMLElement* node);

// For each element type, get the children names
void RecursiveGetElementChildren(std::unordered_set<std::string>& values, 
                                 tinyxml2::XMLElement* node);

void RecursiveFindElementAttributeAndText(std::unordered_map<std::string, std::unordered_set<std::string>>& values,
                                          tinyxml2::XMLElement* node);

std::string GetDescriptionFromElement(tinyxml2::XMLElement* node);
std::string DescriptionToString(tinyxml2::XMLElement* node);

// Print descriptions for every element
void RecursivePrintDescriptions(tinyxml2::XMLElement* node);

// Build all spell xml sqobjects
void RecursiveGetSpells(std::vector<Creator::Entity::Spell>& spells, tinyxml2::XMLElement* node);
// Build all spell xml sqobjects
void RecursiveGetDeities(std::vector<Creator::Entity::Deity>& deities, tinyxml2::XMLElement* node);
// Build all spell xml sqobjects
void RecursiveGetLanguages(std::vector<Creator::Entity::Language>& deities, tinyxml2::XMLElement* node);
// Build all spell xml sqobjects
void RecursiveGetSources(std::vector<Creator::Entity::Source>& sources, tinyxml2::XMLElement* node);
// Build all spell xml sqobjects
void RecursiveGetFeatFeatures(std::vector<Creator::Entity::FeatFeature>& features, tinyxml2::XMLElement* node);
// find all setter names for every type of element
void RecursiveFindAllSetterNames(std::unordered_set<std::string>& setNames,
                                 tinyxml2::XMLElement* node);
// find all rule names for every type of element
void RecursiveFindAllRuleAttNames(std::unordered_map<std::string, std::unordered_set<std::string>>& ruleNamesWithAtts,
                                 tinyxml2::XMLElement* node);

void GetAllElements(std::unordered_map<std::string, std::shared_ptr<Creator::Entity::SQObject>>& list,
                    tinyxml2::XMLElement* node);

// Build all spell xml sqobjects
template<typename T, typename = typename std::enable_if<std::is_base_of<Creator::Entity::SQObject, T>::value>::type>
void RecursiveGetElementsByType(std::vector<T>& sources, tinyxml2::XMLElement* node, const std::string& val)
{
    while (node)
    {
        if (node->Attribute("type"))
        {
            if (SafeCompareString(node->Attribute("type"), val))
            {
                sources.emplace_back(node);
            }
        }
        node = node->NextSiblingElement();
    }
}

void GetAllElements(std::vector<std::shared_ptr<Creator::Entity::SQObject>>& list,
                    tinyxml2::XMLElement* node);