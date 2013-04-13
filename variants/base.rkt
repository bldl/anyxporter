#lang racket

#|

This file defines the API that all the variant specifications of this
project must implement.

|#

(require "konffaa/util.rkt")
(require "konffaa/variant.rkt")

;;; 
;;; base variants
;;; 

(define-variant* project-variant% variant%
  (super-new)

  (define/public (platform) 'cxx) ;; standard C++

  (define/public (platform-str.attr) (symbol->string (platform)))
  
  (define/public (app-basename.attr) "exportemplapp")
  
  (define/public (app-short-name.attr) "ExporTempl")

  (define/public (app-long-name.attr) "ExporTemplApp")

  (define/public (app-name.attr) (app-short-name.attr))

  (define/public (vendor-name.attr) "BLDL")

  (define/public (major-version.attr) 0)
  
  (define/public (minor-version.attr) 1)
  
  (define/public (version100.attr)
    (+ (* (major-version.attr) 100) (minor-version.attr)))
  
  (define/public (version-string.attr)
    (real->decimal-string
     (+ (major-version.attr) (/ (minor-version.attr) 100)) 2))

  ;; platforms...
  
  (define/public (is-harmattan.attr) (eq? (platform) 'harmattan))
  
  (define/public (is-symbian.attr) (eq? (platform) 'symbian))

  (define/public (is-device.attr)
    (true? (memq (platform) '(harmattan symbian))))
  
  (define/public (is-qt-simulator.attr)
    (eq? (platform) 'qt-simulator))
  
  ;; tools and libraries...
  
  (define/public (with-qt.attr)
    #f)

  (define/public (with-qt-mobility.attr)
    (with-qt.attr))

  (define/public (with-qmake.attr)
    (with-qt.attr))

  (define/public (with-gnumake.attr)
    (not (with-qmake.attr)))

  (define/public (with-magnolia.attr)
    #f)

  ;; features...
  
  (define/public (feature-gui.attr)
    #f)

  (define/public (feature-debugging.attr)
    #f)

  ;; build...
  
  (define/public (srcdirs.attr)
    (list "src"
          (if (with-magnolia.attr) "engine-mg" "engine-hw")
          "filesys-cxx"))
  
  ) ;; end project-variant%

#|

Copyright 2009 Helsinki Institute for Information Technology (HIIT)
and the authors. All rights reserved.

Authors: Tero Hasu <tero.hasu@hut.fi>

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

|#
