##
## EPITECH PROJECT, 2024
## Panoramix
## File description:
## Makefile
##

SRC	=	$(wildcard src/*.c)
OBJ	=	$(SRC:.c=.o)
BIN	=	panoramix

FLAGS	=	-Wall -Wextra -Werror -I./includes/

DEBUG_FLAGS	=	-g3 -DDEBUG

CFLAGS ?=	$(FLAGS)

ifndef ECHO
    HIT_TOTAL != ${MAKE} ${MAKECMDGOALS} --dry-run ECHO="HIT_MARK" | grep -c "HIT_MARK"
    HIT_COUNT = $(eval HIT_N != expr ${HIT_N} + 1)${HIT_N}
    ECHO = echo "[\033[90m`expr ${HIT_COUNT} '*' 100 / ${HIT_TOTAL}`%\033[0m]"
endif

all:	compile

compile:	$(BIN)

debug:
	@echo "Running debug compilation"
	@make --no-print-directory CFLAGS="$(FLAGS) $(DEBUG_FLAGS)"

%.o:	%.c
	@$(ECHO) "\033[92mCompiling $@...\033[0m"
	@$(CC) $(CPPFLAGS) -c $(CFLAGS) $< -o $@

$(BIN):	$(OBJ)
	@$(ECHO) "\033[92mLinking project...\033[0m"
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS)

clean:
	@$(ECHO) "\033[92mCleaning project...\033[0m"
	@rm -f $(OBJ)
	@find . -name *~ -delete
	@find . -name *.vgcore -delete
	@find . -name *.gdb_history -delete
	@find . -name *.swp -delete

fclean:	clean
	@$(ECHO) "\033[92mPurge of project...\033[0m"
	rm -f $(BIN)

re:	fclean	compile

re-debug:	fclean	debug

cs:	fclean
	@echo "\033[92mRunning custom coding style script...\033[0m"
	@sudo docker run --rm --security-opt "label:disable" -i -v .:"/mnt/delivery" -v .:"/mnt/reports" ghcr.io/epitech/coding-style-checker:latest "/mnt/delivery" "/mnt/reports"
	@echo -e "You have \033[94m`grep -c ": INFO:" "coding-style-reports.log"`\033[0m infos !"
	@echo -e "You have \033[93m`grep -c ": MINOR:" "coding-style-reports.log"`\033[0m minor errors !"
	@echo -e "You have \033[91m`grep -c ": MAJOR:" "coding-style-reports.log"`\033[0m major errors !"
	@echo "===== INFOS ====="
	@cat coding-style-reports.log | grep ": INFO:"
	@echo "===== MINORS ====="
	@cat coding-style-reports.log | grep ": MINOR:"
	@echo "===== MAJORS ====="
	@cat coding-style-reports.log | grep ": MAJOR:"
	@rm -f coding-style-reports.log
