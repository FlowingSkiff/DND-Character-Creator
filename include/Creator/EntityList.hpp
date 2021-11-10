#pragma once
#include <memory>
#include <vector>
#include <string_view>
#include <unordered_map>
#include <string>
namespace Creator
{
namespace Entity
{
    struct SQObject;
}
enum class SearchType : int {
    NONE = 0,
    NAME = 1,
    SOURCE = 2,
    TYPE = 4,
    EXTERNAL_ID = 8,
    ALL = NAME | SOURCE | TYPE | EXTERNAL_ID
};
int operator&(const SearchType& lhs, const SearchType& rhs);
int operator|(const SearchType& lhs, const SearchType& rhs);

class EntityList
{
  public:
    EntityList();
    ~EntityList();
    auto GetWhere(SearchType type, std::string_view value) const -> std::vector<std::shared_ptr<Entity::SQObject>>;
    auto LoadFromFile(std::string_view fname, bool build_map = false) -> bool;
    auto LoadFromFileList(const std::vector<std::string>& filenames, bool build_map = false) -> bool;
    auto LoadFromParentDirectory(const std::string& dir, bool build_map = false) -> bool;
    auto BuildMap() -> void;

  private:
    std::vector<std::shared_ptr<Entity::SQObject>> m_items;
    bool m_map_is_built = false;
    std::unordered_map<std::string, std::shared_ptr<Entity::SQObject>> m_item_map;

  protected:
};
}// namespace Creator
