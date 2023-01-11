#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "nvs_flash.h"

#include "log.h"
#include "tuya_error_code.h"
#include "storage_interface.h"
#include "system_interface.h"



int local_storage_set(const char* key, const uint8_t* buffer, size_t length)
{
    if (NULL == key || NULL == buffer) {
        return OPRT_INVALID_PARM;
    }

    char nvsKey[16];

    if(strlen(key) > 15)
    {
    	strncpy(nvsKey, key + strlen(key) - 15, 15);
    }
    else
    {
        strncpy(nvsKey, key, 15);
    }
    nvsKey[15] = 0;

    log_debug("write key:%s, len:%d", key, (int)length);

	nvs_handle_t nvsHandle;
	esp_err_t err = nvs_open("tuya", NVS_READWRITE, &nvsHandle);

	if (err != ESP_OK) {
		log_error("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
		return OPRT_COM_ERROR;
	}
	else
	{
		log_debug("open file OK");
	}

	err = nvs_set_blob(nvsHandle, nvsKey, buffer, length);

	if (err != ESP_OK) {
		log_error("Error (%s) writing NVS handle!\n", esp_err_to_name(err));
		return OPRT_COM_ERROR;
	}
	else
	{
		log_debug("write file OK");
	}

	err = nvs_commit(nvsHandle);

	if (err != ESP_OK) {
		log_error("Error (%s) commiting NVS handle!\n", esp_err_to_name(err));
		return OPRT_COM_ERROR;
	}
	else
	{
		log_debug("commit file OK");
	}

	nvs_close(nvsHandle);

	return OPRT_OK;
}

int local_storage_get(const char* key, uint8_t* buffer, size_t* length)
{
    if (NULL == key || NULL == buffer || NULL == length) {
        return OPRT_INVALID_PARM;
    }

    char nvsKey[16];

    if(strlen(key) > 15)
    {
    	strncpy(nvsKey, key + strlen(key) - 15, 15);
    }
    else
    {
        strncpy(nvsKey, key, 15);
    }
    nvsKey[15] = 0;

    log_debug("read key:%s, len:%d", key, (int)*length);

	nvs_handle_t nvsHandle;
	esp_err_t err = nvs_open("tuya", NVS_READONLY, &nvsHandle);

	if (err != ESP_OK) {
		log_error("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
		return OPRT_COM_ERROR;
	}
	else
	{
		log_debug("open file OK");
	}

	err = nvs_get_blob(nvsHandle, nvsKey, buffer, length);

	if (err != ESP_OK) {
		log_error("Error (%s) reading NVS handle!\n", esp_err_to_name(err));
		return OPRT_COM_ERROR;
	}
	else
	{
		log_debug("read file OK");
	}

	nvs_close(nvsHandle);

	return OPRT_OK;
}

int local_storage_del(const char* key)
{
    log_debug("delete key:%s", key);

    char nvsKey[16];

    if(strlen(key) > 15)
    {
    	strncpy(nvsKey, key + strlen(key) - 15, 15);
    }
    else
    {
        strncpy(nvsKey, key, 15);
    }
    nvsKey[15] = 0;

	nvs_handle_t nvsHandle;
	esp_err_t err = nvs_open("tuya", NVS_READWRITE, &nvsHandle);

	if (err != ESP_OK) {
		log_error("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
		return OPRT_COM_ERROR;
	}
	else
	{
		log_debug("open file OK");
	}

	err = nvs_erase_key(nvsHandle, nvsKey);

	if (err != ESP_OK) {
		log_error("Error (%s) deleting NVS handle!\n", esp_err_to_name(err));
		return OPRT_COM_ERROR;
	}
	else
	{
		log_debug("Deleted successfully");
	}

	err = nvs_commit(nvsHandle);

	if (err != ESP_OK) {
		log_error("Error (%s) commiting NVS handle!\n", esp_err_to_name(err));
		return OPRT_COM_ERROR;
	}
	else
	{
		log_debug("commit file OK");
	}

	nvs_close(nvsHandle);

	return OPRT_OK;
}

#ifdef __cplusplus
}
#endif
