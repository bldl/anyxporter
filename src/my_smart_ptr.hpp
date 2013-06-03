#ifndef __my_smart_ptr_hpp__
#define __my_smart_ptr_hpp__

#include "my_platform.h"

// An API similar to that of auto_ptr class, declared in ISO/IEC
// 14882, section 20.4.5. This API is smaller, but allows for the
// cleanup operation to be specified.
template <typename X, typename OpType>
class auto_ptr_op {
public:
  typedef X element_type;
 
  auto_ptr_op() throw() : 
    x(0), free_op(0) {}

  auto_ptr_op(X* obj, OpType* f) throw() : 
    x(obj), free_op(f) {}

  ~auto_ptr_op() throw() { 
    clear(); 
  }
 
  X&     operator*() const throw() { return *x; }
  X*     operator->() const throw() { return x; }
  X*     get() const throw() { return x; }

  X* release() throw() {
    X* p = x;
    x = 0;
    return p;
  }

  void clear() throw() {
    if (x) 
      (*free_op)(x);
    x = 0;
  }

  void reset(X* p, OpType* f) throw() {
    if (p != x) {
      clear();
      x = p;
      free_op = f;
    }
  }

  void set(auto_ptr_op<X, OpType>& p) throw() {
    if (this != &p) {
      clear();
      x = p.x;
      free_op = p.free_op;
      p.x = 0;
    }
  }

private:
  X* x;
  OpType* free_op;
};

/* std::unique_ptr defaults to std::default_delete<T>
   as the freeing operation, but we avoid being fancy
   for maximal compatibility. This is inline code anyway. */
template <typename X>
class auto_ptr_delete {
public:
  typedef X element_type;
 
  auto_ptr_delete() throw() : 
    x(0) {}

  explicit auto_ptr_delete(X* obj) throw() : 
    x(obj) {}

  ~auto_ptr_delete() throw() { 
    clear(); 
  }
 
  X&     operator*() const throw() { return *x; }
  X*     operator->() const throw() { return x; }
  X*     get() const throw() { return x; }

  X* release() throw() {
    X* p = x;
    x = 0;
    return p;
  }

  void clear() throw() {
    if (x) 
      delete x;
    x = 0;
  }

  void reset(X* p = 0) throw() {
    if (p != x) {
      clear();
      x = p;
    }
  }

  void set(auto_ptr_delete<X>& p) throw() {
    if (this != &p) {
      clear();
      x = p.x;
      p.x = 0;
    }
  }

private:
  X* x;
};

#if HAVE_MOVE_SEMANTICS
#include <memory>
#define UNIQUE_PTR std::unique_ptr
#else
#define UNIQUE_PTR auto_ptr_delete
#endif

#endif /* __my_smart_ptr_hpp__ */
