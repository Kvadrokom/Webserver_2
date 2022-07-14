#ifndef RESPONSE_CODE_H
#define RESPONSE_CODE_H

#define R201 201

enum ClientStatusCode 
{
	DEFAULT,
	OK_200,
	OK_200_POST,
	OK_200_DEL,
	BAD_REQUEST_400,
	NOT_FOUND_404,
	FORBIDDEN_403,
	INTERNAL_SERVER_ERROR_500
};

std::string responce_code(int state);

#endif