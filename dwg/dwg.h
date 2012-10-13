/*
 * dwg.h
 *
 *  Created on: Mar 28, 2012
 *      Author: caruizdiaz
 */

#ifndef DWG_H_
#define DWG_H_

#include <string.h>
#include <stdlib.h>

#include "dwg_util.h"

typedef struct sms
{
	str_t destination;
	str_t content;
} sms_t;

typedef struct dwg_msg_header_id
{
	char MAC[8];
	char time[4];
	char serial_number[4];
} dwg_msg_header_id_t;

typedef struct dwg_msg_header
{
	char length[4];
	dwg_msg_header_id_t ID;
	char type[2];
	char flag[2];

} dwg_msg_header_t;

typedef struct dwg_msg_des_header
{
	int length;
	short type;
	short flag;
} dwg_msg_des_header_t;

typedef struct dwg_sms_req
{
	char port;
	char encoding;
	char type;
	char count_of_number;
	char number[24];
	char content_length[2];
	str_t content;

} dwg_sms_request_t;

typedef enum dwg_sms_result_code
{
	SMS_RC_SUCCEED = 0,
	SMS_RC_FAIL,
	SMS_RC_TIMEOUT,
	SMS_RC_BAD_REQUEST,
	SMS_RC_PORT_UNAVAILABLE,
	SMS_RC_PARTIAL_SUCCEED,
	SMS_RC_OTHER_ERROR = 255
} dwg_sms_result_code_t;

typedef struct dwg_sms_res
{
	int count_of_number;
	char number[24];
	int port;
	dwg_sms_result_code_t result;
	int count_of_slice;
	int succeded_slices;
} dwg_sms_response_t;

typedef struct dwg_sms_received
{
	char number[24];
	int type;
	int port;
	char timestamp[16];
	int timezone;
	int encoding;
	str_t message;
} dwg_sms_received_t;

typedef struct dwg_port_status
{
	int port;
	int status;
} dwg_port_status_t;

typedef struct dwg_ports_status
{
	int size;
	dwg_port_status_t *status_array;
} dwg_ports_status_t;

#define DWG_TYPE_STATUS					7
#define DWG_TYPE_STATUS_RESPONSE		8
#define DWG_TYPE_KEEP_ALIVE				0
#define DWG_TYPE_SEND_SMS				1
#define DWG_TYPE_SEND_SMS_RESP			2
#define DWG_TYPE_SEND_SMS_RESULT		3
#define DWG_TYPE_SEND_SMS_RESULT_RESP	4
#define DWG_TYPE_RECV_SMS				5
#define DWG_TYPE_RECV_SMS_RESULT		6

typedef void (*status_callback_fptr) (str_t *gw_ip, dwg_ports_status_t *status);
typedef void (*msg_response_callback_fptr) (str_t *gw_ip, dwg_sms_response_t *res);
typedef void (*msg_sms_recv_callback_fptr) (str_t *gw_ip, dwg_sms_received_t *recv);

typedef struct dwg_message_callback
{
	status_callback_fptr status_callback;
	msg_response_callback_fptr msg_response_callback;
	msg_sms_recv_callback_fptr msg_sms_recv_callback;

} dwg_message_callback_t;

void dwg_send_sms(str_t *destination, str_t *message, unsigned int port);
void dwg_start_server(int port, dwg_message_callback_t *callbacks);

#endif /* DWG_H_ */
