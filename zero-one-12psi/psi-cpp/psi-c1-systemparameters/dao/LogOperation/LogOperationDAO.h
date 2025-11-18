#ifndef _LOGOPERATION_DAO_
#define _LOGOPERATION_DAO_

#include "BaseDAO.h"
#include "../../domain/do/LogOperation/LogOperationDO.h"
#include "../../domain/query/LogOperation/LogOperationQuery.h"

class LogOperationDAO :public BaseDAO
{
	inline std::string queryConditionBuilder(const LogOperationQuery::Wrapper& query, SqlParams& params);
public:
	// 统计数据条数
	uint64_t count(const LogOperationQuery::Wrapper& query);
	// 分页查询数据
	std::list<LogOperationDO> selectWithPage(const LogOperationQuery::Wrapper& query);
	//清空所有数据
	int removeAll();
};


#endif // !_LOGOPERATION_DAO_
