#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <zmq.h>
#include <cJSON.h>
#include "oisconstants.h"

char* handle_method(const char* method_name, cJSON* parameters) {
	char* result;
	cJSON* output_result = cJSON_CreateObject();
	cJSON* result_param = 0;

	if (strcmp(method_name, "get_ois_constant") == 0) {
		char *param = parameters->child->valuestring;
		int oisIndex = getOISKeyboardConstant(param);

		result_param = cJSON_CreateNumber(oisIndex);
		result_param->string = "result";
	}
	else if (strcmp(method_name, "get_keyboard_modifier_constant") == 0) {
		char *param = parameters->child->valuestring;
		int oisIndex = getOISKeyboardModifierConstant(param);

		result_param = cJSON_CreateNumber(oisIndex);
		result_param->string = "result";
	}
	else if (strcmp(method_name, "create_input_manager") == 0) {
		OIS::ParamList pl;

	}

	if (result_param == 0) {
		cJSON *success = cJSON_CreateFalse();
		success->string = "success";
		output_result->child = success;
	} else {
		cJSON *success = cJSON_CreateTrue();
		success->string = "success";
		output_result->child = success;
		output_result->child->next = result_param;
	}

	result = cJSON_Print(output_result);
	cJSON_Delete(output_result);
	return result;
}

void handle_query(const char* query_string, void *socket) {
	int rc;
	zmq_msg_t resultset;

	cJSON *query_string_json = cJSON_Parse(query_string);
	char* method_name = query_string_json->child->valuestring;
	cJSON *parameters = query_string_json->child->next;
	char* resultset_string = handle_method(method_name, parameters);

	rc = zmq_msg_init_size (&resultset, strlen(resultset_string));
	assert (rc == 0);
	memcpy(zmq_msg_data(&resultset), resultset_string, strlen(resultset_string));

	rc = zmq_send(socket, &resultset, 0);
	assert(rc == 0);
	zmq_msg_close(&resultset);
}

int main() {
	int rc;
	void *ctx, *s;
	zmq_msg_t query;
	const char *query_string;

	ctx = zmq_init(1);
	assert(ctx);
	s = zmq_socket(ctx, ZMQ_REP);
	assert(s);
	rc = zmq_bind(s, "tcp://127.0.0.1:5555");
	assert (rc == 0);

	while (1) {
		rc = zmq_msg_init(&query);
		assert(rc == 0);

		rc = zmq_recv(s, &query, 0);
		assert(rc == 0);

		query_string = (const char *)zmq_msg_data (&query);
		handle_query(query_string, s);
		fflush(stdout);
		zmq_msg_close(&query);
	}
}
