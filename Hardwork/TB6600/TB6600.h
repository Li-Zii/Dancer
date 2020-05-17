#ifndef _a4988_H
#define _a4988_H

#include "system.h"

/*  LED时钟端口、引脚定义 */



#define Direction PBout(8)
#define M1 PBout(1)
#define M2 PBout(3)
#define M3 PBout(4)
#define Enable PBout(6)




void TB6600_Init(void);


#endif
