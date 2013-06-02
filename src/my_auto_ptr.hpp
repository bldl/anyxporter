#ifndef __my_auto_ptr_hpp__
#define __my_auto_ptr_hpp__

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

  void set(X* p, OpType* f) throw() {
    clear();
    x = p;
    free_op = f;
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

#endif /* __my_auto_ptr_hpp__ */
