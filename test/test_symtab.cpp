#include "olc/utils/symtab.h"
#include <cassert>
#include <iostream>

using olc::utils::SymTab;

int main() {
  SymTab<std::string, int> symtab;
  symtab.insert("a", 1);
  symtab.insert("b", 2);

  assert(symtab.lookup("a") == 1);
  assert(symtab.lookup("b") == 2);
  assert(symtab.lookup("c") == 0);
  assert(symtab.lookup("d") == 0);
  assert(symtab.lookup("e") == 0);

  symtab.enterScope();
  symtab.insert("a", 3);
  symtab.insert("c", 4);

  assert(symtab.lookup("a") == 3);
  assert(symtab.lookup("b") == 2);
  assert(symtab.lookup("c") == 4);
  assert(symtab.lookup("d") == 0);
  assert(symtab.lookup("e") == 0);

  symtab.exitScope();
  try {
    symtab.insert("a", 5);
  } catch (const std::exception &e) {
  }
  symtab.insert("d", 6);

  assert(symtab.lookup("a") == 1);
  assert(symtab.lookup("b") == 2);
  assert(symtab.lookup("c") == 0);
  assert(symtab.lookup("d") == 6);
  assert(symtab.lookup("e") == 0);

  std::cout << "Finish symtab test" << std::endl;

  return 0;
}
