#include "api.h"
#include <json-c/json.h>

/*
 *		Retorna o query que sera enviado ao API do mySQL para criar uma tabela 
 *		caso essa nao exista. Nete escolhemos que informacoes que irao na tabela
 *		e o tipo de variavel.
 */

char	*ft_createcursusquery(void)
{
	return ("CREATE TABLE IF NOT EXISTS cursus"\
			"(id INT PRIMARY KEY, cursus_name VARCHAR(100))");
}

/*
 *		Retorna um ponteiro de char com as informacoes para inserir os dados
 *		selecionados na tabela do DB. 
 */

char	*ft_insertcursusquery(struct json_object *obj)
{
	char	*info;
	char	*query;
	char	*name;
	char	*id;

	info = (char *) json_object_to_json_string(obj);
	id = ft_searchjsonobj(ft_searchjsonobj(info, "cursus"), "id");
	name = ft_searchjsonobj(ft_searchjsonobj(info, "cursus"), "name");
	asprintf(&query, "INSERT INTO cursus VALUES(%s, '%s')", id, name);
	return (query);
}

/*
 *		Faz o parsing do array de objetos json para melhor leitura dos dados que
 *		serao escolhidos e inclusos na table cursus.
 */

MYSQL	*ft_getcursus(MYSQL *conn, char *info)
{
	int					x;
	struct json_object	*obj;
	struct json_object	*json;
	struct json_object	*array;
	char				*query;

	x = -1;
	json = json_tokener_parse(info);
	json_object_object_get_ex(json, "cursus_users", &obj);
	while (++x < (int)json_object_array_length(obj))
	{
		array = json_object_array_get_idx(obj, x);
		query = ft_insertcursusquery(array);
		if (mysql_query(conn, query))
		{
			mysql_query(conn, ft_strjoin("DELETE FROM cursus WHERE id = ",
				ft_searchjsonobj(ft_searchjsonobj((char *)json_object_to_json_string(array), "cursus"), "id")));
			if (mysql_query(conn, query))
				return (0);
		}
	}
	return (conn);
}

/*
 *		Tenta criar a tabela cursus e popular a mesma com as informacoes 
 *		recebidas.
 */

char	*ft_populatecursus(MYSQL *conn, char *info)
{
	if (mysql_query(conn, ft_createcursusquery()))
		return ("Falha ao criar tabela cursus!\n");
	conn = ft_getcursus(conn, info);
	if (!conn)
		return ("Falha ao inserir dados na tabela cursus!\n");
	return (NULL);
}
