#include "api.h"

/*
 *		Retorna um query para criar a tabela users.
 */

char	*ft_createuserquery(void)
{
	return ("CREATE TABLE IF NOT EXISTS users(id INT PRIMARY KEY, "\
			 "login VARCHAR(15), email VARCHAR(100), first_name VARCHAR(25), "\
			 "last_name VARCHAR(50), staff VARCHAR(10), created_at VARCHAR(25),"\
			 "updated_at VARCHAR(25))");
}

/*
 *		Busca no JSON as informacoes escolhidas e retorna elas parseadas.
 */

char	*ft_userinfos(char *info, int x)
{
	char	*userinfos[8] = {"id", "login", "email", "first_name", "last_name",
		"staff?", "created_at", "updated_at"};

	return (ft_searchjsonobj(info, userinfos[x]));
}

/*
 *		Faz o parsing das informacoes do json, montando um query para depois
 *		inserir os dados na tabela.
 */

char	*ft_insertuserquery(char *info)
{
	char	*query;
	char	*id;
	int		x;

	x = 0;
	id = ft_userinfos(info, x);
	query = ft_strjoin("INSERT INTO users VALUES(", id);
	query = ft_strjoin(query, ", \'");
	while (++x < 8)
	{
		if (x > 1)
			query = ft_strjoin(query, "\', \'");
		query = ft_strjoin(query, ft_userinfos(info, x));
	}
	query = ft_strjoin(query, "\')");
	return (query);
}

/*
 *		Cria a tabela users caso nao exista e popula a mesma com as informacoes
 *		recebidas pela variavel info. Retorna para a funcao de criacao e
 *		populacao da tabela projetos.
 */

char	*ft_populateuser(MYSQL *conn, char *info)
{	
	char	*query;

	if (mysql_query(conn, ft_createuserquery()))
		return ("Falha ao criar tabela user!\n");
	query = ft_insertuserquery(info);
	if (mysql_query(conn, query))
	{
		mysql_query(conn, ft_strjoin("DELETE FROM users WHERE id = ", ft_userinfos(info, 0)));
		if (mysql_query(conn, query))
			return ("Falha inserir dados na tabela user!\n");
	}
	free (query);
	return (ft_populateprojects(conn, info));
}
