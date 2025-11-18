/*
@author: AC
@date:2025/10/17
@file:PeriodDO.h
*/

#ifndef _PERIOD_DO_H_
#define _PERIOD_DO_H_

#include "../DoInclude.h"

/*
* 结账记录DO
*/
class PeriodDO : public BaseDO {
public:
	// 结账id
	MYSQL_SYNTHESIZE(string, id, Id);
	// 结账日期
	MYSQL_SYNTHESIZE(string, date, Date);
	// 操作日期
	MYSQL_SYNTHESIZE(string, time, Time);
	// 操作人
    MYSQL_SYNTHESIZE(string, user, User);


	PeriodDO() : BaseDO("period") {
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("date", "s", date);
		MYSQL_ADD_FIELD("time", "s", time);
		MYSQL_ADD_FIELD("user", "s", user);
	}
};


#endif 