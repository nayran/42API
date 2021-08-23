# 42Labs API

Um API em C que faz requisições com o cURL para a API oficial da 42, recebe um JSON, trata os dados de forma estática e armazena em um banco de dados mySQL, devolvendo informações em HTTP com o framework ulfius. A aplicação foi cointainerizada em ubuntu usando o Docker.

## IMPORTANTE
Para utilizar essa API é necessário fazer antes a instalação do Docker.

# Modo de usar

'git clone https://github.com/42sp/42labs-selection-process-nayran.git'

'cd ./42labs-selection-process-nayran'


Abrir dois terminais, um para deixar o servidor rodando (Terminal01), com este poderá acompanhar cada requisição recebida. O outro terminal será util para fazer as requisições (Terminal02).


No Terminal01 rodar o seguinte comando:

docker build . -t api ; docker run -it api


No Terminal02 este outro, mas dessa vez substituindo "COMANDO" por um dos comandos abaixo:

docker exec -it $(docker ps | grep api | awk '{print $1}') COMANDO


## Comandos

### cURL
O cURL fará requisições ao servidor a partir do login fornecido, basta substituir "LOGIN" por algum login da intra que queira adicionar ao banco de dados e receber informações do mesmo.

curl http://localhost:8080/LOGIN




### mySQL
No banco de dados mySQL podemos verificar informações adicionais recebidas e salvas dos usuários.

mysql -uroot

Ao rodar este comando, o terminal abrirá o shell do próprio mySQL, assim os comandos serão diferentes dos usuais. Vale lembrar que os comandos devem terminar com um ';'. O primeiro passo será escolher um banco de dados(DBs), o nome do DB criado nesse programa é "api_db":

Para listar os disponíveis basta: show databases

Para escolher um: 'use "NOME";'

Agora você pode ver as tabelas do banco de dados, utilize: 'show tables;'

Imprima na tela todas informações da table com um simples: 'select * from "NOME DA TABLE";'




# Objetivo proposto:

A sua tarefa é construir uma API com conexão de banco de dados para uma aplicação de análise estatística de alunos. A aplicação deverá receber `Intra login` e retornar o máximo de informações e análises que você julgue como úteis de uma forma legível e de fácil processamento. Essas informações devem ser buscadas através da [API oficial da Intra](https://api.intra.42.fr/), persistidas em um banco de dados e atualizadas após cada nova requisição.

Os dados devem ser mantidos e utilizados para gerar análises de performance dos alunos. Exemplos: projetos concluídos, tempo gasto por projeto, etc.

**A aplicação deverá ser construída utilizando C.**

Quaisquer banco de dados, bibliotecas e ferramentas são permitidas. 

## **O que será avaliado**

Queremos avaliar sua capacidade de desenvolver e documentar um back-end para uma aplicação. Serão avaliados:

- Código bem escrito e limpo;
- Quais ferramentas foram usadas, como e por quê;
- Sua criatividade e capacidade de lidar com problemas diferentes e abstratos;
- Sua capacidade de se comprometer com o que foi fornecido;
- Sua capacidade de documentação da sua aplicação.

## **O mínimo necessário**

- [README.md](http://readme.md) com documentação contendo informações do projeto;

## **Bônus**

Os seguintes itens não são obrigatórios, mas darão mais valor ao seu trabalho. Os destacados são mais significativos para nós.

- **Testes**;
- **Conteinerização da aplicação**;
- **Autenticação e autorização** (**OAuth, JWT**);
- Uso de ferramentas externas que facilitem o seu trabalho (Miro, Trello, etc.);
- Cuidados especiais com otimização, padrões, entre outros;
- Migrations ou script para configuração do banco de dados;
- CronJobs;
- Rota para plotagem de gráficos;
- Manifestos K8s;
- Pipelines de CI;
- Utilização de algum serviço de computação na nuvem (AWS, GCP, Azure, etc.);

## **Critérios de Aceitação**

- Você deverá utilizar a API oficial da intra: [api.intra.42.fr](https://api.intra.42.fr/)
- Deve haver uma documentação descrevendo sua API;

## **Formato de entrega**

Seu código deverá ser submetido neste repositório, sinta-se livre pare substituir este README.md com o seu próprio.
