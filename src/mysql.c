#include "api.h"

/*
 *		Inicia a conexao com o mySQL, e retorna um ponteiro MYSQL que é usado
 *		para mandar informacoes para a API do mySQL.
 */

MYSQL	*ft_connect(void)
{
	MYSQL	*conn;

	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, "localhost", "root", "", NULL, 8080, NULL, 0))
		return (0);
	return (conn);
}

/*
 *		Verifica a conexao com o mySQL, cria um novo banco de dados caso ele nao
 *		exista e seleciona o mesmo para ser utilizado pelo programa.
 *		Retorna a funcao que fara a populacao do DB.
 */

char	*ft_mysql(char *info, MYSQL *conn)
{
	if (!conn)
	{
		free (info);
		return ("Falha na conexao do servidor.!\n");
	}
	if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS api_db"))
		return ("Falha ao criar o banco de dados!\n");
	if (mysql_query(conn, "USE api_db"))
		return ("Falha ao selecionar o banco de dados!\n");
	return (ft_populateuser(conn, info));
}
