#ifndef _UPDATEX_H_
#define _UPDATEX_H_

#include"initX.h"
void updateTimetable();//每小时更新所有城市的交通表
PASS* updatePassStage(PASS* prePass, PASS* tmpPass);//更新tmpPass的状态，其中prePass起辅助作用

#endif // !_UPDATEX_H_