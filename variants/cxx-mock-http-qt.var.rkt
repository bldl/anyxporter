#lang racket

#|

This is a mock version implemented in standard C++ that just pretends
to export data. Implements HTTP POST based uploading using Qt APIs.
This variant is handy for testing uploading on the PC.

|#

(require "base.rkt")
(require "konffaa/util.rkt")
(require "konffaa/variant.rkt")

(define* klass%
   (variant-class
    project-variant%
    (super-new)
    
    (define/override (with-qt.attr)
      #t)
  
    (define/override (feature-http-post.attr)
      #t)
    
    (define/override (lua-export-script.attr)
      "contact_to_xml.lua")

    (define/override (component-datasrc.attr)
      'datasrc-mock)

    (define/override (component-ui.attr)
      'ui-qtconsole)
    
    )) ;; end class

(define* (info)
  (new klass%)) 
