#pragma once
#include "SQBaseObject.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <tinyxml2.h>
#include "CreatorFactory.hpp"
namespace Creator::Entity
{

    /**
     * @brief Class to store a spell for DND 5e. All items can be read in from
     *        an xml element or a sqlite3 db. Spells cannot be bought or displayed
     *        on a sheet so it only inherits from the base object. 
     * 
     */
    struct Spell : public SQObject
    {
        /**
         * @brief Construct a new Spell object from sqlite3 db options.
         * @param argc number of columns and values included from the DB
         * @param argv values read from Sqlite3 db
         * @param colz column names from the sqlite3 db
         */
        Spell(int argc, char** argv, char** colz);
        /**
         * @brief Construct a new Spell object 
         * 
         * @param node 
         */
        Spell(tinyxml2::XMLElement* node);

        bool is_ritual = false;
        bool is_concentration = false;
        bool has_verbal_component = false;
        bool has_somantic_component = false;
        bool has_material_component = false;
        std::string material_component = "none";
        std::string range = "self";
        std::string duration = "Instantaneous";
        std::string time = "1 action";
        std::string school = "Conjuration";
        int level = 0;
        std::string keywords = "";
        std::string classSupport = "All";

        // Read format for use with sqlite3 db reading
        std::string GetReadFormat() const override;
        // writing format for sqlite3 insert
        std::string GetWriteFormat() const override;
        // output writing to stream
        std::ostream& WriteToStream(std::ostream& os) const override;
        // member map for reading from xml setter options
        Factory::Maptype GetMemberMap() override;
    };

    /**
     * @brief Deity class which holds values for a deity. 
     * 
     */
    struct Deity : public SQObject, public SheetDisplay
    {
        /**
         * @brief Construct a new Deity object from sqlite3 db options.
         * @param argc number of columns and values included from the DB
         * @param argv values read from Sqlite3 db
         * @param colz column names from the sqlite3 db
         */
        Deity(int argc, char** argv, char** colz);
        /**
         * @brief Construct a new Deity object 
         * 
         * @param node 
         */
        Deity(tinyxml2::XMLElement* node);

        std::string setting = "None";
        std::string alignment = "N";
        std::string domains = "None";
        std::string symbol = "None";
        std::string gender = "None";

        // Read format for use with sqlite3 db reading
        std::string GetReadFormat() const override;
        // writing format for sqlite3 insert
        std::string GetWriteFormat() const override;
        // output writing to stream
        std::ostream& WriteToStream(std::ostream& os) const override;
        // member map for reading from xml setter options
        Factory::Maptype GetMemberMap() override;
    };

    /**
     * @brief Language class which holds values for a Language. 
     * 
     */
    struct Language : public SQObject
    {
        /**
         * @brief Construct a new Language object from sqlite3 db options.
         * @param argc number of columns and values included from the DB
         * @param argv values read from Sqlite3 db
         * @param colz column names from the sqlite3 db
         */
        Language(int argc, char** argv, char** colz);
        /**
         * @brief Construct a new Language object 
         * 
         * @param node 
         */
        Language(tinyxml2::XMLElement* node);

        bool is_standard = true;
        bool is_monster = false;
        bool is_exotic = false;
        bool is_secret = false;
        std::string speakers = "Humans";
        std::string script = "Common";
        std::string supports = "";

        // Read format for use with sqlite3 db reading
        std::string GetReadFormat() const override;
        // writing format for sqlite3 insert
        std::string GetWriteFormat() const override;
        // output writing to stream
        std::ostream& WriteToStream(std::ostream& os) const override;
        // member map for reading from xml setter options
        Factory::Maptype GetMemberMap() override;
    };

    /**
     * @brief Source class which holds values for a Source. 
     * 
     */
    struct Source : public SQObject
    {
        /**
         * @brief Construct a new Source object from sqlite3 db options.
         * @param argc number of columns and values included from the DB
         * @param argv values read from Sqlite3 db
         * @param colz column names from the sqlite3 db
         */
        Source(int argc, char** argv, char** colz);
        /**
         * @brief Construct a new Source object 
         * 
         * @param node 
         */
        Source(tinyxml2::XMLElement* node);

