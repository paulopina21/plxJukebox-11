

/* @@ end of prolog @@ */

#ifndef PARAMS
# if __STDC__
#  define PARAMS(Args) Args
# else
#  define PARAMS(Args) ()
# endif
#endif

/* We assume to have `unsigned long int' value with at least 32 bits.  */
#define HASHWORDBITS 32


/* Defines the so called `hashpjw' function by P.J. Weinberger
   [see Aho/Sethi/Ullman, COMPILERS: Principles, Techniques and Tools,
   1986, 1987 Bell Telephone Laboratories, Inc.]  */
static unsigned long hash_string PARAMS ((const char *__str_param));

static inline unsigned long
hash_string (str_param)
     const char *str_param;
{
  unsigned long int hval, g;
  const char *str = str_param;

  /* Compute the hash value for the given string.  */
  hval = 0;
  while (*str != '\0')
    {
      hval <<= 4;
      hval += (unsigned long) *str++;
      g = hval & ((unsigned long) 0xf << (HASHWORDBITS - 4));
      if (g != 0)
	{
	  hval ^= g >> (HASHWORDBITS - 8);
	  hval ^= g;
	}
    }
  return hval;
}
