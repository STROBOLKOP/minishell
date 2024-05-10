CC = cc

#COLORS
GREEN  := $(shell tput -Txterm setaf 2)
WHITE  := $(shell tput -Txterm setaf 7)
YELLOW := $(shell tput -Txterm setaf 3)
RESET  := $(shell tput -Txterm sgr0)

SRCS = $(wildcard *.c)
TEST_EXECS = ${SRCS:.c=}

HELP_DOCS = \
	%help; \
	while(<>) { push @{$$help{$$2 // 'options'}}, [$$1, $$3] if /^([\w\-]+)\s*:.*\#\#(?:@([\w\-]+))?\s(.*)$$/ }; \
	print "usage: make [target]\n\n"; \
	for (sort keys %help) { \
	print "${WHITE}$$_:${RESET}\n"; \
	for (@{$$help{$$_}}) { \
	$$sep = " " x (32 - length $$_->[0]); \
	print "  ${YELLOW}$$_->[0]${RESET}$$sep${GREEN}$$_->[1]${RESET}\n"; \
	}; \
	print "\n"; }

help: ##@other Show this help.
	@perl -e '$(HELP_DOCS)' $(MAKEFILE_LIST)

all: readline ##@build Compile all the test files.

readline: readline.c ##@build compile readline.c testing file.
	${CC} -lreadline $< -o $@

clean: ##@cleaning rm object files (none in this branch)

fclean: clean ##@cleaning runs clean then rm built executables
	rm -f ${TEST_EXECS}

reall: fclean all ##@build runs fclean then runs all

.PHONY: help all clean fclean reall
