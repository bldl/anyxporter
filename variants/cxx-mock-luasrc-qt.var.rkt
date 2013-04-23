#lang racket

#|

This is a mock version implemented in standard C++ that just pretends
to export data. Builds Lua from source. Uses qmake to do it, but Qt
Mobility is not used.

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
  
    (define/override (with-qt-mobility.attr)
      #f)
  
    (define/override (lua-link-as.attr)
      'source-code)
    
    (define/override (lua-export-script.attr)
      "contact_to_xml.lua")

    (define/override (component-datasrc.attr)
      'datasrc-mock)

    (define/override (component-ui.attr)
      'ui-qtconsole)

    )) ;; end class

(define* (info)
  (new klass%)) 
