#ifndef REGISTER_ACCESS_H
#define REGISTER_ACCESS_H

#ifndef BIT_TO_MASK
#define BIT_TO_MASK(a) (1u << (a))
#endif

#ifndef SET_BIT
#define SET_BIT(REG, BIT) ((REG) |= (BIT))
#endif

#ifndef CLEAR_BIT
#define CLEAR_BIT(REG, BIT) ((REG) &= ~(BIT))
#endif

#ifndef READ_BIT
#define READ_BIT(REG, BIT) ((REG) & (BIT))
#endif

#ifndef CLEAR_REG
#define CLEAR_REG(REG) ((REG) = (0x0))
#endif

#ifndef WRITE_REG
#define WRITE_REG(REG, VAL) ((REG) = (VAL))
#endif

#ifndef READ_REG
#define READ_REG(REG) ((REG))
#endif

#ifndef MODIFY_REG
#define MODIFY_REG(REG, CLEARMASK, SETMASK) WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
#endif

#endif /*REGISTER_ACCESS_H*/