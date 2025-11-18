#include "LogOperationDAO.h"
#include "LogOperationMapper.h"

inline std::string LogOperationDAO::queryConditionBuilder(const LogOperationQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->user)
	{
		sqlCondition<< " AND `user`=?";
		SQLPARAMS_PUSH(params,"s",std::string,query->user.getValue(""));
	}
	if (query->begintime)
	{
		sqlCondition << " AND `time`>=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->begintime.getValue(""));
	}
	if (query->endtime)
	{
		sqlCondition << " AND `time`<=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->endtime.getValue(""));
	}
	if (query->info)
	{
		sqlCondition << " AND `info`=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->info.getValue(""));
	}

	return sqlCondition.str();
}

uint64_t LogOperationDAO::count(const LogOperationQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM log ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<LogOperationDO> LogOperationDAO::selectWithPage(const LogOperationQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT id,time,user,info FROM log ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 构建排序语句
	//sql += " ORDER BY IFNULL(`update_time`, `create_time`) DESC, `id` DESC ";
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	// 执行查询
	return sqlSession->executeQuery<LogOperationDO>(sql, LogOperationMapper(), params);
}

int LogOperationDAO::removeAll()
{
	// 执行删除所有记录的SQL语句
	std::string sql = "DELETE FROM log";
	// 返回受影响的行数
	int affectedRows = sqlSession->executeUpdate(sql);

	return affectedRows; // 返回实际删除的记录数
}