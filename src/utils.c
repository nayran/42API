#include "api.h"
#include <json-c/json.h>

/*
 *		Funcao que concatena duas strings.
 */

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*x;
	char	*aux;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	x = malloc(strlen(s1) + strlen(s2) + 1);
	aux = x;
	if (!x)
		return (NULL);
	while (*s1)
	{
		*x = *s1;
		x++;
		s1++;
	}
	while (*s2)
	{
		*x = *s2;
		x++;
		s2++;
	}
	*x = '\0';
	return (aux);
}

/*
 *		Faz a busca de um objeto JSON num arquivo JSON, retornando o mesmo em
 *		string.
 */

char	*ft_searchjsonobj(char *info, char *obj)
{
	struct json_object	*json;
	struct json_object	*jsonobj;

	if (!info)
		return (NULL);
	json = json_tokener_parse(info);
	json_object_object_get_ex(json, obj, &jsonobj);
	return ((char *)json_object_get_string(jsonobj));
}

/*
 *		userid para requisicao HTTP
 */

char	*ft_uid(void)
{
	return (UID);
}

/*
 *		secret para requisicao HTTP
 */

char	*ft_secret(void)
{
	return (SECRET);
}

/*
 *		Funcao para receber a resposta das requisicoes HTTP feitas pelo cURL
 */

size_t	WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *contxt)
{
	size_t				bytec;
	struct MemoryStruct	*mem;

	bytec = size * nmemb;
	mem = (struct MemoryStruct *)contxt;
	mem->memory = realloc(mem->memory, mem->size + bytec + 1);
	if (mem->memory == NULL)
	{
		printf("Memoria insuficiente\n");
		return (0);
	}
	memcpy(&(mem->memory[mem->size]), ptr, bytec);
	mem->size += bytec;
	mem->memory[mem->size] = 0;
	return (nmemb);
}
