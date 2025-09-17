# compiler to use
CXX = g++

# compiler flags
# -std=c++17 : use the C++17 standard
# -Wall      : enable warnings
# -Wextra    : enable extra warnings
# -O2        : optimize code for better performance
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# grabs all .cpp files in the current directory
SRCS = $(wildcard *.cpp)

# grabs all the .h files in the current directory
HEADERS = $(wildcard *.h)

# grabs the corresponding .o files for the .cpp files 
# after compiling them
OBJS = $(SRCS:.cpp=.o)

# base name of the output executable (without extension)
TARGET_BASE = gnuish-shell

# use > as the recipe prefix instead of a tab
# because I kept getting "missing separator" errors
.RECIPEPREFIX = >

# default variables
EXE =                          # Linux executables have no extension
RUN = ./$(TARGET_BASE)         # the program to run 
RM  = rm -f                    # delete files

# Windows-specific overrides
ifeq ($(OS),Windows_NT)
    EXE = .exe
    # if using a Unix-like shell (MSYS/Git Bash), use Unix commands
    ifneq (,$(findstring sh,$(SHELL)))
        RUN = ./$(TARGET_BASE)$(EXE)
        RM  = rm -f
    else # for CMD or PowerShell
        RUN = .\$(TARGET_BASE)$(EXE)
        RM  = del /q
    endif
endif

# final executable name
# gnuish-shell.exe on Windows, gnuish-shell on Linux
TARGET := $(TARGET_BASE)$(EXE)

# build the program :)
all: $(TARGET)

# link the object files to create the final executable
$(TARGET): $(OBJS)
> $(CXX) $(OBJS) -o $@

# compile header files into object files
%.o: %.cpp $(HEADERS)
> $(CXX) $(CXXFLAGS) -c $< -o $@

# build the target if needed and run it with optional arguments
run: $(TARGET)
> $(RUN) $(ARGS)

# delete object files and the executable
clean:
> -$(RM) $(OBJS) $(TARGET)

# declare phony targets (not real files)
.PHONY: all run clean
