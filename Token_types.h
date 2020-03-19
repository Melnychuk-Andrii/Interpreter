#ifndef TOKEN_TYPES
#define TOKEN_TYPES

extern enum token_type {tINT,
						tPLUS,
						tMINUS,
						tMUL,
						tDIV,
						tLPAR,
						tRPAR,
						tFLOAT };

extern const char* token_names[] = {"tINT",
									"tPLUS",
									"tMINUS",
									"tMUL",
									"tDIV",
									"tLPAR",
									"tRPAR",
									"tFLOAT"};

#endif
