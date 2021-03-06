/*
 * This file and its contents are licensed under the Timescale License.
 * Please see the included NOTICE for copyright information and
 * LICENSE-TIMESCALE for a copy of the license.
 */
#ifndef TIMESCALEDB_TSL_CONTINUOUS_AGGS_MATERIALIZE_H
#define TIMESCALEDB_TSL_CONTINUOUS_AGGS_MATERIALIZE_H

#include <postgres.h>
#include <fmgr.h>
#include <nodes/pg_list.h>
#include "continuous_agg.h"

typedef struct SchemaAndName
{
	Name schema;
	Name name;
} SchemaAndName;

/***********************
 * Time ranges
 ***********************/

typedef struct TimeRange
{
	Oid type;
	Datum start;
	Datum end;
} TimeRange;

typedef struct InternalTimeRange
{
	Oid type;
	int64 start; /* inclusive */
	int64 end;   /* exclusive */
} InternalTimeRange;

bool continuous_agg_materialize(int32 materialization_id, ContinuousAggMatOptions *options);
void continuous_agg_execute_materialization(int64 bucket_width, int32 hypertable_id,
											int32 materialization_id, SchemaAndName partial_view,
											int64 invalidation_range_start,
											int64 invalidation_range_end,
											int64 materialization_invalidation_threshold);
void continuous_agg_update_materialization(SchemaAndName partial_view,
										   SchemaAndName materialization_table,
										   Name time_column_name,
										   InternalTimeRange new_materialization_range,
										   InternalTimeRange invalidation_range,
										   int64 bucket_width);

#endif /* TIMESCALEDB_TSL_CONTINUOUS_AGGS_MATERIALIZE_H */
