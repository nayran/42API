#include "api.h"

/*
 *		Recebe um query, executa no DB e retorna o resultado da operacao.
 */

MYSQL_RES	*ft_query_to_res(MYSQL *conn, char *query)
{
	mysql_query(conn, query);
	return (mysql_store_result(conn));
}

/*
 *		Busca no DB o ultimo projeto entregue pelo login.
 */

char	*ft_lastproject(MYSQL *conn, char *login)
{
	char		*query;
	MYSQL_ROW	row;
	MYSQL_RES	*result;

	asprintf(&query, "SELECT project_name FROM projects WHERE user_login = "\
			"'%s' ORDER BY marked_at DESC", login);
	result = ft_query_to_res(conn, query);
	row = mysql_fetch_row(result);
	return (row[0]);
}

/*
 *		Busca no DB o tempo que o usuario gastou no projeto.
 */

char	*ft_timeonproject(MYSQL *conn, char *res, char *login)
{
	char		*query;
	MYSQL_ROW	row;
	MYSQL_RES	*result;

	asprintf(&query, "SELECT TIMESTAMPDIFF(DAY, created_at, marked_at) FROM "\
		"projects WHERE project_name = '%s' AND user_login = '%s'",
		ft_lastproject(conn, login), login);
	result = ft_query_to_res(conn, query);
	row = mysql_fetch_row(result);
	asprintf(&res, "%sTempo no ultimo projeto:\t %s dias\n", res, row[0]);
	return (res);
}

/*
 *		Busca no DB o numero de projetos finalizados pelo usuario.
 */

char	*ft_numofprojects(MYSQL *conn, char *res, char *login)
{
	char		*query;
	MYSQL_RES	*result;

	asprintf(&query, "SELECT * FROM projects WHERE user_login = '%s'"\
			"and status = 'finished'", login);
	result = ft_query_to_res(conn, query);
	asprintf(&res, "%sNumero de projetos entregues:\t %ld\n",
		res, mysql_num_rows(result));
	return (res);
}

/*
 *		Busca no DB os projetos que o usuario esta inscrito.
 */

char	*ft_ongoingprojects(MYSQL *conn, char *res, char *login)
{
	int			i;
	char		*query;
	MYSQL_ROW	row;
	MYSQL_RES	*result;
	int			num_fields;

	asprintf(&query, "SELECT project_name FROM projects WHERE user_login = "\
			"'%s' AND status = 'in_progress'", login);
	result = ft_query_to_res(conn, query);
	asprintf(&res, "%sProjetos em andamento:\t\t", res);
	num_fields = mysql_num_fields(result);
	while ((row = mysql_fetch_row(result)))
		for (i = 0; i < num_fields; i++)
			asprintf(&res, "%s %s", res, row[i]);
	return (res);
}

/*
 *		Busca o numero de usuarios salvos no DB.
 */

char	*ft_numofusers(MYSQL *conn, char *res)
{
	char		*query;
	MYSQL_RES	*result;

	asprintf(&query, "SELECT * FROM users");
	result = ft_query_to_res(conn, query);
	asprintf(&res, "%s\nUsuarios no banco de dados:\t %ld\n",
		res, mysql_num_rows(result));
	return (res);
}

/*
 *		Faz o redirecionamento para as buscas no DB e salva as respostas
 *		numa variavel que sera o retorno do servidor.
 */

char	*ft_printmysql(MYSQL *conn, char *login)
{
	char		*res;

	asprintf(&res, "\n\t%s\n\n", login);
	asprintf(&res, "%sUltimo projeto entregue:\t %s\n",
		res, ft_lastproject(conn, login));
	res = ft_timeonproject(conn, res, login);
	res = ft_numofprojects(conn, res, login);
	res = ft_ongoingprojects(conn, res, login);
	asprintf(&res, "%s\n\n", res);
	return (res);
}
