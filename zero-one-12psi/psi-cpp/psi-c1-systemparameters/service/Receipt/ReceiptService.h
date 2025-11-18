#ifndef _RECEIPTSERVICE_H
#define _RECEIPTSERVICE_H
#pragma once
#include "../../domain/dto/Receipt/ReceiptDTO.h"
#include "../../domain/query/Receipt/ReceiptQuery.h"
#include "../../dao/Receipt/ReceiptDAO.h"
#include "../../../arch-skeleton/Macros.h"
#include "../../domain/do/Receipt/ReceiptDO.h"
class ReceiptService
{
public:

//分页查询单据编号
	ReceiptPageDTO::Wrapper listAll(const ReceiptQuery::Wrapper& query);

//新增(获取)单据编号
	ReceiptgetDTO::Wrapper addNumber(const ReceiptAddNumberDTO::Wrapper& dto);
//删除单据编号
	bool  removeNumber(const ReceiptgetDTO::Wrapper& dto);
};

//编号生成的时间工具类
class ReceiptDateTimeFormat
{
public:
	//获取当前时间（当前编号生成时间）
	std::string format()
	{
		auto now = std::chrono::system_clock::now();
		auto time_t = std::chrono::system_clock::to_time_t(now);

		std::stringstream time;
		time << std::put_time(std::localtime(&time_t), "%Y-%m-%d");

		return time.str();
	}
};



#endif // !_RECEIPTSERVICE_H


