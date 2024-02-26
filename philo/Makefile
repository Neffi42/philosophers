### PROGRAM NAME ###
NAME		:= philo

### UTILS ###
CC 			:= clang
CFLAGS 		:= -Wall -Wextra -Werror -g3 -pthread
ifeq (thread, $(filter thread,$(MAKECMDGOALS)))
	CFLAGS += -fsanitize=thread
endif
ifeq (leak, $(filter leak,$(MAKECMDGOALS)))
	CFLAGS += -fsanitize=leak
endif
DEP_FLAGS	:= -MMD -MP
MAKE_FLAG 	:= --no-print-directory --silent
RM 			:= rm -rf

### DIRECTORIES ###
SRC_DIR 	:= src
INCLD_DIR 	:= include
OBJS_DIR 	:= objs

### FILES ###
SRC 		:=	ft_utils.c \
				ft_utils2.c \
				inits.c \
				main.c \
				routine_utils.c \
				routine.c \
				utils.c
INCLUDES	:=	$(INCLD_DIR)
INCLD_FLAG 	:= 	$(addprefix -I , $(INCLUDES))
OBJS 		:= 	$(patsubst %.c,$(OBJS_DIR)/%.o,$(SRC))
DEPS		:= 	$(patsubst %.c,$(OBJS_DIR)/%.d,$(SRC))

### COLORS ###
DEFAULT    	:= \033[0m
BLACK    	:= \033[0;30m
RED        	:= \033[0;31m
GREEN    	:= \033[0;32m
UGREEN    	:= \033[4;32m
YELLOW    	:= \033[;33m
BLUE    	:= \033[0;34m
PURPLE    	:= \033[0;35m
CYAN    	:= \033[0;36m
BWHITE    	:= \033[1;37m
NEW			:= \r\033[K

### PROJECT ###
.PHONY: all clean fclean re thread leak norm
all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(NEW)$(PURPLE)[$(NAME)] $(UGREEN)Building:$(DEFAULT)$(BWHITE) $@$(DEFAULT)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) $(INCLD_FLAG) -o $@
	@printf "\n"

-include $(DEPS)
$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "$(NEW)$(PURPLE)[$(NAME)] $(UGREEN)Building:$(DEFAULT) $<"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(DEP_FLAGS) $(CFLAGS) $(INCLD_FLAG) -c $< -o $@

clean: ; @printf "$(PURPLE)[$(NAME)] $(RED)Removing $(DEFAULT)$(OBJS_DIR) files\n"
	@$(RM) $(OBJS_DIR)

fclean: clean ; @printf "$(PURPLE)[$(NAME)] $(RED)Removing $(DEFAULT)$(NAME)\n"
	@$(RM) $(NAME)

re: fclean all

thread: re

leak: re

### NORM ###
norm:
	@norminette $(SRC_DIR) $(INCLD_DIR) | awk '/Error/ {print; found=1} END \
	{if (!found) {print "$(PURPLE)[$(NAME)] $(DEFAULT)Norm: $(BWHITE)OK$(DEFAULT)"; exit 0 }; exit 1 }'
