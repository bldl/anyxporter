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
    
    (define/override (srcdirs.attr)
      (append (super srcdirs.attr)
              (list "ui-console"
                    "datasrc-mock")))
    
    )) ;; end class

(define* (info)
  (new klass%)) 
