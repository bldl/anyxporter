#!/bin/sh

SRCDIR=$(dirname $(readlink -f $0))
cd $SRCDIR
exec racket --name "$0" --require variants/konffaa/configure.rkt --main -- ${1+"$@"}

# INTRODUCTION
# 
# This is a script for configuring this project. The idea is simple:
# you choose a single configuration (from variants/), passing its
# name on the command line. This script will then proceed to generate
# a bunch of include files that reflect the configuration. The
# include files are only touched when they actually change as a
# result of the change in configuration; this is to allow this script
# to better work with build tools whose dependency checking is based
# on timestamps.
