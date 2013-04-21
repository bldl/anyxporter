#lang racket

#|

This is a mock version implemented in standard C++ that just pretends
to export data. Builds Lua from source.

|#

(require "base.rkt")
(require "konffaa/util.rkt")
(require "konffaa/variant.rkt")

(require (only-in "cxx-mock.var.rkt" (klass% super-variant%)))

(define* klass%
   (variant-class
    super-variant%
    (super-new)
    
    (define/override (lua-link-as.attr)
      'source-code)

    )) ;; end class

(define* (info)
  (new klass%)) 
