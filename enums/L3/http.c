#include "http.h"

char *http_to_str(HttpErrorCode code) {
char* message = "";
  switch (code)
  {
  case HTTP_BAD_REQUEST:
    message =  "400 Bad Request";
    break;
  case HTTP_UNAUTHORIZED:
    message =  "401 Unauthorized";
    break;
  case HTTP_NOT_FOUND:
   message =  "404 Not Found";
    break;
  case HTTP_TEAPOT:
   message =  "418 I AM A TEAPOT!";
    break;
  case HTTP_INTERNAL_SERVER_ERROR:
    message =  "500 Internal Server Error";
    break;
  
  default:
    break;
  }
  return message;
}
