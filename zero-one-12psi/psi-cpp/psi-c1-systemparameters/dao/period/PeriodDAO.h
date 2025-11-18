/*
@author: AC
@date:2025/10/17
@file:PeriodDAO.h
*/

#ifndef PERIOD_DAO_H_
#define PERIOD_DAO_H_ 
#include "BaseDAO.h"
#include "domain/dto/period/PeriodDTO.h"
#include "domain/do/period/PeriodDO.h"
#include "domain/vo/period/PeriodVO.h"  // 包含UserDataVO

class PeriodDAO : public BaseDAO {
public: 
	// 向数据库插入结账信息
	bool insertPeriod(const PeriodDO& periodDO);
	// 查询该日期是否已有结账记录
	bool existsByDate(const string& date);
	// 插入操作日志信息
	bool insertLog(const PeriodDO& periodDO, const string& info);
	// 查询数据库中最新的结账日期
	std::string getLatestPeriodDate();
	// 删除最新日期的结账记录
	bool deletePeriodByDate(const std::string& date);

	// 查询总记录数
	int64_t countAll();

	// 分页查询记录
	std::list<std::unique_ptr<PeriodDO>> queryByPage(int32_t offset, int32_t pageSize);
};







#endif