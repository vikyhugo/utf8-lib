MAKEFILE_PATH := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

.PHONY: all test build always

all: build test

test: build | always
	make -C $(MAKEFILE_PATH)CMakeBinDir test
	
build: | always
	cd $(MAKEFILE_PATH)CMakeBinDir && cmake ..
	make -C $(MAKEFILE_PATH)CMakeBinDir

always:
	mkdir -p $(MAKEFILE_PATH)CMakeBinDir

clean: | always
	rm -rf $(MAKEFILE_PATH)CMakeBinDir $(MAKEFILE_PATH)build
