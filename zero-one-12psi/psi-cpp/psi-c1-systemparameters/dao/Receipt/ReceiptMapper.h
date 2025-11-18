#pragma once
#include "domain/do/Receipt/ReceiptDO.h"
#include"Mapper.h"


//ReceiptMapper映射分页查询数据
class ReceiptMapper : public Mapper<numberDO>
{
public:
	/**
	* 重写虚函数
	*/
	numberDO mapper(ResultSet* resultSet)const override
	{
		numberDO data;
		if (!resultSet)
		{
			throw std::invalid_argument("ResultSet is null");
		}
		/**
		* 映射字段
		*/
		try
		{
			if (!resultSet->isNull("id"))data.setID(resultSet->getUInt64("id"));
			if (!resultSet->isNull("number_type"))data.setNumber_type(resultSet->getString("number_type"));
			if (!resultSet->isNull("create_time"))data.setCreate_time(resultSet->getString("create_time"));
			if (!resultSet->isNull("number"))data.setNumber(resultSet->getInt("number"));

		}
		catch (const std::exception& e)
		{

		}
		return data;
	}
};

//CountMapper映射查询总数据数的数据映射
class CountMapper : public Mapper<int>
{
public:
	/**
	* 重写虚函数
	*/
	int mapper(ResultSet* rs)const override
	{
		if (rs)
		{
			return rs->getInt(1);
		}
		return 0;
	}
};