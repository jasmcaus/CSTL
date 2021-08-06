.PHONY: all echo

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s
#Suppress display of executed commands.
$(VERBOSE).SILENT:
MAKEFLAGS += --silent

all:
	python3 script.py
.PHONY: all

echo:
	echo Working!
.PHONY: echo


SOURCE_DIR = .
BUILD_DIR = build
# GENERATOR = "MinGW Makefiles"

cmake:
	cmake -S $(SOURCE_DIR) -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug -DCSTL_BUILDINTERNALTESTS=On
	cmake --build $(BUILD_DIR) --config Debug
	echo ------------------ Running Target ------------------
	cd build/bin/ ; ./CSTLInternalTests
.PHONY: cmake

cmakeclean:
	rm -rf build/ && mkdir build
.PHONY: cmakeclean