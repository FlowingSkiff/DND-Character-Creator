#include "tinyxml2.h"
#include "SQObject.hpp"
#include "PathingTools.hpp"
#include "LoggingTools.hpp"
#include "XMLTools.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <memory>
#include <algorithm>
#include <mutex>
#include <execution>
struct XMLIterator
{
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using pointer = tinyxml2::XMLElement*;
    using value_type = tinyxml2::XMLElement;
    using reference = tinyxml2::XMLElement&;
    using iterator = XMLIterator;

    XMLIterator(pointer ptr): m_ptr(ptr) { }
    reference operator*() const{ return *m_ptr; }
    pointer operator->(){return m_ptr; }
    iterator& operator++()
    {
        m_ptr = m_ptr->NextSiblingElement();
        return *this;
    }
    iterator operator++(int)
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }
    friend bool operator==(const iterator& a, const iterator& b)
    {return a.m_ptr == b.m_ptr;}
    friend bool operator!=(const iterator& a, const iterator& b)
    {return a.m_ptr != b.m_ptr;}
    private:
        pointer m_ptr = nullptr;

};

namespace Custom
{
    struct XMLWrapper
    {
        XMLWrapper(tinyxml2::XMLElement* node):m_ptr(node)
        {
        }
        tinyxml2::XMLElement* m_ptr = nullptr;
    };
    XMLIterator begin(XMLWrapper& wrapped)
    {
        return XMLIterator(wrapped.m_ptr);
    }
    XMLIterator end(XMLWrapper& /*wrapped*/)
    {
        return XMLIterator(nullptr);
    }
} // Custom

std::shared_ptr<Creator::Entity::SQObject> GetObjectFromNode(tinyxml2::XMLElement* node)
{
    auto& it = *node;
    const auto type_name_safe = [&](){
        if (!node->Attribute("type"))
            {
                if (SafeCompareString(it.Name(), "append"))
                    return std::string("Append");
                else if (it.Attribute("name"))
                    LogError("Could not find type property for element {}", it.Attribute("name"));
                else
                    LogWarn("Encountered {} with no name or type", it.Name());
                return std::string();
            }
            std::string tmp = it.Attribute("type");
            InplaceUnderscoreWhitespace(tmp);
            return tmp;
        }();
    const auto& type = magic_enum::enum_cast<Creator::Entity::Type>(type_name_safe);
    if (type.has_value())
    {
        using namespace Creator::Entity;
        switch (type.value())
        {
        case Creator::Entity::Type::Archetype_Feature:
            return std::make_shared<ArchetypeFeature>(&it);
            break;
        case Creator::Entity::Type::Archetype:
            return std::make_shared<Archetype>(&it);
            break;
        case Creator::Entity::Type::Class_Feature:
            return std::make_shared<ClassFeature>(&it);
            break;
        case Creator::Entity::Type::Spell:
            return std::make_shared<Spell>(&it);
            break;
        case Creator::Entity::Type::Race:
            return std::make_shared<Race>(&it);
            break;
        case Creator::Entity::Type::Magic_Item:
            return std::make_shared<MagicItem>(&it);
            break;
        case Creator::Entity::Type::Sub_Race:
            return std::make_shared<SubRace>(&it);
            break;
        case Creator::Entity::Type::Option:
            return std::make_shared<Option>(&it);
            break;
        case Creator::Entity::Type::Armor:
            return std::make_shared<Armor>(&it);
            break;
        case Creator::Entity::Type::Item:
            return std::make_shared<Item>(&it);
            break;
        case Creator::Entity::Type::Weapon:
            return std::make_shared<Weapon>(&it);
            break;
        case Creator::Entity::Type::Class:
            return std::make_shared<Class>(&it);
            break;
        case Creator::Entity::Type::Ability_Score_Improvement:
            return std::make_shared<AbilityScoreImprovement>(&it);
            break;
        case Creator::Entity::Type::Rule:
            return std::make_shared<Rule>(&it);
            break;
        case Creator::Entity::Type::Source:
            return std::make_shared<Source>(&it);
            break;
        case Creator::Entity::Type::Language:
            return std::make_shared<Language>(&it);
            break;
        case Creator::Entity::Type::Companion:
            return std::make_shared<Companion>(&it);
            break;
        case Creator::Entity::Type::Companion_Action:
            return std::make_shared<CompanionAction>(&it);
            break;
        case Creator::Entity::Type::Background:
            return std::make_shared<Background>(&it);
            break;
        case Creator::Entity::Type::Background_Feature:
            return std::make_shared<BackgroundFeature>(&it);
            break;
        case Creator::Entity::Type::Deity:
            return std::make_shared<Deity>(&it);
            break;
        case Creator::Entity::Type::Feat:
            return std::make_shared<Feat>(&it);
            break;
        case Creator::Entity::Type::Feat_Feature:
            return std::make_shared<FeatFeature>(&it);
            break;
        case Creator::Entity::Type::Information:
            return std::make_shared<Information>(&it);
            break;
        case Creator::Entity::Type::Race_Variant:
            return std::make_shared<RaceVariant>(&it);
            break;
        case Creator::Entity::Type::Racial_Trait:
            return std::make_shared<RacialTrait>(&it);
            break;
        case Creator::Entity::Type::Append:
            return std::make_shared<Append>(&it);
            break;
        case Creator::Entity::Type::Companion_Trait:
            return std::make_shared<CompanionTrait>(&it);
            break;
        case Creator::Entity::Type::Companion_Reaction:
            return std::make_shared<CompanionReaction>(&it);
            break;
        case Creator::Entity::Type::Support:
            return std::make_shared<Support>(&it);
            break;
        case Creator::Entity::Type::Weapon_Property:
            return std::make_shared<WeaponProperty>(&it);
            break;
        case Creator::Entity::Type::Proficiency:
            return std::make_shared<Proficiency>(&it);
            break;
        case Creator::Entity::Type::Background_Variant:
            return std::make_shared<BackgroundVariant>(&it);
            break;
        case Creator::Entity::Type::Grants:
            return std::make_shared<Grants>(&it);
            break;
        case Creator::Entity::Type::Internal:
            return std::make_shared<Internal>(&it);
            break;
        case Creator::Entity::Type::Dragonmark:
            return std::make_shared<Dragonmark>(&it);
            break;
        case Creator::Entity::Type::Magic_School:
            return std::make_shared<MagicSchool>(&it);
            break;
        case Creator::Entity::Type::Condition:
            return std::make_shared<Condition>(&it);
            break;
        default:
            LogWarn("Unhandled new operation for type {}", it.Attribute("type"));
            return std::make_shared<SQObject>(Type::General, &it);
            break;
        }
    }
    else
    {
        if (it.Attribute("type"))
        {
            if (it.Attribute("name"))
                LogError("Could not load element of type {} for element {} \"{}\"", it.Attribute("type"), it.Attribute("name"), it.Value());
            else
                LogError("Could not load element of type {} for element without name \"{}\"", it.Attribute("type"), it.Value());
        }
        else
        {
            if (it.Attribute("name"))
                LogError("Could not load element of type undefined for element {} \"{}\"", it.Attribute("name"), it.Value());
            else
                LogError("Could not load element of type undefined for element without name \"{}\"", it.Value());
        }
    }
    return std::make_shared<Creator::Entity::SQObject>(Creator::Entity::SQObject(Creator::Entity::Type::None));
}


