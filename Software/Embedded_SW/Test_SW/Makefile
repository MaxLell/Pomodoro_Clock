# This Makefile requires an installation of CPPCheck and clang-format
# If this is not wanted, please remove the section "tidy"
COMMON_DIRS =
COMMON_DIRS +=../Pomodoro_Clock_HW/User/UnityTest

# Build Targets
TARGET_EXEC=exec.out
TARGET_TEST=test_runner.out

# Source Code
CODEDIRS_EXEC=./app $(COMMON_DIRS)
INCDIRS_EXEC=$(COMMON_DIRS)

# Test Code
UNITY_ROOT=./tests/unity_lib
SRC_DIRS_TEST=$(UNITY_ROOT) ./tests $(COMMON_DIRS)
INC_DIRS_TEST=$(UNITY_ROOT) $(COMMON_DIRS)

CC=gcc
OPT=-O0
# generate files that encode make rules for the .h dependencies
DEPFLAGS=-MP -MD

CFLAGS_EXEC=-Wall -Wextra -g $(foreach D,$(INCDIRS_EXEC),-I$(D)) $(OPT) $(DEPFLAGS)
SRC_FILES_EXEC=$(foreach D,$(CODEDIRS_EXEC),$(wildcard $(D)/*.c))
OBJECTS_EXEC=$(patsubst %.c,%.o,$(SRC_FILES_EXEC))
DEPFILES_EXEC=$(patsubst %.c,%.d,$(SRC_FILES_EXEC))

CFLAGS_TEST=-Wall -Wextra -g $(foreach D,$(INC_DIRS_TEST),-I$(D)) $(OPT) $(DEPFLAGS)
SRC_FILES_TEST=$(foreach D,$(SRC_DIRS_TEST),$(wildcard $(D)/*.c))
OBJECTS_TEST=$(patsubst %.c,%.o,$(SRC_FILES_TEST))
DEPFILES_TEST=$(patsubst %.c,%.d,$(SRC_FILES_TEST))


##########################
########## APP ###########
##########################

all: show_compile_msg $(TARGET_EXEC) test tidy

show_compile_msg:
	@echo " "
	@echo "-----------------------------------------------------------------"
	@echo "---------------------- RUN COMPILER -----------------------------"
	@echo "-----------------------------------------------------------------"
	@echo " "

$(TARGET_EXEC): $(OBJECTS_EXEC)
	
	$(CC) $(CFLAGS_EXEC) $(SRC_FILES_EXEC) -o $(TARGET_EXEC)

##########################
########## TEST ##########
##########################

test: $(TARGET_TEST)

$(TARGET_TEST): $(OBJECTS_TEST)
	$(CC) $(CFLAGS_TEST) $(SRC_FILES_TEST) -o $(TARGET_TEST)
	@echo " "
	@echo "-----------------------------------------------------------------"
	@echo "---------------------- RUN TESTS --------------------------------"
	@echo "-----------------------------------------------------------------"
	@echo " "
	./$(TARGET_TEST)

clean:
	@rm -rf $(TARGET_EXEC) $(OBJECTS_EXEC) $(DEPFILES_EXEC)
	@rm -rf $(TARGET_TEST) $(OBJECTS_TEST) $(DEPFILES_TEST)
	@- rm -r *.dSYM
	@- rm *.d
	@rm *.out
	
tidy:
	@echo " "
	@echo "-----------------------------------------------------------------"
	@echo "---------------------- RUN LINTER -------------------------------"
	@echo "-----------------------------------------------------------------"
	@echo " "

	cppcheck $(SRC_FILES_EXEC)
#	cppcheck --addon=misra.py $(SRC_FILES_EXEC)
#   cpplint $(SRC_FILES_EXEC)
	
	@clang-format --style=Google -i $(SRC_FILES_EXEC) $(SRC_FILES_TEST)

# REMOVE THIS SECTION FOR LARGE PROJECTS - FOR SMALL PROJECTS THAT TIDIES UP 
# ALL THE INTERMEDIATE FLUFF THAT IS GENERATED DURING COMPILATION
	@rm -rf $(OBJECTS_EXEC) $(DEPFILES_EXEC)
	@rm -rf $(OBJECTS_TEST) $(DEPFILES_TEST)
	@rm -r *.dSYM
	@rm *.d
	@rm *.out
	

# shell commands are a set of keystrokes away
distribute: clean
	zip -r Simple_Database.zip *

# @ silences the printing of the command
# $(info ...) prints output
diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git diff --stat

# include the dependencies
-include $(DEPFILES_EXEC) 
-include $(DEPFILES_TEST)

# add .PHONY so that the non-targetfile - rules work even if a file with the same name exists.
.PHONY: all clean test tidy distribute diff

