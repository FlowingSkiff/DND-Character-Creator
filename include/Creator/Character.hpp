#pragma once
#include <string>
#include "Base\SQObject.hpp"
#include <set>
#include <memory>
namespace Creator
{
class Character
{
  public:
    Character();
    ~Character();

  public:
    bool IsDefined(const std::string& id) const;
    bool Define(const std::string& def);

    auto GetName() const -> std::string_view;
    // auto GetDeity() const -> const Entity::Deity&;
    // auto GetRace() const -> const Entity::Race&;
    // auto GetClass() const -> const Entity::Class&;
    auto GetDefines() const -> const std::set<std::string>&;

    /*
    bool SetName(std::string_view rhs);
    bool SetDeity(std::string_view rhs);
    bool SetDeity(const Entity::Deity& rhs);
    bool SetRace(std::string_view rhs);
    bool SetRace(const Entity::Race& rhs);
    bool SetClass(const Entity::Class& rhs);
    bool SetClass(std::string_view rhs);
    */

  protected:
    //const EntityList& m_entity_list;
    std::string m_name;
    std::vector<std::shared_ptr<Entity::SQObject>> m_children;
    std::set<std::string> m_defines;

  private:
};
}// namespace Creator
