# $Id $

CC = gcc
RM = rm -f
PROF = -O -ggdb
# uncomment the line below to use Cygwin
#CYGWIN = -DCYGWIN
ECHOCMD = echo -e
LIBS = -lcrypt
# Use the line below on linux
EXE = merc
# Use the line below for Cygwin
#EXE = merc.exe

# The colors Duke! The COLORS!
L_NRM     = \e[0;00m
D_RED	  = \e[0;31m
L_RED	  = \e[1;31m
D_GREEN   = \e[0;32m
L_GREEN   = \e[1;32m
D_BROWN   = \e[0;33m
L_YELLOW  = \e[1;33m
D_BLUE	  = \e[0;34m
L_BLUE	  = \e[1;34m
D_PURPLE  = \e[0;35m
L_MAGENTA = \e[1;35m
D_CYAN    = \e[0;36m
L_CYAN    = \e[1;36m
L_GREY	  = \e[0;37m
L_WHITE   = \e[1;37m

# Use these two lines to use crypt(), ie on Linux systems.
C_FLAGS = $(PROF) -Wall
L_FLAGS = $(PROF) -lcrypt

# Uncomment these two lines to use plaintext passwords.
# This is how you fix the 'crypt' linking errors!
#L_FLAGS = $(PROF)
#C_FLAGS = -Wall $(PROF) -DNOCRYPT -DQMFIXES

# Source Files
SRC_FILES := $(wildcard *.c)

# Backup Files
BCK_DIR = backup
BCK_FILES := $(BCK_DIR)/*

# Object Files
OBJ_DIR = obj
OBJ_FILES := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Header Files
H_FILES = $(wildcard *.h)

merc: $(OBJ_FILES)
	@$(ECHOCMD) "$(L_BLUE)[- $(L_WHITE)Rebuilding MUD executable:  $(L_GREEN)merc.exe$(L_BLUE) -]$(L_NRM)"
	@$(ECHOCMD) "$(L_BLUE)[- $(L_YELLOW)**********$(L_CYAN)Compile Complete$(L_YELLOW)**********$(L_BLUE) -]$(L_NRM)"
	@$(CC) $(L_FLAGS) -o $(EXE) $(OBJ_FILES) $(LIBS)

$(OBJ_DIR)/%.o: %.c $(H_FILES)
	@$(ECHOCMD) "$(L_BLUE)-->  $(L_WHITE)Compiling file: $(L_MAGENTA)$<$(L_BLUE)  <--$(L_RED)"
	@$(CC) $(C_FLAGS) -c -o $@ $<
	@$(ECHOCMD) "$(L_BLUE)[-   $(L_YELLOW)$<$(L_NRM) compiled $(L_GREEN)OK$(L_BLUE)   -]$(L_NRM)"

clean:
	@$(ECHOCMD) "$(L_BLUE)-->  $(L_CYAN)Cleaning up for full make...  $(L_BLUE)<-- $(L_NRM)"
	@$(RM) $(OBJ_FILES) $(EXE) ../area/old_$(EXE) ../area/$(EXE) *~ *.bak *.orig *.rej
	@$(ECHOCMD) "$(L_BLUE)[-   $(L_GREEN)done$(L_NRM).    $(L_BLUE)-]$(L_NRM)"

install:
	@$(ECHOCMD) "$(L_BLUE)**** $(L_CYAN)Updating Live Executable $(L_BLUE)****$(L_NRM)"
	@$(RM) $../area/old_$(EXE)
	@mv ../area/$(EXE) ../area/old_$(EXE)
	@cp $(EXE) ../area/$(EXE)
	@$(ECHOCMD) "$(L_GREEN)**** $(L_YELLOW)Live Executable Updated $(L_GREEN)****$(L_NRM)"

cleanup:
	@$(ECHOCMD) "$(L_BLUE)-->  $(L_CYAN)Making clean for backing up  $(L_BLUE)<-- $(L_NRM)"
	@$(RM) $(OBJ_FILES) $(BCK_FILES) $(EXE) ../area/$(EXE) ../area/old_$(EXE) ../log/*.log *~ *.bak *.orig *.rej
	@$(ECHOCMD) "$(L_BLUE)[-   $(L_GREEN)Ready to make a backup now$(L_NRM).   $(L_BLUE)-]$(L_NRM)"
