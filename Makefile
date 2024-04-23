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
    HIT_TOTAL != ${MAKE} ${MAKECMDGOALS} --dry-run ECHO="HIT_MARK" |	\
		grep -c "HIT_MARK"
    HIT_COUNT = $(eval HIT_N != expr ${HIT_N} + 1)${HIT_N}
    ECHO = echo "[`expr ${HIT_COUNT} '*' 100 / ${HIT_TOTAL}`%]"
endif

all:	compile

compile:	$(BIN)

debug:
	@echo "Running debug compilation"
	@make --no-print-directory CFLAGS="$(FLAGS) $(DEBUG_FLAGS)"

%.o:	%.c
	@$(ECHO) "Compiling $@..."
	@$(CC) $(CPPFLAGS) -c $(CFLAGS) $< -o $@

$(BIN):	$(OBJ)
	@$(ECHO) "Linking project..."
	@$(CC) $(OBJ) -o $(BIN) $(CFLAGS)

clean:
	@$(ECHO) "Cleaning project..."
	@rm -f $(OBJ)
	@find . -name *~ -delete
	@find . -name *.vgcore -delete
	@find . -name *.gdb_history -delete
	@find . -name *.swp -delete

fclean:	clean
	@$(ECHO) "Purge of project..."
	@rm -f $(BIN)

re:	fclean	compile

re-debug:	fclean	debug

cs:	fclean
	@echo "Running custom coding style script..."
	@sudo docker run --rm --security-opt "label:disable" -i -v \
		.:"/mnt/delivery" -v .:"/mnt/reports" \
		ghcr.io/epitech/coding-style-checker:latest "/mnt/delivery"	\
		"/mnt/reports"
	@echo "You have `grep -c ": INFO:" "coding-style-reports.log"` infos !"
	@echo "You have `grep -c ": MINOR:" "coding-style-reports.log"` \
 minor errors !"
	@echo "You have `grep -c ": MAJOR:" "coding-style-reports.log"`	\
 major errors !"
	@cat coding-style-reports.log
	@rm -f coding-style-reports.log
