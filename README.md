# Lab API em C

Playground para experimentar um CRUD de usuários em C usando Ulfius (HTTP), Jansson (JSON) e PostgreSQL.

## Pré-requisitos
- GCC, `make` e `pkg-config`
- Bibliotecas de desenvolvimento: `libulfius`, `liborcania`, `libjansson`, `libpq`
- Docker + Docker Compose (para subir o banco e rodar testes de integração)

## Banco de dados
1) Suba o PostgreSQL local com as credenciais esperadas pela aplicação:
   ```sh
   docker compose up -d database
   ```
   - Host: `localhost:5432`
   - Usuário: `teste` | Senha: `teste123` | Banco: `testedb`
2) Crie a tabela usada pelo serviço (não há migrações automáticas):
   ```sql
   CREATE TABLE IF NOT EXISTS users (
     id INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
     name VARCHAR(255),
     age INT
   );
   ```

## Build e execução
Com o banco ativo:
```sh
make          # compila em build/lab_api
make run      # inicia o servidor em http://localhost:8080
```
Use `make clean` para remover artefatos de build.

## Endpoints
Prefixo: `/api/v1`

- `GET /users` → 200 com `{ count, users[] }` ou 204 se vazio.
- `GET /users/:id` → 200 com usuário ou 204 se não existir.
- `POST /users` → 201. Corpo: `{"name":"Fulano","age":30}`
- `PUT /users` → 200 ao atualizar, 204 se id não encontrado. Corpo: `{"id":1,"name":"Novo Nome","age":31}`
- `DELETE /users/:id` → 200 ao remover, 204 se id não encontrado.
- Erros de banco retornam 500.

Exemplos rápidos:
```sh
curl -X POST http://localhost:8080/api/v1/users \
  -H "Content-Type: application/json" \
  -d '{"name":"Alice","age":25}'

curl http://localhost:8080/api/v1/users

curl -X PUT http://localhost:8080/api/v1/users \
  -H "Content-Type: application/json" \
  -d '{"id":1,"name":"Alice Souza","age":26}'
```

## Testes
- Unitários (Unity): `make tests`
- Integração (PostgreSQL via Compose): `make itests`
  - O `make itests` sobe o banco definido em `tests/integration/docker-compose.yaml` na porta 5432; pare qualquer outro PostgreSQL na mesma porta antes de rodar.
