#include "api.h"

/*
 *		Adiciona as credenciais do client no campo field, o qual sera um header
 *		de autorizacao para requisicao de dados na API da 42.
 */

char	*ft_fields(void)
{
	char	*fields;

	fields = strdup("grant_type=client_credentials&client_id=");
	fields = ft_strjoin(fields, ft_uid());
	fields = ft_strjoin(fields, "&client_secret=");
	fields = ft_strjoin(fields, ft_secret());
	return (fields);
}

/*
 *		Adiciona a token em um campo fields, este sera enviado como header
 *		de autorizacao para a API da 42.
 */

char	*ft_authorization(char *token)
{
	char	*fields;

	fields = malloc(strlen(token) + 23);
	strncpy(fields, "Authorization: Bearer ", 23);
	strncat(fields, token, strlen(fields) + strlen(token) + 1);
	return (fields);
}

/*
 *		Adiciona o login ao final da URL para requisicoes.
 */

char	*ft_url(char *login)
{
	return (ft_strjoin("https://api.intra.42.fr/v2/users/", login));
}

/*
 *		Inicializacao da struct chunk.
 */

struct MemoryStruct	ft_initchunk(void)
{
	struct MemoryStruct	chunk;

	chunk.memory = malloc(1);
	chunk.size = 0;
	chunk.memory[chunk.size] = 0;
	return (chunk);
}

/*
 *		Recebe um JSON e retorna apenas o campo 'access_token'.
 */

char	*ft_token(char *s)
{
	return (ft_searchjsonobj(s, "access_token"));
}

/*
 *		Funcao para finalizar as funcoes de requisicao, liberando o chunk.
 */

char	*ft_curlerror(char *mem, void *curl)
{
	printf("Request error!\n");
	free(mem);
	curl_easy_cleanup(curl);
	return (NULL);
}

/*
 *		Faz uma requisicao POST, enviando as credenciais para receber a token
 *		de autorizacao. Essa fica armazenada na variavel chunk.memory.
 */

char	*ft_gettoken(void)
{
	CURL				*curl;
	CURLcode			ret;
	struct MemoryStruct	chunk;
	char				*fields;
	char				*token;

	curl = curl_easy_init();
	chunk = ft_initchunk();
	if (curl)
	{
		fields = ft_fields();
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields);
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.intra.42.fr/oauth/token");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		ret = curl_easy_perform(curl);
		free (fields);
		if (ret)
			return (ft_curlerror(chunk.memory, curl));
		curl_easy_cleanup(curl);
	}
	token = ft_token(chunk.memory);
	free(chunk.memory);
	return (token);
}

/*
 *		A funcao faz uma requisicao HTTPGET, adicionando a token de
 *		autorizacao, header e url na struct curl. Tambem salva a resposta 
 *		(no caso, um arquivo JSON parseado) na struct chunk, ficando acessível
 *		na chunk.memory
 */

char	*ft_getallinfo(char *login)
{
	CURL				*curl;
	CURLcode			ret;
	struct MemoryStruct	chunk;
	struct curl_slist	*list;

	curl = curl_easy_init();
	list = NULL;
	if (curl)
	{
		chunk = ft_initchunk();
		list = curl_slist_append(list, ft_authorization(ft_gettoken()));
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
		curl_easy_setopt(curl, CURLOPT_URL, ft_url(login));
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		ret = curl_easy_perform(curl);
		if (ret)
			return (ft_curlerror(chunk.memory, curl));
		curl_easy_cleanup(curl);
	}
	return (chunk.memory);
}
