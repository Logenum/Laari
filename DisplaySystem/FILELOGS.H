extern int Logprintf(const char *, ...); /* function with variable argument count */
extern UINT LogDate(void);

extern UINT LogLoc(char *, UINT);
extern UINT LodLoc(char *, UINT);

extern int LogVars(char *,
									 UINT,
									 const char *, ...);
extern int LodVars(char *,
									 UINT,
									 const char *, ...);

