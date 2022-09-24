#ifndef RESPONSE_CODE_H
#define RESPONSE_CODE_H

#define R201 201

enum ClientStatusCode 
{
	DEFAULT,
	BAD_REQUEST_400,
	NOT_FOUND_404,
	FORBIDDEN_403,
	NOT_ALLOWED_405,
	REQUEST_ENTITY_TOO_LARGE_413,
	INTERNAL_SERVER_ERROR_500
};

// std::string responce_code(int state);

#endif