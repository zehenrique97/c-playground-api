#include <stdio.h>
#include <ulfius.h>
#include <jansson.h>
#include "user_controller_adapter.h"
#include "app_context.h"

#define PORT 8080
#define PREFIX "/api/v1"

int main() {
    AppContext app;

    if(app_init(&app)) return 1;

    struct _u_instance instance;

    if(ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
        fprintf(stderr, "Error while trying to start instance\n");
    }

    ulfius_add_endpoint_by_val(&instance, "GET", PREFIX, "/users", 0, &user_controller_adapter_get_users, &(app.get_users_port));
    ulfius_add_endpoint_by_val(&instance, "GET", PREFIX, "/users/:id", 0, &user_controller_adapter_get_user_by_id, &(app.get_user_port_by_id));
    ulfius_add_endpoint_by_val(&instance, "POST", PREFIX, "/users", 0, &user_controller_adapter_post_user, &(app.create_user_port));
    ulfius_add_endpoint_by_val(&instance, "PUT", PREFIX, "/users", 0, &user_controller_adapter_put_user, &(app.update_user_port));
    ulfius_add_endpoint_by_val(&instance, "DELETE", PREFIX, "/users/:id", 0, &user_controller_adapter_delete_user, &(app.delete_user_port));

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