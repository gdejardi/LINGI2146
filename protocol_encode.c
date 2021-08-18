#include <stdio.h>
#include <stdlib.h>
#include "protocol.h"

/* Encode the type and the code of the message */
int encode_type(message *msg, char *buf){
	int to_encode = msg->type | msg->code;
	memcpy(buf, &to_encode, 1);
	return 1;
}

/* Encode the id of the message */
int encode_id(message *msg, char *buf){
	int to_encode = msg->id;
	memcpy(buf, &to_encode, 2);
	return 2;
}

/* Encode the token of the message */
int encode_token(message *msg, char *buf){
	int to_encode = msg->token;
	memcpy(buf, &to_encode, 4);
	return 4;
}

/* Encode the payload of the message */
int encode_payload(message *msg, char *buf){
	memcpy(buf, msg->payload, msg->len);
	return msg->len;
}

/* Encode the option(s) delta and len of the message */
int encode_delta(option *opt, char *buf){
	int to_encode = opt->delta | opt->len;
	memcpy(buf, &to_encode, 1)
	return 1;
}

/* Encode option value */
int encode_value(option *opt, char *buf){
	memcpy(buf, opt->value, opt->len);
	return opt->len
}

/* Encode option(s) of the message */
int encode_options(message *msg, char *buf){
	option *opt = msg->option;
	/* There may be several options or 0 */
	int offset = 0;
	while(option != NULL){
		offset += encode_delta(opt, buf + offset);
		offset += encode_value(opt, buf + offset);
		opt = opt->next;
	}
	return offset;
}

/* Encode the separator (11111111) of the message between options and payload */
int encode_separator(message *msg, char *buf){
	memcpy(buf, 255, 1);
	return 1;
}

int encode_message(message *msg, char *buf, int len){
	memset(buf, 0, len);
	int offset = 0;
	offset += encode_type(msg, buf + offset);
	offset += encode_id(msg, buf + offset);
	offset += encode_token(msg, buf + offset);
	offset += encode_options(msg, buf + offset);
	offset += encode_separator(msg, buf + offset);
	offset += encode_payload(msg, buf + offset);	
	return offset;
}
