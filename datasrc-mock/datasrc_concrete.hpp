#ifndef __datasrc_concrete_hpp__
#define __datasrc_concrete_hpp__

// A mock data source.
namespace datasrc
{
  typedef int Db;
  typedef int Iter;
  struct Entry {
    char const* lastName;
    char const* firstName;
  };
}

#endif /* __datasrc_concrete_hpp__ */

