make && valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --trace-children=yes --suppressions=/home/nalebrun/git/minishell/valgrind.supp -s ./minishell
