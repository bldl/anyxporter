#lang racket

#|

Self-signed release build for Symbian v9 and higher.
Uses mock data to avoid Qt dependency.

|#

(require "base.rkt")
(require "konffaa/util.rkt")
(require "konffaa/variant.rkt")

(define* klass%
   (variant-class
    symbian-variant%
    (super-new)

    (define/override (component-datasrc.attr)
      'datasrc-mock)

    ;; works with these but with numerous warnings
    ;;(define/override (gcc-name.attr) "gcce-2011.09")
    ;;(define/override (gcc-cxx-flags.attr) '("-std=c++0x"))
  
    )) ;; end class

(define* (info)
  (new klass%)) 
