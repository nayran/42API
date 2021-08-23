#ifndef API_H
# define API_H

# define _GNU_SOURCE
# define PORT 8080
# define UID "HERE"
# define SECRET "HERE"

# include <stdio.h>
# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <curl/curl.h>
# include <mysql/mysql.h>

struct	MemoryStruct {
	char	*memory;
	size_t	size;
};

char	*ft_gettoken(void);
char	*ft_fields(void);
char	*ft_authorization(char *token);
char	*ft_getallinfo(char *login);
char	*ft_mysql(char *info, MYSQL *conn);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_searchjsonobj(char *info, char *obj);
char	*ft_uid(void);
char	*ft_secret(void);
size_t	WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *contxt);
int		ft_ulfius(void);
char	*ft_printmysql(MYSQL *con, char *login);
char	*ft_populateuser(MYSQL *conn, char *info);
char	*ft_populateprojects(MYSQL *conn, char *info);
MYSQL	*ft_connect(void);
char	*ft_populatecursus(MYSQL *conn, char *info);

#endif
