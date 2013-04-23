#lang racket

#|

This is a mock version implemented in standard C++ that just pretends
to export data.

|#

(require "base.rkt")
(require "konffaa/util.rkt")
(require "konffaa/variant.rkt")

(define* klass%
   (variant-class
    project-variant%
    (super-new)
    
    (define/override (component-datasrc.attr)
      'datasrc-mock)

    (define/override (component-ui.attr)
      'ui-console)
    
    )) ;; end class

(define* (info)
  (new klass%)) 
