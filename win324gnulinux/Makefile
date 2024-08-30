#!/usr/bin/env make -f

build: CreateProcessDemo.cpp
	x86_64-w64-mingw32-gcc-win32  CreateProcessDemo.cpp  -o CreateProcessDemo.exe

test: build
	wine CreateProcessDemo.exe explorer.exe

clean:
	rm  -f  CreateProcessDemo.exe

.PHONY: clean

