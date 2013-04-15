#include "abstract.hpp"

using std::ios_base;

namespace filesys
{
  void fileOpenTruncate(File& f, Path const& p) {
    f.open(p, ios_base::out | ios_base::trunc | ios_base::binary);
  }

  void fileClose(File& f) {
    f.close();
  }

  void fileAppend(File& f, Bytes const& s) {
    f.write(s.data(), s.size());
  }
}

