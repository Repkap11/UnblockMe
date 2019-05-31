MAKEFILES := Makefile
CPUS ?= $(shell nproc || echo 1)

#MAKEFLAGS += -k #Continue after failed targets
MAKEFLAGS += -r #Don't use build in commands
#MAKEFLAGS += -s #Be silent on stdout
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --jobs=$(CPUS)

TARGET := unblock

CFLAGS := -Wall -Wextra -Werror -std=c++98 -Wno-unused-parameter -Wno-unused-variable -fno-pie -march=native
INCLUDES := -I include/

#CFLAGS += -O3 -DREPGAME_FAST
CFLAGS += -g

LIBS := -l m

CC := g++
#CC := clang++

ifeq ($(CC),g++)
CFLAGS += -no-pie
endif
LD := ld

OBJECTS := $(patsubst src/%.cpp,out/%.o, $(wildcard src/*.cpp))
DEPS := $(patsubst src/%.cpp,out/%.d, $(wildcard src/*.cpp))

CC := ccache $(CC)
LD := ccache $(LD)

solve: all
	python3 solve.py

run: all
	./$(TARGET)

all: $(TARGET)

out:
	mkdir -p out

out/%.o: src/%.cpp $(MAKEFILES) | out
	@#Use g++ to build o file and a dependecy tree .d file for every cpp file
	$(CC) $(INCLUDES) $(CFLAGS) -MMD -MP -MF $(patsubst %.o,%.d,$@) -MT $(patsubst %.d,%.o,$@) -c $< -o $@

$(TARGET): $(OBJECTS) $(MAKEFILES)
	$(CC) -flto $(CFLAGS) $(OBJECTS) $(LIBS) -o $@

-include $(DEPS)

clean:
	rm -rf out

install:
	sudo apt install python3-pip
	pip3 install adbutils numpy matplotlib opencv-python

.PRECIOUS: $(TARGET) $(OBJECTS)

.PHONY: all run install clean