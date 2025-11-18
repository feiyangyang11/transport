#include "ReceiptDAO.h"
#include "./ReceiptMapper.h"

//查询总记录数
int ReceiptDAO::count(const ReceiptQuery::Wrapper &query)
{
	//创建sql参数（用于参数查询，防止sql注入）
	SqlParams params;
	//构建sql语句
	string sql = "SELECT COUNT(*) FROM number ";

	//调用queryConditionBuilder方法添加WHERE条件
	//此方法会根据query中的条件动态添加sql条件
	//同时将参数添加到params中
	sql += queryConditionBuilder(query, params);

	//执行sql语句
	CountMapper mapper;
	auto result = sqlSession->executeQueryOne<int>(sql,mapper,params);
	if (result)
	{
		return result;
	}
	return 0;
}


//查询对应类型的最大单据数字数字是多少
int ReceiptDAO::getLargestNumber(string numbertype)
{
	//创建sql参数，防止sql注入
	SqlParams params;

	//构建sql语句
	string sql = "SELECT MAX(number) FROM number WHERE number_type = ? ";
	SQLPARAMS_PUSH(params, "s", std::string, numbertype);
	//执行sql语句
	CountMapper mapper;
	auto result = sqlSession->executeQueryOne<int>(sql, mapper,params);
	
	return result + 1;
	
	
}


//分页查询
std::list<numberDO> ReceiptDAO::selectWithPage(const ReceiptQuery::Wrapper& query)
{
	//创建sql参数列表（用于参数查询，防止sql注入）
	SqlParams params;
	//构建sql语句（选择字段）
	string sql = "SELECT number_type,create_time,number FROM number ";

	//调用queryConditionBuilder方法添加WHERE条件
	//此方法会根据query中的条件动态添加sql条件
	//同时将参数添加到params中
	SQLPARAMS_PUSH(params, "s", std::string, query->NumberType.getValue(""));
	
	//添加排序规则
	sql += " ORDER BY create_time DESC, number DESC ";
	
	////添加分页限制
	//sql += " LIMIT " + std::to_string(((query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10))) + "," + std::to_string(query->pageSize.getValue(10));
	
	//执行查询
	ReceiptMapper mapper;
	return sqlSession->executeQuery<numberDO>(sql,mapper, params);
}


//插入(并获取nuberDo，传输给contorller层)
int ReceiptDAO::insertNumber(const numberDO& data)
{
	//构建sql插入语句
	string sql = "INSERT INTO number (number_type,number,create_time) VALUES (?,?,?)";

	//创建sql参数列表
	SqlParams params;

	//依此添加参数
	//number_type
	SQLPARAMS_PUSH(params, "s", string, data.getNumber_type());
	//number
	SQLPARAMS_PUSH(params, "i", int, data.getNumber());
	//creat_time
	SQLPARAMS_PUSH(params, "s", string, data.getCreate_time());

	//执行更新（INSERT、UPDATE、DELETE统称为更新操作）
	// sqlSession->executeUpdate方法说明：
	// - 第1个参数：SQL语句
	// - 第2个参数：SqlParams参数列表
	// 返回：受影响的行数（通常是1表示成功，0表示失败）
	return sqlSession->executeUpdate(sql, params);
}

//删除单据编号
bool ReceiptDAO::removeNumber(const numberDO& data)
{
	//构建sql语句
	string sql = "DELETE FROM number WHERE number_type = ? AND number = ? AND create_time = ?";

	//创建sql参数列表
	SqlParams params;
	//number_type
	SQLPARAMS_PUSH(params,"s",string,data.getNumber_type());
	//number
	SQLPARAMS_PUSH(params, "i", int, data.getNumber());
	//creat_time
	SQLPARAMS_PUSH(params, "s", string, data.getCreate_time());


	//执行更新（INSERT、UPDATE、DELETE统称为更新操作）
	// sqlSession->executeUpdate方法说明：
	// - 第1个参数：SQL语句
	// - 第2个参数：SqlParams参数列表
	// 返回：受影响的行数（通常是1表示成功，0表示失败）
	return sqlSession->executeUpdate(sql, params);
}


std::string ReceiptDAO::queryConditionBuilder(const ReceiptQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	if (query->NumberType)
	{
		sqlCondition << " WHERE number_type= ? ";
		SQLPARAMS_PUSH(params, "s", std::string, query->NumberType.getValue(""));
	}
	
	return sqlCondition.str();
}
