includes = $(wildcard include/**/*.cc include/*.cc) 
out := $(patsubst include/%.cc,out/%.o,$(includes)) 
bin := $(wildcard src/**/*.cc src/*.cc) 
out4bin := $(patsubst src/%.cc,out/%.o,$(bin)) 
targets := $(patsubst out/%.o,bin/%,$(out4bin)) 

cc := g++-12 -fmodules-ts 
flags := -std=c++23 -fno-exceptions -Werror=return-type

pre-build: $(out) 
build: $(targets)
.PHONY: pre-build build clean clean-all check

$(out):out/%.o:include/%.cc
	$(cc) $(flags) -c $< -o $@

$(out4bin):out/%.o:src/%.cc 
	$(cc) $(flags) -c $< -o $@

$(out4bin):$(out)

$(targets):bin/%:out/%.o
	$(cc) $< $(out) -o $@

clean: 
	-rm -rf $(out4bin) $(targets) $(out)

clean-all: 
	-rm -rf bin/** out/**

check: $(out)
	$(cc) $(flags) -fsyntax-only $(includes) $(bin)