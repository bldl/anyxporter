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
  
  ;; features...
  
  (define/public (feature-gui.attr)
    #f)

  (define/public (feature-debugging.attr)
    #f)

  (define/public (feature-http-post.attr)
    #f)

  ;; tools and libraries...
  
  (define/public (with-qt.attr)
    #f)

  (define/public (with-qt-mobility.attr)
    #f)

  (define/public (with-qt-network.attr)
    (feature-http-post.attr))
  
  (define/public (with-qmake.attr)
    (with-qt.attr))

  (define/public (with-gnumake.attr)
    (not (with-qmake.attr)))

  (define/public (with-magnolia.attr)
    #f)

  ;; runtime...

  (define/public (lua-script-path.attr)
    "lua-src/")

  (define/public (lua-export-script.attr)
    "contact_to_xml.lua")

  (define/public (export-output-file.attr)
    "outfile")

  ;; components...

  (define/public (component-datasrc.attr)
    'datasrc-dummy)
  
  (define/public (component-engine.attr)
    (if (with-magnolia.attr) 'engine-mg 'engine-hw))

  (define/public (component-filesys.attr)
    'filesys-cxx)
  
  (define/public (component-httppost.attr)
    (if (feature-http-post.attr) 'httppost-qt 'httppost-dummy))

  (define/public (component-ui.attr)
    (if (with-qt.attr) 'ui-qtconsole 'ui-console))

  ;; build...

  ;; 'pkg-config, 'dynamic-lib, 'static-lib, or 'source-code
  (define/public (lua-link-as.attr)
    'pkg-config)

  (define/public (lua-link-as-pkg-config.attr)
    (eq? (lua-link-as.attr) 'pkg-config))
  
  (define/public (lua-link-as-source-code.attr)
    (eq? (lua-link-as.attr) 'source-code))
  
  (define/public (srcdirs.attr)
    (cons "src"
          (map
           symbol->string
           (filter identity
                   (list
                    (component-datasrc.attr)
                    (component-engine.attr)
                    (component-filesys.attr)
                    (component-httppost.attr)
                    (component-ui.attr)
                    )))))
  
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
