#!/bin/bash

grep --color=auto -nR "// \(TODO\|XXX\|FIXME\)" src/*
