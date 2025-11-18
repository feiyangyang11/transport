#include "ReceiptService.h"

//分页查询 
ReceiptPageDTO::Wrapper ReceiptService::listAll(const ReceiptQuery::Wrapper& query)
{
	//1，创建分页DTO
	auto pages = ReceiptPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;
	//2.查询总记录数
	ReceiptDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}
	
	//3.设置分页信息
	pages->total = count;//数据总条数
	pages->calcPages(); //总页数
	
	//4.分页查询数据
	list<numberDO> reuslt = dao.selectWithPage(query);

	//5.DO转DTO(接受DAO的DO数据，转成DTO数据类型，传输给Controller层)
	for (numberDO& sub : reuslt)
	{
		auto dto = ReceiptgetDTO::createShared();
		/**
		* DO转DTO帮助宏，注意该宏只支持30个字段转换，超出30个字段，反复调用该宏调用即可
		* @param target: 属性值接收目标对象
		* @param src: 属性值来源对象
		* @param ...: 字段参数：目标对象字段名,来源对象get方法名称(去除get后剩余部分)。如:id,Id,name,Name......
		*/
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, numberType, Number_type,number,Number, create_time,Create_time);
		pages->addData(dto);
	}

	return pages;
}
//获取编号
ReceiptgetDTO::Wrapper ReceiptService::addNumber(const ReceiptAddNumberDTO::Wrapper& dto)
{
	numberDO data;
	// DTO转DO
	// (并添加编号类型)
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, Number_type, NumberType);
	
	//添加生成日期
	ReceiptDateTimeFormat time;
	data.setCreate_time(time.format());

	//添加编号数字(查询到最大的数是多少，然后再加一)
	ReceiptDAO dao;
	
	data.setNumber(dao.getLargestNumber(data.getNumber_type()));


	//执行dao层的插入函数
	dao.insertNumber(data);
	
	
	

	/**
	* DO转DTO
	*/
	auto con = ReceiptgetDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO(con, data, numberType, Number_type, number, Number, create_time, Create_time);
	
	return con;
}
//删除编号
bool ReceiptService::removeNumber(const ReceiptgetDTO::Wrapper& dto)
{
	numberDO data;
	// DTO转DO
	// (并添加ReceiptgetDTO中的数据)
	ZO_STAR_DOMAIN_DTO_TO_DO(data,dto, Number_type, numberType, Number, number, Create_time, create_time);
	
	//执行dao中的删除操作
	ReceiptDAO dao;
	return dao.removeNumber(data);
}
