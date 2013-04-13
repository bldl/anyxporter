#lang racket

(require "util/module.rkt")
(provide (all-from-out "util/module.rkt"))

(require* "util/print.rkt")
(require* "util/let.rkt")

(define-syntax* fix
  (syntax-rules ()
    ((_ fn arg ...)
     (lambda rest (apply fn arg ... rest)))))

(define* (path-basename path)
  (let-values 
      (((base name dir) (split-path path)))
    name))

(define* (true? x)
  (and x #t))

(define* (symbol<? s1 s2)
  (string<? (symbol->string s1) (symbol->string s2)))

(define* (symbol-sort lst)
  (sort lst symbol<?))

(define* (sublist? s lst)
  (true? (andmap (lambda (x) (memq x lst)) s)))

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