#include "XMLTools.hpp"

void Xmlelement::InsertAttribute(const std::string& name, const std::string& val)
{
    m_attributes[name].insert(val);
}
std::string Xmlelement::GetAttribute(const std::string& name) const
{
    if (m_attributes.find(name) != m_attributes.end())
        return *m_attributes.at(name).begin();
    return "";
}
bool Xmlelement::operator==(const Xmlelement& rhs)
{
    return m_value == rhs.m_value;
}
bool Xmlelement::operator!=(const Xmlelement& rhs)
{
    return m_value != rhs.m_value;
}

void RecursiveGetSpells(std::vector<Creator::Entity::Spell>& spells, tinyxml2::XMLElement* node)
{
    while (node)
    {
        if (node->Attribute("type"))
        {
            if (SafeCompareString(node->Attribute("type"), "spell"))
            {
                spells.emplace_back(node);
            }
        }
        node = node->NextSiblingElement();
    }
}

void RecursiveGetDeities(std::vector<Creator::Entity::Deity>& deities, tinyxml2::XMLElement* node)
{
    while (node)
    {
        if (node->Attribute("type"))
        {
            if (SafeCompareString(node->Attribute("type"), "Deity"))
            {
                deities.emplace_back(node);
            }
        }
        node = node->NextSiblingElement();
    }
}

void RecursiveGetLanguages(std::vector<Creator::Entity::Language>& languages, tinyxml2::XMLElement* node)
{
    while (node)
    {
        if (node->Attribute("type"))
        {
            if (SafeCompareString(node->Attribute("type"), "Language"))
            {
                languages.emplace_back(node);
            }
        }
        node = node->NextSiblingElement();
    }
}

void RecursiveGetSources(std::vector<Creator::Entity::Source>& sources, tinyxml2::XMLElement* node)
{
    while (node)
    {
        if (node->Attribute("type"))
        {
            if (SafeCompareString(node->Attribute("type"), "Source"))
            {
                sources.emplace_back(node);
            }
        }
        node = node->NextSiblingElement();
    }
}

void RecursivePrintDescriptions(tinyxml2::XMLElement* node)
{
    while (node)
    {
        std::cout << GetDescriptionFromElement(node) << '\n';
        node = node ->NextSiblingElement();
    }
}

std::string GetDescriptionFromElement(tinyxml2::XMLElement* node)
{
    if (auto desc = node->FirstChildElement("description"))
    {
        tinyxml2::XMLPrinter pt;
        if (auto descp = desc->FirstChildElement())
        {
            while (descp)
            {
                descp->Accept(&pt);
                descp = descp->NextSiblingElement();
            }
        }
        return std::string(pt.CStr());
    }
    return "";
}

std::string DescriptionToString(tinyxml2::XMLElement* node)
{
    if (SafeCompareString(node->Value(), "description"))
    {
        tinyxml2::XMLPrinter pt;
        if (auto desc = node->FirstChildElement())
        {
            while (desc)
            {
                desc->Accept(&pt);
                desc = desc->NextSiblingElement();
            }
        }
        return std::string(pt.CStr());
    }
    return "";
}

void RecursiveFindElementAttributeAndText(std::unordered_map<std::string, std::unordered_set<std::string>>& values,
                                          tinyxml2::XMLElement* node)
{
    static const std::string has_text = "***Has Text***";
    while (node)
    {
        auto child = node->FirstChildElement();
        while (child)
        {
            std::string type = child->Value();
            auto att = child->FirstAttribute();
            while (att)
            {
                values[type].insert(att->Name());
                att = att->Next();
            }
            if (child->ToText())
                values[type].insert(has_text);
            child = child->NextSiblingElement();
        }
        node = node->NextSiblingElement();
    }
}

void RecursiveGetElementChildren(std::unordered_set<std::string>& values, 
                                 tinyxml2::XMLElement* node)
{
    while (node)
    {
        if (SafeCompareString(node->Value(), "element"))
        {
            auto child = node->FirstChildElement();
            while (child)
            {
                values.insert(std::string(child->Value()));
                child = child->NextSiblingElement();
            }
        }
        node = node->NextSiblingElement();
    }
}

void RecursiveAddElements(std::unordered_map<std::string, std::vector<Xmlelement>>& gmap,
                            tinyxml2::XMLElement* node)
{
    while(node)
    {
        Xmlelement tmp;
        tmp.m_value = node->Value();
        auto att = node->FirstAttribute();
        while (att)
        {
            tmp.InsertAttribute(att->Name(), att->Value());
            att = att->Next();
        }
        gmap[tmp.m_value].push_back(tmp);
        RecursiveAddElements(gmap, node->FirstChildElement());
        node = node -> NextSiblingElement();
    }
}

void RecursiveSieveElementTypes(    std::unordered_map<std::string, std::unordered_set<std::string>>& smap,
                                    tinyxml2::XMLElement* node)
{
    while(node)
    {
        if (node->FindAttribute("type"))
        {
            std::string type = node->FindAttribute("type")->Value();
            if (node->FirstChildElement("setters"))
            {
                auto setters = node->FirstChildElement("setters");
                auto att = setters->FirstChildElement(); // set something
                while (att)
                {
                    smap[type].insert(att->Attribute("name"));
                    att = att->NextSiblingElement();
                }
            }
        }
        RecursiveSieveElementTypes(smap, node->FirstChildElement());
        node = node->NextSiblingElement();
    }
}

void RecursiveFindAllSetterNames(std::unordered_set<std::string>& setNames,
                                 tinyxml2::XMLElement* node)
{
    while (node)
    {
        if (auto setters = node->FirstChildElement("setters"))
        {
            auto child = setters->FirstChildElement();
            while (child)
            {
                if (auto set = child->FindAttribute("name"))
                {
                    setNames.insert(set->Value());
                }
                child = child->NextSiblingElement();
            }
        }
        node = node->NextSiblingElement();
    }
}

void RecursiveFindAllRuleAttNames(std::unordered_map<std::string, std::unordered_set<std::string>>& ruleNamesWithAtts,
                                 tinyxml2::XMLElement* node)
{
    while (node)
    {
        if (auto setters = node->FirstChildElement("rules"))
        {
            auto child = setters->FirstChildElement();
            while (child)
            {
                auto att = child->FirstAttribute();
                while (att)
                {
                    ruleNamesWithAtts[child->Name()].insert(att->Name());
                    att = att->Next();
                }
                child = child->NextSiblingElement();
            }
        }
        node = node->NextSiblingElement();
    }
}

void RecursiveGetFeatFeatures(std::vector<Creator::Entity::FeatFeature>& features, tinyxml2::XMLElement* node)
{
    while (node)
    {
        if (node->Attribute("type"))
        {
            if (SafeCompareString(node->Attribute("type"), "Feat Feature"))
            {
                features.emplace_back(node);
            }
        }
        node = node->NextSiblingElement();
    }
}