

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "argp.h"

/* If set by the user program to a non-zero value, then a default option
   --version is added (unless the ARGP_NO_HELP flag is used), which calls
   this function with a stream to print the version to and a pointer to the
   current parsing state, and then exits (unless the ARGP_NO_EXIT flag is
   used).  This variable takes precedent over ARGP_PROGRAM_VERSION.  */
void (*argp_program_version_hook) (FILE *stream, struct argp_state *state) = NULL;
