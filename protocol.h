#include <stdio.h>
#include <stdlib.h>

typedef struct message{
	int type;
	int code;
	int id;
	int token;
	option *option
	int len;
	char *payload;
}

typedef struct option{
	int delta;
	int len;
	char *value;
	option *next;
}

enum Operation{
	GET = 0,
	POST = 1,
	PUT = 2,
	DEL = 3
};

enum Code{
	OK = 200,
	CLIENT_ERROR = 400,
	SERVER_ERROR = 500
};

enum Type{
	CONF = 0,
	NOT_CONF = 1,
	ACK = 2,
	RESET = 3
};

enum Delta{
	URI_PATH = 0,
	URI_PARAM = 1
};

