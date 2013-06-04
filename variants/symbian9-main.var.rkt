#lang racket

#|

Self-signed release build for Symbian v9 and higher. Uses mock data to
avoid Qt dependency. Has a C++ standard 'main' function, which works,
but the problem is that cannot see any output if there an exception or
whatever printed to the console, as no console exists. This variant
also has no icon, so will want to use fshell or PyS60 REPL or
something to launch it.

|#

(require "base.rkt")
(require "konffaa/util.rkt")
(require "konffaa/variant.rkt")

(define* klass%
   (variant-class
    symbian-variant%
    (super-new)

    (define/override (feature-console.attr)
      #f)

    (define/override (feature-icon.attr)
      #f)

    (define/override (component-datasrc.attr)
      'datasrc-mock)

    )) ;; end class

(define* (info)
  (new klass%)) 
