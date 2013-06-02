# This makefile assumes GNU Make. The command 'in-gnupoc-env' is a
# custom one, setting the environment so that the tools of the
# specified SDK can be run.

BASENAME := app-self

default :
	@echo for making a self-signed code-signing cert for the project

# requires SDK 9.2 for -expdays support
makekeys-make : 
	in-gnupoc-env s60_31 makekeys -cert -password -len 2048 -expdays 3650 $(BASENAME).key $(BASENAME).cer

# an attempt to duplicate what the above appears to do
openssl-make :
	openssl dsaparam -outform PEM -out $(BASENAME).dsaparam 2048 
	openssl gendsa -out $(BASENAME).key $(BASENAME).dsaparam
	openssl req -new -x509 -nodes -sha1 -days 3650 -key $(BASENAME).key > $(BASENAME).cer

openssl-make-rsa : 
	openssl genrsa -out $(BASENAME).key -passout pass:my-secret 2048 
	openssl req -new -x509 -nodes -sha1 -days 3650 -key $(BASENAME).key > $(BASENAME).cer

# If this works, we must be on the right track.
makekeys-view :
	in-gnupoc-env s60_31 makekeys -view $(BASENAME).cer

openssl-view-key :
	openssl dsa -in $(BASENAME).key -text

openssl-view-cert :
	openssl x509 -in $(BASENAME).cer -text

openssl-view : openssl-view-key openssl-view-cert

clean :
	-rm $(BASENAME).key $(BASENAME).cer $(BASENAME).dsaparam

# 
# Copyright 2013 Tero Hasu
# 
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation files
# (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge,
# publish, distribute, sublicense, and/or sell copies of the Software,
# and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
