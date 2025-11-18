
#ifndef _LOGOPERATION_DO_
#define _LOGOPERATION_DO_
#include"../DoInclude.h"

class LogOperationDO :public BaseDO
{
	//编号
	MYSQL_SYNTHESIZE(string, id, Id);
	//操作时间
	MYSQL_SYNTHESIZE(string, time, Time);
	//操作用户
	MYSQL_SYNTHESIZE(string, user, User);
	//操作内容
	MYSQL_SYNTHESIZE(string, info, Info);
public:
	LogOperationDO() :BaseDO("log")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("time", "dt", time);
		MYSQL_ADD_FIELD("user", "s", user);
		MYSQL_ADD_FIELD("info", "s", info);
	}
};
//指针别名
using PtrLogOperationDO = std::shared_ptr<LogOperationDO>;

#endif // !_LOGOPERATION_DO_


