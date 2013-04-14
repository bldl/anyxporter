#ifndef __my_nullptr_hpp__
#define __my_nullptr_hpp__

// http://gcc.gnu.org/gcc-4.6/changes.html
#if (defined(__GNUC__) && \
     ((__GNUC__ < 4) || (__GNUC__ == 4 && __GNUC_MINOR__ < 6)))
#define nullptr __null
#endif

// non-GCC emulation
// http://stackoverflow.com/questions/2419800/can-nullptr-be-emulated-in-gcc
#if 0
const class {
public:
  template<class T>
  operator T*() const
  { return 0; }

  template<class C, class T>
  operator T C::*() const
  { return 0; }

private:
  void operator&() const;
} nullptr = {};
#endif

#endif /* __my_nullptr_hpp__ */

