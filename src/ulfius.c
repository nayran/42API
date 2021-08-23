#include "api.h"
#include <ulfius.h>

/*
 *		Envia o login para a funcao ft_getallinfo, a mesma fara requisicoes
 *		via cURL e retornara um JSON parseado, o qual ficara gravado na
 *		variavel info. Confere a existencia do login com a funcao
 *		ft_searchjsonobj. Enfim conecta e armazena os dados no mySQL.
 *		A funcao retorna um ponteiro de char que sera a resposta do servidor.
 */

char	*ft_getinfo(char *login)
{
	char	*info;
	MYSQL	*conn;

	info = ft_getallinfo(login);
	if (!info)
		return ("cURL erro!\n");
	if (!ft_searchjsonobj(info, "login"))
		return ("Login invalido!\n");
	conn = ft_connect();
	info = ft_mysql(info, conn);
	if (!info)
		info = ft_printmysql(conn, login);
	mysql_close(conn);
	return (info);
}

/*
 *		Faz o manuseio da http_url, na qual recebe o login e envia para a
 *		funcao ft_getinfo. Adiciona resposta da requisicao na struct e retorna 
 *		o callback.
 */

int	callback(const struct _u_request *request, struct _u_response *response, void *user_data)
{
	char	*info;

	printf("Request: %s\n", &request->http_url[1]);
	info = ft_getinfo(&request->http_url[1]);
	ulfius_set_string_body_response(response, 200, info);
	return (U_CALLBACK_CONTINUE);
	(void)user_data;
}

/*
 *		Inicializa e encerra o framework Ulfius. Envia as requisicoes recebidas
 *		para a funcao callback.
 */

int	ft_ulfius(void)
{
	struct _u_instance	instance;

	if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK)
	{
		fprintf(stderr, "Erro ulfius_init_instance!\n");
		return (1);
	}
	ulfius_add_endpoint_by_val(&instance, "GET", "/:login", NULL, 0, &callback, NULL);
	if (ulfius_start_framework(&instance) == U_OK)
	{
		printf("Framework iniciado na porta %d\n", instance.port);
		getchar();
	}
	else
		fprintf(stderr, "Erro ao iniciar framework\n");
	ulfius_stop_framework(&instance);
	ulfius_clean_instance(&instance);
	return (0);
}
