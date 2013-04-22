#lang racket

#|

A Qt-based console program that uses the Qt Mobility APIs for
exporting contact data. Targeting Harmattan. Note that this variant
cannot be built for the desktop as the Mobility APIs are not
available.

|#

(require "base.rkt")
(require "konffaa/util.rkt")
(require "konffaa/variant.rkt")

(define* klass%
   (variant-class
    project-variant%
    (super-new)
    
    (define/override (platform)
      'harmattan)
    
    (define/override (with-qt.attr)
      #t)
  
    (define/override (with-qt-mobility.attr)
      #t)
  
    (define/override (lua-link-as.attr)
      'source-code)
    
    (define/override (lua-script-path.attr)
      "lua-src/") ;; xxx for now, later install path

    (define/override (lua-export-script.attr)
      "qt_contact_to_xml.lua")

    (define/override (srcdirs.attr)
      (append (super srcdirs.attr)
              (list "ui-qtconsole"
                    "datasrc-qt")))
    
    )) ;; end class

(define* (info)
  (new klass%)) 