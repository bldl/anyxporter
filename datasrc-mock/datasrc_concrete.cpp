#include "abstract.hpp"

#include "nullptr.hpp"

#include <assert.h>

// A mock data source.
namespace datasrc
{

  static const Entry data[] = {
    {"Fisk", "Ben"},
    {"Murdock", "Wilson"},
    {"Natchios", "Matthew"},
    {"Nelson", "Elektra"},
    {"Urich", "Franklin"},
    {nullptr, nullptr}
  };

  void open(Db& /*db*/) {}

  void close(Db& /*db*/) {}

  void iterator(Db& /*db*/, Iter& iter) {
    iter = 0;
  }

  void atEof(Iter const& iter, bool& res) { 
    res = (data[iter].lastName == nullptr);
  }

  void next(Iter& iter, Entry& h) {
    assert(data[iter].lastName && "iteration past end");
    h = data[iter];
    iter++;
  }

}

