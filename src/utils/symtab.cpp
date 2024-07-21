#include "olc/utils/symtab.h"
#include <utility>

namespace olc::utils {

template <typename SYM, typename DAT> SymTab<SYM, DAT>::SymTab() {
  enterScope();
}

template <typename SYM, typename DAT>
DAT SymTab<SYM, DAT>::lookup(const SYM &name) const {
  for (auto it = symtab_.rbegin(); it != symtab_.rend(); ++it) {
    auto jt = it->find(name);
    if (jt != it->end()) {
      return jt->second;
    }
  }
  return {};
}

template <typename SYM, typename DAT>
void SymTab<SYM, DAT>::insert(const SYM &name, const DAT &data) {
  symtab_.back().insert(std::pair<SYM, DAT>(name, data));
}

template <typename SYM, typename DAT> void SymTab<SYM, DAT>::enterScope() {
  symtab_.push_back(std::unordered_map<SYM, DAT>());
}

template <typename SYM, typename DAT> void SymTab<SYM, DAT>::exitScope() {
  symtab_.pop_back();
}

template class SymTab<std::string, int>; // for test

} // namespace olc::utils
