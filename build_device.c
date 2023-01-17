//Autor: Javier Castorena


typedef struct
{
    char name[32];
    char path[64];
    char partition_table_type[32];
    char model[64];
    char serial[256];
    char device_capacity[32];
    char sector_size[32];
    char device_type[32];

} storage_device;

typedef struct
{
    int partition_num;
    storage_device device;
} storage_device_list;

typedef struct
{
    char partition_type[32];
} storage_partition;

typedef struct
{
    int partition_num;
    storage_partition partition;
} partition_list;