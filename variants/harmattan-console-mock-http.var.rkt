#lang racket

#|

A Qt-based console program that exports mock data, with an option to
do HTTP uploading. Targeting Harmattan.

This configuration is actually not valid, as Harmattan has Qt 4.7.4,
and hence lacks QHttpPart.

|#

(require "base.rkt")
(require "konffaa/util.rkt")
(require "konffaa/variant.rkt")

(require (only-in "harmattan-console.var.rkt" (klass% parent%)))

(define* klass%
   (variant-class
    parent%
    (super-new)
    
    (define/override (feature-qt-contacts.attr)
      #f)
    
    (define/override (feature-http-post.attr)
      #t)
    
    (define/override (lua-export-script.attr)
      "contact_to_xml.lua")

    (define/override (component-datasrc.attr)
      'datasrc-mock)

    )) ;; end class

(define* (info)
  (new klass%)) 
