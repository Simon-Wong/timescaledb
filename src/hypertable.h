#ifndef TIMESCALEDB_HYPERTABLE_H
#define TIMESCALEDB_HYPERTABLE_H

#include <postgres.h>
#include <nodes/primnodes.h>

#include "catalog.h"
#include "dimension.h"
#include "tablespace.h"

typedef struct SubspaceStore SubspaceStore;
typedef struct Chunk Chunk;
typedef struct HeapTupleData *HeapTuple;

typedef struct Hypertable
{
	FormData_hypertable fd;
	Oid			main_table_relid;
	Hyperspace *space;
	SubspaceStore *chunk_cache;
	Tablespaces *tablespaces;
} Hypertable;

extern bool hypertable_has_privs_of(Oid hypertable_oid, Oid userid);
extern Oid	hypertable_permissions_check(Oid hypertable_oid, Oid userid);
extern Hypertable *hypertable_from_tuple(HeapTuple tuple);
extern int	hypertable_set_name(Hypertable *ht, const char *newname);
extern int	hypertable_set_schema(Hypertable *ht, const char *newname);
extern Oid	hypertable_id_to_relid(int32 hypertable_id);
extern Chunk *hypertable_get_chunk(Hypertable *h, Point *point);
extern Oid	hypertable_relid(RangeVar *rv);
extern bool is_hypertable(Oid relid);
extern bool hypertable_has_tablespace(Hypertable *ht, Oid tspc_oid);
extern Tablespace *hypertable_add_tablespace(Hypertable *ht, int32 tspc_id, Oid tspc_oid);
extern bool hypertable_delete_tablespace(Hypertable *ht, Oid tspc_id);
extern int	hypertable_delete_all_tablespaces(Hypertable *ht);

#endif   /* TIMESCALEDB_HYPERTABLE_H */