void ParGetAllElements([[maybe_unused]] std::vector<std::shared_ptr<Creator::Entity::SQObject>>& list,
                    tinyxml2::XMLElement* node)
{
    Custom::XMLWrapper wrapped(node);
    //for (auto& it : wrapped)
    //{
    //    
    //}
    std::mutex mtx;
    std::for_each(std::execution::par_unseq,
                  begin(wrapped), end(wrapped),
                  [&](auto& v){
                        auto tmp = GetObjectFromNode(&v);
                        std::lock_guard<std::mutex> guard(mtx);
                        list.emplace_back(std::move(tmp));
                  });
}




using namespace tinyxml2;
using namespace Creator::Entity;

std::shared_ptr<spdlog::logger> Logfile::m_instance = nullptr;

int main()
{
    const std::string path = R"(C:\Users\boats\OneDrive\Surface Documents\5e Character Builder\custom)";
    std::vector<std::string> paths;
    ExplorePath(path, paths);
    {
        std::vector<std::shared_ptr<SQObject>> allElements;
        allElements.reserve(12000);
        
        auto t1 = std::chrono::high_resolution_clock::now();
        
        for (const auto& p : paths)
        {
            XMLDocument xmlDoc;
            xmlDoc.LoadFile(p.c_str());
            auto root = xmlDoc.FirstChildElement("elements");
            auto firstElement = root->FirstChildElement("element");
            GetAllElements(allElements, firstElement);
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        std::cout << "Loading took " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "milliseconds\n";
        std::cout << allElements.size() << '\n';
    }
    {
        std::vector<std::shared_ptr<SQObject>> allElements;
        allElements.reserve(12000);
        auto t1 = std::chrono::high_resolution_clock::now();
        
        for (const auto& p : paths)
        {
            XMLDocument xmlDoc;
            xmlDoc.LoadFile(p.c_str());
            auto root = xmlDoc.FirstChildElement("elements");
            auto firstElement = root->FirstChildElement("element");
            ParGetAllElements(allElements, firstElement);
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        std::cout << "Loading took " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "milliseconds\n";
        std::cout << allElements.size() << '\n';
    }
    {
        std::vector<std::shared_ptr<SQObject>> allElements;
        allElements.reserve(12000);
        auto t1 = std::chrono::high_resolution_clock::now();
        
        std::mutex lock;
        std::for_each(std::execution::par_unseq,
                      paths.begin(), paths.end(),
                      [&](const auto& p){
                            XMLDocument xmlDoc;
                            xmlDoc.LoadFile(p.c_str());
                            auto root = xmlDoc.FirstChildElement("elements");
                            auto firstElement = root->FirstChildElement("element");
                            Custom::XMLWrapper wpr(firstElement);
                            for (auto& v : wpr)
                            {
                                auto tmp = GetObjectFromNode(&v);
                                std::lock_guard<std::mutex> guard(lock);
                                allElements.emplace_back(std::move(tmp));
                            }
                      }
                      );
        auto t2 = std::chrono::high_resolution_clock::now();
        std::cout << "Loading took " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "milliseconds\n";
        std::cout << allElements.size() << '\n';
    }
}