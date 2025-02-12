make && valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --trace-children=yes --track-fds=all --suppressions=valgrind.supp -s ./minishell
