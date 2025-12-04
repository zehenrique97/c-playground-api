#include "user_types.h"

#ifndef USER_ENTITY_H
#define USER_ENTITY_H

UserEntity *map_query_to_entity_array(PGresult *result);

UserEntity map_query_to_entity(PGresult *result);

#endif