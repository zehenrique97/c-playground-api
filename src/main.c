#include <stdio.h>
#include <ulfius.h>
#include <jansson.h>
#include "../include/user_controller.h"
#include "../include/app_context.h"

#define PORT 8080
#define PREFIX "/api/v1"

// TODO: Implementar testes
// TODO: Ajustar estrutura de pastas e makefile
// TODO: Ajustar extensão do VS Code
// TODO: Colocar a API em um container

int main() {
    AppContext app;

    if(app_init(&app)) return 1;

    struct _u_instance instance;

    if(ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
        fprintf(stderr, "Error while trying to start instance\n");
    }

    ulfius_add_endpoint_by_val(&instance, "GET", PREFIX, "/users", 0, &get_users, &app);
    ulfius_add_endpoint_by_val(&instance, "GET", PREFIX, "/users/:id", 0, &get_user_by_id, &app);
    ulfius_add_endpoint_by_val(&instance, "POST", PREFIX, "/users", 0, &post_user, &app);
    ulfius_add_endpoint_by_val(&instance, "PUT", PREFIX, "/users", 0, &put_user, &app);
    ulfius_add_endpoint_by_val(&instance, "DELETE", PREFIX, "/users/:id", 0, &delete_user, &app);

    if(ulfius_start_framework(&instance) == U_OK) {
        printf("Server started successfully. Listening on port: %d\nPress Control+C to stop\n", PORT);

        while(1) {
            sleep(1);
        }
    } else {
        fprintf(stderr, "Error while trying to start server\n");
    }

    printf("Stopping server...\n");
    ulfius_stop_framework(&instance);
    ulfius_clean_instance(&instance);
    
    return 0;
}