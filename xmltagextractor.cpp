#include <iostream>
#include <regex>
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <tinyxml2.h>


#include <Creator/Base/XMLTools.hpp>
#include <Creator/Base/PathingTools.hpp>
#include <Creator/Base/StringTools.hpp>
#include <Creator/Base/LoggingTools.hpp>
#include <Creator/Base/SQObject.hpp>

std::shared_ptr<spdlog::logger> Logfile::m_instance = nullptr;

using namespace tinyxml2;
using namespace Creator::Entity;
int main(int, char**)
{
    const std::string path = R"(C:\Users\boats\OneDrive\Surface Documents\5e Character Builder\custom)";
    std::vector<std::string> paths;
    ExplorePath(path, paths);
    std::unordered_set<std::string> allChildren;
    std::unordered_map<std::string, std::unordered_set<std::string>> childtypes;
    std::vector<Spell> spells;
    std::vector<Deity> deities;
    std::vector<Language> languages;
    std::vector<Source> sources;
    std::unordered_set<std::string> allSetterNames;
    std::unordered_map<std::string, std::unordered_set<std::string>> allRuleAttNames;
    std::vector<FeatFeature> featFeatures;
    std::vector<Feat> feats;
    std::vector<Companion> companions;
    std::vector<CompanionAction> companionActions;
    std::vector<AbilityScoreImprovement> abilityScoreImprovements;
    std::vector<Rule> rules;
    std::vector<Option> options;
    std::vector<Background> backgrounds;
    std::vector<BackgroundFeature> backgroundFeatures;
    std::vector<ClassFeature> classFeatures;
    std::vector<ArchetypeFeature> archetypeFeatures;
    std::vector<RaceVariant> raceVariants;
    std::vector<RacialTrait> racialTraits;
    std::vector<SubRace> subRaces;
    std::vector<Archetype> archetypes;
    std::vector<Race> races;
    std::vector<Class> classes;
    std::vector<Item> items;
    std::vector<Weapon> weaspons;
    std::vector<Armor> armors;
    std::vector<MagicItem> magicItems;
    std::vector<std::shared_ptr<SQObject>> allElements;
    for (const auto& p : paths)
    {
        XMLDocument xmlDoc;
        if (xmlDoc.LoadFile(p.c_str()) != XML_SUCCESS)
        {
            LogCritical("Could not load file: {}", path);
            return 0;
        }
        auto root = xmlDoc.FirstChildElement("elements");
        auto firstElement = root->FirstChildElement("element");
        // RecursiveGetElementChildren(allChildren, firstElement);
        // RecursiveSieveElementTypes(typemap, firstElement);
        // RecursiveFindElementAttributeAndText(childtypes, firstElement);
        // RecursivePrintDescriptions(firstElement);
        // RecursiveGetSpells(spells, firstElement);
        // RecursiveFindAllSetterNames(allSetterNames, firstElement);
        // RecursiveGetDeities(deities, firstElement);
        // RecursiveGetLanguages(languages, firstElement);
        // RecursiveGetSources(sources, firstElement);
        // RecursiveFindAllRuleAttNames(allRuleAttNames, firstElement);
        // RecursiveGetFeatFeatures(featFeatures, firstElement);
        // RecursiveGetElementsByType(magicItems, firstElement, "Magic Item");
        GetAllElements(allElements, firstElement);
    }
    std::ofstream outtmp("logs/allElements.txt");
    for (const auto& f : allElements)
    {
        outtmp << *f << '\n';
    }
}
