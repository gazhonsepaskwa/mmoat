CC = gcc
WFLAGS = -Wall -Werror -Wextra -g -g3 -ggdb
LINK = -lreadline

SRCDIR = srcs
OBJDIR = .objs
INCDIR = includes/
LIBFT_DIR = lib/libft

NAME = minishell
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = $(shell find $(SRCDIR) -name "*.c")
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

CYAN = \033[36m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(WFLAGS) -MMD -MP -I$(INCDIR) -c $< -o $@ $(LINK)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(WFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LINK)
	@echo "$(CYAN)Build completed: $(NAME)$(RESET)"



# test part

TEST_SRCDIR = tests
TEST_OBJDIR = .TEST_objs
TEST_SRCS = $(shell find $(TEST_SRCDIR) -name "*.c")
TEST_OBJS = $(patsubst $(TEST_SRCDIR)/%.c, $(TEST_OBJDIR)/%.o, $(TEST_SRCS))
TEST_DEPS = $(TEST_OBJS:.o=.d)

$(TEST_OBJDIR)/%.o: $(TEST_SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(WFLAGS) -MMD -MP -I$(INCDIR) -c $< -g3 -ggdb -o $@ $(LINK)

tests: $(LIBFT) $(TEST_OBJS)
	@$(CC) $(WFLAGS) $(TEST_OBJS) $(LIBFT) -o test $(LINK)
	@echo "$(CYAN)Test build completed: test$(RESET)"

# test part end



clean:
	@rm -rf $(OBJDIR) $(TEST_OBJDIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(CYAN)Project cleaned$(RESET)"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm $(NAME) test
	@echo "$(CYAN)Executable removed$(RESET)"

re: fclean all

-include $(DEPS) $(TEST_DEPS)
