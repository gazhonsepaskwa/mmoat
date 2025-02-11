make && valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=valgrind.supp -s ./minishell