        std::string abbreviation = "";
        std::string url = "";
        std::string image = "";
        std::string errata = "";
        std::string author = "";
        std::string author_abbreviation = "";
        std::string author_url = "";
        std::string release = "";
        std::string information = "";
        bool is_official = true;
        bool is_core = true;
        bool is_playtest = false;
        bool is_incomplete = false;
        bool is_homebrew = false;
        bool is_third_party = false;
        bool is_supplement = false;
        bool is_league = false;
        bool is_legal = true;
        bool is_disabled = false;


        // Read format for use with sqlite3 db reading
        std::string GetReadFormat() const override;
        // writing format for sqlite3 insert
        std::string GetWriteFormat() const override;
        // output writing to stream
        std::ostream& WriteToStream(std::ostream& os) const override;
        // member map for reading from xml setter options
        Factory::Maptype GetMemberMap() override;
    };

    /**
     * @brief Information class which holds values for a Information. 
     * 
     */
    struct Information : public SQObject
    {
        /**
         * @brief Construct a new Information object from sqlite3 db options.
         * @param argc number of columns and values included from the DB
         * @param argv values read from Sqlite3 db
         * @param colz column names from the sqlite3 db
         */
        Information(int argc, char** argv, char** colz);
        /**
         * @brief Construct a new Information object 
         * 
         * @param node 
         */
        Information(tinyxml2::XMLElement* node);

        // Read format for use with sqlite3 db reading
        std::string GetReadFormat() const override;
        // writing format for sqlite3 insert
        std::string GetWriteFormat() const override;
        // output writing to stream
        std::ostream& WriteToStream(std::ostream& os) const override;
        // member map for reading from xml setter options
        Factory::Maptype GetMemberMap() override;
    };

    /**
     * @brief FeatFeature class which holds values for a FeatFeature. 
     * 
     */
    struct FeatFeature : public SQObject, public SheetDisplay
    {
        /**
         * @brief Construct a new FeatFeature object from sqlite3 db options.
         * @param argc number of columns and values included from the DB
         * @param argv values read from Sqlite3 db
         * @param colz column names from the sqlite3 db
         */
        FeatFeature(int argc, char** argv, char** colz);
        /**
         * @brief Construct a new FeatFeature object 
         * 
         * @param node 
         */
        FeatFeature(tinyxml2::XMLElement* node);

        std::string supports = "";
        std::string requirements = "";
        std::vector<RuleBase> rules;

        // Read format for use with sqlite3 db reading
        std::string GetReadFormat() const override;
        // writing format for sqlite3 insert
        std::string GetWriteFormat() const override;
        // output writing to stream
        std::ostream& WriteToStream(std::ostream& os) const override;
        // member map for reading from xml setter options
        Factory::Maptype GetMemberMap() override;
    };

    /**
     * @brief Feat class which holds values for a Feat. 
     * 
     */
    struct Feat : public SQObject, public SheetDisplay
    {
        /**
         * @brief Construct a new Feat object from sqlite3 db options.
         * @param argc number of columns and values included from the DB
         * @param argv values read from Sqlite3 db
         * @param colz column names from the sqlite3 db
         */
        Feat(int argc, char** argv, char** colz);
        /**
         * @brief Construct a new Feat object 
         * 
         * @param node 
         */
        Feat(tinyxml2::XMLElement* node);

        std::vector<RuleBase> rules;
        std::string requirements = "";
        std::string prerequisite = "";
        bool allow_duplicate = false;

        // Read format for use with sqlite3 db reading
        std::string GetReadFormat() const override;
        // writing format for sqlite3 insert
        std::string GetWriteFormat() const override;
        // output writing to stream
        std::ostream& WriteToStream(std::ostream& os) const override;
        // member map for reading from xml setter options
        Factory::Maptype GetMemberMap() override;
    };

    /**
     * @brief Companion class which holds values for a Companion. 
     * 
     */
    struct Companion : public SQObject, public CharacterBase
    {
        /**
         * @brief Construct a new Companion object from sqlite3 db options.
         * @param argc number of columns and values included from the DB
         * @param argv values read from Sqlite3 db
         * @param colz column names from the sqlite3 db
         */
        Companion(int argc, char** argv, char** colz);
        /**
         * @brief Construct a new Companion object 
         * 
         * @param node 
         */
        Companion(tinyxml2::XMLElement* node);

        std::vector<RuleBase> rules;
        std::string supports;
        std::string requirements;

