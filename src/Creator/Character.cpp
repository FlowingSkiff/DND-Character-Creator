#include "Creator/Character.hpp"

namespace Creator
{
Character::Character() {}
Character::~Character() {}

bool Character::IsDefined(const std::string& name) const
{
    return m_defines.find(name) != m_defines.end();
}
bool Character::Define(const std::string& name)
{
    bool def = IsDefined(name);
    m_defines.insert(name);
    return def;
}
auto Character::GetName() const -> std::string_view
{
    return m_name;
}
auto Character::GetDefines() const -> const std::set<std::string>&
{
    return m_defines;
}
}// namespace Creator