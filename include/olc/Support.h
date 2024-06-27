
#include <iostream>

namespace olc {

__always_inline void unreachable(const char *file, int line, const char *msg) {
#ifndef NDEBUG
  std::fprintf(stderr, "%s:%d: unreachable: %s\n", file, line, msg);
#endif
  __builtin_unreachable();
}

#define olc_unreachable(msg) olc::unreachable(__FILE__, __LINE__, msg)

} // namespace olc
