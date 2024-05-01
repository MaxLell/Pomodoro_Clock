#ifndef TESTSUPPORT_H
#define TESTSUPPORT_H

#ifdef TEST
#define FOREVER (0)
#define STATIC
#define INLINE
#else
#define FOREVER (1)
#define STATIC static
#define INLINE inline
#endif

#endif // TESTSUPPORT_H
