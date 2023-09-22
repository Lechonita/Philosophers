###############################################################################
#____________________________Makefile for Philo_______________________________#
###############################################################################

NAME = philo

################################## Compiler ##################################

FLAGS = -Wall -Wextra -Werror

ifeq ($(debug), true)
	FLAGS += -g3 -fsanitize=address,undefeined
endif

CC = cc

################################## Includes ###################################

INC_DIR = ./inc
INCLUDES += -I $(INC_DIR)

################################### Sources ####################################

SRC += main.c
SRC += init.c
SRC += libft.c
SRC += utils.c
SRC += error.c
SRC += threads.c
SRC += routine_manager.c
SRC += routine_philo.c

SRC_DIR = ./src
vpath %.c $(SRC_DIR)

################################### Objects ####################################

OBJ_DIR = ./obj
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

################################# Progress Bar #################################

NB_OBJ = ${words ${SRC}}
COUNTER = 1
PROGRESS = 0
DONE = 100
SPACE = 0
FILL = 0
EMPTY = 0

define PROGRESS_BAR
	$(eval PROGRESS=$(shell echo $$(($(COUNTER) * 100 / $(NB_OBJ)))))
	$(eval DONE=$(shell echo $$(($(PROGRESS) * 30 / 100))))
	$(eval SPACE=$(shell echo $$((30 - $(DONE)))))
	$(eval FILL=$(shell printf "%*s" ${DONE} | sed 's/ /▶/g'))
	$(eval EMPTY=$(shell printf "%*s" ${SPACE} | sed 's/ /◀/g'))
	printf "\r${CLEAR}$(BLUE)Compile : $(LGREEN)${FILL}$(LRED)${EMPTY} $(BLUE)%3d%%$(END) %s.c " ${PROGRESS} $1
	$(eval COUNTER=$(shell echo $$(($(COUNTER) + 1))))
endef

#################################### Rules #####################################

all: $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ) : $(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@ $(INCLUDES)
	@$(call PROGRESS_BAR, $(basename $(notdir $<)))

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(LDFLAGS) $(INCLUDES) -o $(NAME) -lpthread
	@echo "\n	⤳$(GREEN) Created $(NAME) ✨\n$(DEF_COLOR)"

# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes -q ./$(NAME)

clean:
	@echo "$(HGREY)Removing .o object files...$(END)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(HGREY)Removing Philo...$(END)"
	@rm -f $(NAME)
	@echo "	⤳$(GREY) All cleaned 🌊\n$(END)"

re: fclean all

.PHONY: all clean fclean re

#################################### Color #####################################

END=\033[0m
RED=\033[1;31m
LRED=\033[38;5;124m
GREEN=\033[1;32m #\033[1;5;32m
LGREEN=\033[38;5;22m
BLUE=\033[1;34m
LBLUE=\033[1;94m
GREY=\033[1;3;90m
HGREY=\033[38;5;235m
DEF_COLOR =	\033[0;39m
BOLD="\033[1m"
UP = "\033[A"
DOWN = "\033[B"
RIGHT = "\033[C"
LEFT = "\033[D"
CUT = "\033[K"
CLEAR = \033[2K
SAVE = "\033[s"
RESTORE = "\033[u"