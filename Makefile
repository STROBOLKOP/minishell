.DEFAULT_GOAL := $(MKDF)

CC = cc -g

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
	print "usage: make [target]\n\nSet default goal with:\nexport MKDF=[target]\n\n"; \
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

.PHONY: readline
readline: readline.c ##@build Compile readline.c testing file.
	${CC} $< -o $@ -lreadline

.PHONY: ast
ast: ast.c ##@build Compile Abstract Syntax Tree testing file.
	${CC} $< -o $@

.PHONY: token
token: token.c ##@build Compile token testing file.
	${CC} $< -o $@

clean: ##@cleaning rm object files (none in this branch)

fclean: clean ##@cleaning run clean then rm built executables
	rm -f ${TEST_EXECS}

re: fclean ${.DEFAULT_GOAL} ##@build run fclean, then compile default goal.

reall: fclean all ##@build run fclean then run all

.PHONY: help all clean fclean reall re
