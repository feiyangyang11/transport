#ifndef _RECEIPTDO_H_
#define	_RECEIPTDO_H_

#pragma once
#include"../DoInclude.h"
/**
* numberDO --单据编号数据库实例对象
*/

class numberDO : public BaseDO 
{
	//主键ID --> ID
	MYSQL_SYNTHESIZE(long long, id, ID);

	//单据类型 --> VARCHAR(20)
	MYSQL_SYNTHESIZE(string, number_type, Number_type);

	//流水号数字 --> INT
	MYSQL_SYNTHESIZE(int, number, Number);

	//创建时间 --> string  mysql将DAYETIME转化为字符串传输过来 
	MYSQL_SYNTHESIZE(string, create_time, Create_time);

public:
	/**
	* 构造函数，配置数据库表名和字段映射
	* 
	* BaseDO("Number")    指定数据库表名
	*/

	numberDO() : BaseDO("number")
	{
		//配置主键字段
		MYSQL_ADD_FIELD_PK("id", "ll", id);



		//配置普通字段(可以指定是否为NULL)
		MYSQL_ADD_FIELD_NULLABLE("number_type","s", number_type,false);
		MYSQL_ADD_FIELD_NULLABLE("number", "i", number, false);
		MYSQL_ADD_FIELD("create_time", "s", create_time);
	}
};
//定义智能指针类型别名（方便使用）
using PtrnumberDO = std::shared_ptr<numberDO>;

#endif // !_NUMBERDO_H_