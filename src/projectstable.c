#include "api.h"
#include <json-c/json.h>

/*
 *		Busca as informacoes no JSON recebido pela variavel info e retorna elas
 *		já parseadas.
 */

char	*ft_projectinfos(char *info, int x)
{
	char	*aux;
	char	*userinfos[12] = {"id", "id", "name", "status", "final_mark",
		"occurrence", "validated?", "cursus_ids", "marked_at", "marked",
		"created_at", "updated_at"};

	if (x == 1 || x == 2)
		aux = ft_searchjsonobj(ft_searchjsonobj(info, "project"), userinfos[x]);
	else
		aux = ft_searchjsonobj(info, userinfos[x]);
	return (aux);
}

/*
 *		Retorna um query para criar a tabela, caso ela nao exista.
 */

char	*ft_createprojectsquery(void)
{
	return ("CREATE TABLE IF NOT EXISTS projects(id INT PRIMARY KEY, "\
			"project_id INT, project_name VARCHAR(100), status VARCHAR(30), "\
			"final_mark INT, occurrence INT, validated VARCHAR(10), cursus "\
			"VARCHAR(100), marked_at VARCHAR(25), marked VARCHAR(10), "\
			"created_at VARCHAR(25), updated_at VARCHAR(25), user_login "\
			"VARCHAR(15), user_id INT)");
}

/*
 *		Retorna um query de insercao na tabela projects, com as informacoes
 *		parseadas do JSON.
 */

char	*ft_insertprojectquery(struct json_object *obj, char *login, char *userid)
{
	char	*info;
	char	*ui[12];
	char	*query;
	int		x;

	info = (char *) json_object_to_json_string(obj);
	x = -1;
	while (++x < 12)
		ui[x] = ft_projectinfos(info, x);
	asprintf(&query, "INSERT INTO projects VALUES(%s, %s, '%s', '%s', %s, %s,"\
		"'%s', '%s', '%s', '%s', '%s', '%s', '%s', %s)", ui[0], ui[1], ui[2],
		ui[3], ui[4], ui[5], ui[6], ui[7], ui[8], ui[9], ui[10], ui[11], login, userid);
	return (query);
}

/*
 *		Manipula um array de objetos JSON para melhor leitura do parsing e 
 *		tenta fazer o insert na tabela, caso ja exista, exclui a linha antiga
 *		e adiciona a nova.
 */

MYSQL	*ft_getprojects(MYSQL *conn, char *info)
{
	struct json_object	*json;
	struct json_object	*obj;
	int					x;
	char				*login;
	char				*userid;
	char				*query;
	struct json_object	*array;

	userid = ft_searchjsonobj(info, "id");
	login = ft_searchjsonobj(info, "login");
	json = json_tokener_parse(info);
	json_object_object_get_ex(json, "projects_users", &obj);
	x = -1;
	while (++x < (int)json_object_array_length(obj))
	{
		array = json_object_array_get_idx(obj, x);
		query = ft_insertprojectquery(array, login, userid);
		if (mysql_query(conn, query))
		{
			mysql_query(conn, ft_strjoin("DELETE FROM projects WHERE id = ",
				ft_projectinfos((char *)json_object_to_json_string(array), 0)));
			if (mysql_query(conn, query))
				return (0);
		}
	}
	return (conn);
}

/*
 *		Cria a tabela projects, caso nao exista e popula a mesma. Retorna para 
 *		a funcao que cria e popula a tabela cursus.
 */

char	*ft_populateprojects(MYSQL *conn, char *info)
{
	if (mysql_query(conn, ft_createprojectsquery()))
		return ("Falha ao criar tabela projects!\n");
	conn = ft_getprojects(conn, info);
	if (!conn)
		return ("Falha ao inserir dados na tabela projects!\n");
	return (ft_populatecursus(conn, info));
}
