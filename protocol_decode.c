#include <stdio.h>
#include <stdlib.h>
#include "protocol.h"

/* Decode the type of the message */
int decode_type(char *buf){
	int type;
	memset(&type, 0, 1);
	memcpy(&type, buf, 1);
	return type;
}

/* Decode the code of the message */
int decode_code(char *buf){
	int code;
	memset(&code, 0, 1);
	memcpy(&code, buf, 1);
	return code;
}

/* Decode the id of the message */
int decode_id(char *buf){
	int id;
	memset (&id, 0, 2);
	memcpy(&id, buf, 2);
	return id;
}

/* Decode the token of the message */
int decode_token(char *buf){
	int token;
	memset(&token, 0, 4);
	memcpy(&token, buf, 4);
	return token;
}

/* Decode options of the message */
int decode_options(char *buf, int *offset){
	option *opt;
	memset(&opt, 0, 1);
	memcpy(&opt, buf, 1);
	*offset += 1;
	memcpy(&(opt->delta), buf + *offset, 1);
	*offset += 1;
	memcpy(&(opt->len), buf + *offset, 1);
	*offset += 1;
	memcpy(&(opt->value), buf + *offset, opt->len);
	*offset += opt->len;
	/* Look if there is another option */
	if (decode_separator(buf + *offset) == 0){
		opt = opt->next;
		decode_options(buf + *offset, *offset);
	}
	return 1;
}

/* Decode the separator between options and payload */
int decode_separator(char *buf){
	int separator;
	memset(&separator, 0, 1);
	memcpy(&separator, buf, 1);
	/* if separator == 255, it means that the following part is the payload and so, the end of the options */
	if (separator == 255){
		return 1;
	}
	else{
		return 0;
	}
}

/* Decode message */
int decode_message(char *buf, message *msg){
	int offset = 0;
	msg->type = decode_type(buf);
	msg->code = decode_type(buf);
	msg->id = decode_id(buf + offset);
	offset += 2;
	msg->token = decode_token(buf + offset);
	offset += 4;
	if (decode_separator(buf + offset) == 0){
		decode_options(buf + offset, offset);
	}
	else{
		msg->option = NULL;
	}
	offset += 1;
	msg->len = len - offset;
	char payload;
	memset(msg->payload, 0 msg->len);
	memcpy(msg->payload, buf + offset, msg->len);
	return 1;
}
