#define ERR_GENERAL 1	//General error or unspecified error
#define ERR_MISUSE_BUILTIN 2	//Misuse of shell builtins (e.g., missing keyword or command)
#define ERR_CMD_CANT_EXE 126	//Command invoked cannot execute (e.g., permissions issue)
#define ERR_CMD_NOT_FOUND 127	//Command not found

#define ERR_UNCLOSED_QUOTE  1
#define ERR_UNEXPECTED_TOKEN 2
#define ERR_SYNTAX 3
