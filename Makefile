CC = gcc
WFLAGS = -Wall -Werror -Wextra -g -g3 -ggdb
LINK = -lreadline

SRCDIR = srcs
OBJDIR = .objs
INCDIR = includes/
LIBFT_DIR = lib/libft

NAME = minishell
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_SRCS := $(shell find $(LIBFT_DIR) -name "*.c")

SRCS = $(shell find $(SRCDIR) -name "*.c")
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

CYAN = \033[36m
YELLOW = \033[33m
RESET = \033[0m

.PHONY: all clean fclean re libft

all: $(NAME)

$(LIBFT): $(LIBFT_SRCS)
	@make -C $(LIBFT_DIR) all > /dev/null
	@echo "$(YELLOW)[LIBFT] Created$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(WFLAGS) -MMD -MP -I$(INCDIR) -D DIO_PATH="\"$(HOME)/ast.xml\"" -c $< -o $@ $(LINK)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(WFLAGS) $(OBJS) $(LIBFT) -D DIO_PATH="\"$(HOME)/ast.xml\"" -o $(NAME) $(LINK)
	@echo "$(CYAN)Build completed: $(NAME)$(RESET)"

clean:
	@make -C $(LIBFT_DIR) clean > /dev/null
	@echo "$(YELLOW)[LIBFT] Object files removed$(RESET)"
	@rm -rf $(OBJDIR)
	@echo "$(CYAN)Project cleaned$(RESET)"

fclean: clean
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@echo "$(YELLOW)[LIBFT] Removed$(RESET)"
	@rm -rf $(NAME)
	@echo "$(CYAN)Executable removed$(RESET)"

re: fclean all

-include $(DEPS) $(TEST_DEPS)
