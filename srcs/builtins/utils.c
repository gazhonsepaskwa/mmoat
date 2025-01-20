#include "../../includes/builtins.h"

int	err_msg_cmd(char *cmd, char *arg, char *msg, int code)
{
	ft_put_s_fd(cmd, 2);
	ft_put_s_fd(": ", 2);
	ft_put_s_fd(msg, 2);
	if (arg)
	{
		ft_put_s_fd(": ", 2);
		ft_putendl_fd(arg, 2);
	}
	return (code);
}
