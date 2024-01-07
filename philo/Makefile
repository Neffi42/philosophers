### PROGRAM NAME ###
NAME		:= philo

### UTILS ###
CC 			:= cc
CFLAGS 		:= -Wall -Wextra -Werror -g3 -pthread
RM 			:= rm -rf
MAKE_FLAG 	:= --no-print-directory --silent
DEFAULT    	:= \033[0m
BLACK    	:= \033[0;30m
RED        	:= \033[0;31m
GREEN    	:= \033[0;32m
YELLOW    	:= \033[0;33m
BLUE    	:= \033[0;34m
PURPLE    	:= \033[0;35m
CYAN    	:= \033[0;36m
BWHITE    	:= \033[1;37m

### DIRECTORIES ###
SRC_DIR 	:= src
INCLD_DIR 	:= include
OBJS_DIR 	:= objs

### FILES ###

define SRC 	:=
	ft_utils.c
	main.c
	utils.c
endef
SRC 		:= $(strip $(SRC))

define INCLUDES	:=
	$(INCLD_DIR)/
endef
INCLUDES 	:= $(strip $(INCLUDES))

OBJS 		:= $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRC))

INCLD_FLAG 	:= $(addprefix -I , $(INCLUDES))

### PROJECT ###
.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)* Assembling $(BWHITE)$@$(DEFAULT)"
	@$(CC) $(CFLAGS) $(OBJS) $(INCLD_FLAG) -o $@

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(CYAN)- Compiling$(DEFAULT) $<"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLD_FLAG) -c $< -o $@

.PHONY: clean
clean:
	@echo "$(RED)! Removing$(DEFAULT) $(OBJS_DIR) files"
	@$(RM) $(OBJS_DIR)

.PHONY: fclean
fclean: clean
	@echo "$(RED)! Removing$(DEFAULT) $(NAME)"
	@$(RM) $(NAME)

.PHONY: re
re: fclean all

### NORM ###
.PHONY: norm
norm:
	@norminette $(SRC_DIR) $(INCLD_DIR) | awk '/Error/ {print; found=1} END \
	{if (!found) {print "$(PURPLE)Norm OK$(DEFAULT)"; exit 0 }; exit 1 }'
