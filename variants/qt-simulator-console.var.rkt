#lang racket

#|

A Qt-based console program that uses the Qt Mobility APIs for
exporting contact data. Note that this variant cannot be built for the
desktop as the Mobility APIs are not available. Qt Simulator can be
targeted, however, but building and running then requires Qt Creator,
apparently.

|#

(require "base.rkt")
(require "konffaa/util.rkt")
(require "konffaa/variant.rkt")

(define* klass%
   (variant-class
    project-variant%
    (super-new)
    
    (define/override (platform)
      'qt-simulator)
    
    (define/override (with-qt.attr)
      #t)
  
    (define/override (srcdirs.attr)
      (append (super srcdirs.attr)
              (list "qtconsole-ui"
                    "datasrc-qt")))
    
    )) ;; end class

(define* (info)
  (new klass%)) 
