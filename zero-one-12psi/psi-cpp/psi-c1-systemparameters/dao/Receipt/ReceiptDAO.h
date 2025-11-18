
#ifndef _RECEIPTDAO_H_
#define _RECEIPTDAO_H_
#pragma once
#include"../../../lib-mysql/include/BaseDAO.h"
#include"../../domain/query/Receipt/ReceiptQuery.h"
#include"../../domain/do/Receipt/ReceiptDO.h"

//DAO层与数据库交互
class ReceiptDAO : public BaseDAO 
{
public:
	//查询总记录数√
	int count(const ReceiptQuery::Wrapper &query);

	//查询对应类型的最大单据数字数字是多少
	int getLargestNumber(string numbertype);

	//分页查询√
	std::list<numberDO> selectWithPage(const ReceiptQuery::Wrapper& query);

	//插入(并获取nuberDo，传输给contorller层)
	int insertNumber(const numberDO& data);

	//删除单据编号
	bool removeNumber(const numberDO& data);

private:
	//调用queryConditionBuilder方法添加WHERE条件√
	std::string queryConditionBuilder(const ReceiptQuery::Wrapper& query,SqlParams& params);

	

};






#endif // !_RECEIPTDAO_H_


