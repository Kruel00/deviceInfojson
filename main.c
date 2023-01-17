#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

const char* remove_invalid_chars(char *stringo);

#define DEBUG 1

int main(int argc, char **argv)
{
    FILE *fp;
    char input[32768UL];

    struct json_object *blockdevices;
    struct json_object *disk;
    struct json_object *value;
    size_t n_disk;
    size_t i;
    
    {
    popen("lsblk -e7 -JO > devices_info.json", "r");
    }

    fp = fopen("devices_info.json", "r");
    if (fp == NULL)
    {
        printf("Failed to run command\n");
        exit(1);
    }

    fread(input, sizeof(input), 1, fp);
    pclose(fp);

    struct json_object *parsed_json = json_tokener_parse(input);
    json_object_object_get_ex(parsed_json, "blockdevices", &blockdevices);
    n_disk = json_object_array_length(blockdevices);
    char testo[32];
    
    for(i=0; i<n_disk;i++){
        printf("\n================== Disk =====================\n");
        disk = json_object_array_get_idx(blockdevices, i);
        json_object_object_get_ex(disk, "name", &value);
        strcpy(testo,json_object_to_json_string_ext(value,0));
        printf("name: \t\t%s\n",remove_invalid_chars(testo));

        json_object_object_get_ex(disk, "path", &value);
        strcpy(testo, json_object_to_json_string_ext(value,0));
        printf("Path: \t\t%s\n",remove_invalid_chars(testo));
 
        json_object_object_get_ex(disk, "pttype", &value);
        strcpy(testo,json_object_to_json_string_ext(value,0));
        printf("Table Type: \t%s\n",remove_invalid_chars(testo));

        json_object_object_get_ex(disk, "model", &value);
        strcpy(testo,json_object_to_json_string_ext(value,0));
        printf("Model: \t\t%s\n",remove_invalid_chars(testo));

        json_object_object_get_ex(disk, "serial", &value);
        strcpy(testo,json_object_to_json_string_ext(value,0));
        printf("Serial No: \t%s\n",remove_invalid_chars(testo));

        json_object_object_get_ex(disk, "size", &value);
        strcpy(testo,json_object_to_json_string_ext(value,0));
        printf("Storage Size: \t%s\n",remove_invalid_chars(testo));

        json_object_object_get_ex(disk, "phy-sec", &value);
        strcpy(testo,json_object_to_json_string_ext(value,0));
        printf("Sector Size: \t%s\n",testo);

        json_object_object_get_ex(disk, "type", &value);
        strcpy(testo,json_object_to_json_string_ext(value,0));
        printf("Bus Type: \t%s\n",remove_invalid_chars(testo));

        json_object_object_get_ex(disk, "tran", &value);
        strcpy(testo,json_object_to_json_string_ext(value,0));
        printf("Storage Type: \t%s\n",remove_invalid_chars(testo));
        
    }

   

    return 0;
}

const char* remove_invalid_chars(char *s)
{
    char *str_buf;
    str_buf = strtok(s,"\"");
    str_buf = strtok(str_buf," ");

    for(int i=0;i<strlen(str_buf);i++) str_buf[i] = (str_buf[i] != '\\' ? str_buf[i] : (char)1);

    return str_buf;
}

