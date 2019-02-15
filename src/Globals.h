#define DEBUG 0
extern int OUTPUT;
#define DEBUG_INFO(x) {if(DEBUG == 1){}}

#ifdef DEBUG
#define PRINTD printf
#else
#define PRINTD(format, args...) ((void)0)
#endif

#define IN_DEBUG(x) {if(DEBUG){ x } }
#define IN_OUTPUT(x) {if(OUTPUT){ x } }

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)<(b))?(b):(a))

#include <stdbool.h>

void assert(bool b, char* message);
