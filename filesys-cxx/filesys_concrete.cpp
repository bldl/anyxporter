#include "abstract.hpp"

using std::ios_base;

namespace dataout
{
  void fileOpenTruncate(File& f, Path const& p) {
    f.open(p, ios_base::out | ios_base::trunc | ios_base::binary);
  }

  void fileClose(File& f) {
    f.close();
  }
}