        // Read format for use with sqlite3 db reading
        std::string GetReadFormat() const override;
        // writing format for sqlite3 insert
        std::string GetWriteFormat() const override;
        // output writing to stream
        std::ostream& WriteToStream(std::ostream& os) const override;
        // member map for reading from xml setter options
        Factory::Maptype GetMemberMap() override;
    };

    struct CompanionAction: public SQObject, public SheetDisplay
    {
        CompanionAction(int argc, char** argv, char** colz);
        CompanionAction(tinyxml2::XMLElement* node);

        std::vector<RuleBase> rules;
        std::string action = "";

        // Read format for use with sqlite3 db reading
        std::string GetReadFormat() const override;
        // writing format for sqlite3 insert
        std::string GetWriteFormat() const override;
        // output writing to stream
        std::ostream& WriteToStream(std::ostream& os) const override;
        // member map for reading from xml setter options
        Factory::Maptype GetMemberMap() override;
    };

    struct AbilityScoreImprovement: public SQObject, public SheetDisplay
    {
        AbilityScoreImprovement(int argc, char** argv, char** colz);
        AbilityScoreImprovement(tinyxml2::XMLElement* node);

        std::vector<RuleBase> rules;
        std::string supports;
        std::string requirements;
        bool allow_duplicate = false;
        // Read format for use with sqlite3 db reading
        std::string GetReadFormat() const override;
        // writing format for sqlite3 insert
        std::string GetWriteFormat() const override;
        // output writing to stream
        std::ostream& WriteToStream(std::ostream& os) const override;
        // member map for reading from xml setter options
        Factory::Maptype GetMemberMap() override;
    };

    struct Rule: public SQObject
    {
        Rule(int argc, char** argv, char** colz);
        Rule(tinyxml2::XMLElement* node);

        std::string keywords = "";
        // Read format for use with sqlite3 db reading
        std::string GetReadFormat() const override;
        // writing format for sqlite3 insert
        std::string GetWriteFormat() const override;
        // output writing to stream
        std::ostream& WriteToStream(std::ostream& os) const override;
        // member map for reading from xml setter options
        Factory::Maptype GetMemberMap() override;
    };

    struct Option: public SQObject, public SheetDisplay
    {
        Option(int argc, char** argv, char** colz);
        Option(tinyxml2::XMLElement* node);

        std::vector<RuleBase> rules;

        std::string keywords = "";
        // Read format for use with sqlite3 db reading
        std::string GetReadFormat() const override;
        // writing format for sqlite3 insert
        std::string GetWriteFormat() const override;
        // output writing to stream
        std::ostream& WriteToStream(std::ostream& os) const override;
        // member map for reading from xml setter options
        Factory::Maptype GetMemberMap() override;
    };

    struct Background: public SQObject, public SheetDisplay
    {
        Background(int argc, char** argv, char** colz);
        Background(tinyxml2::XMLElement* node);

        std::vector<RuleBase> rules;
        // Read format for use with sqlite3 db reading
        std::string GetReadFormat() const override;
        // writing format for sqlite3 insert
        std::string GetWriteFormat() const override;
        // output writing to stream
        std::ostream& WriteToStream(std::ostream& os) const override;
        // member map for reading from xml setter options
        Factory::Maptype GetMemberMap() override;
    };

    struct BackgroundFeature: public SQObject, public SheetDisplay, public SpellcastingBase
    {
        BackgroundFeature(int argc, char** argv, char** colz);
        BackgroundFeature(tinyxml2::XMLElement* node);

        std::vector<RuleBase> rules;
        std::string supports = "";
        std::string requirements = "";
        // Read format for use with sqlite3 db reading
        std::string GetReadFormat() const override;
        // writing format for sqlite3 insert
        std::string GetWriteFormat() const override;
        // output writing to stream
        std::ostream& WriteToStream(std::ostream& os) const override;
        // member map for reading from xml setter options
        Factory::Maptype GetMemberMap() override;
    };

    /**
     * @brief Create a New Object From Type object
     * 
     * @param typearg index of the type attribute
     * @param argc forward from the sqlite3 number of args
     * @param argv forward from the sqlite3 arg values
     * @param col forward of the column labels from sqlite3
     * @return SQObject* 
     */
    SQObject* CreateNewObjectFromType(int typearg, int argc, char** argv, char** col);
}