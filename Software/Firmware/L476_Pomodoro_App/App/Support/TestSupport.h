#ifndef TEST_SUPPORT_H
#define TEST_SUPPORT_H

//--------------------------------------------
// application version
//--------------------------------------------
#define VERSION_MAJOR (0)
#define VERSION_MINOR (1)

//--------------------------------------------
// useful test overrides
//--------------------------------------------
#ifdef TEST
#define FOREVER (0)
#define STATIC
#define INLINE
#else
#define FOREVER (1)
#define STATIC static
#define INLINE inline
#endif

#endif /* TEST_SUPPORT_H */