/*
@author: AC
@date:2025/10/17
@file:PeriodService.h
*/

#ifndef _PERIOD_SERVICE_H_
#define _PERIOD_SERVICE_H_ 
#include "domain/dto/period/PeriodDTO.h"
#include "domain/vo/period/PeriodVO.h"
#include "dao/period/PeriodDAO.h"
#include "domain/do/period/PeriodDO.h"
#include "id/UuidFacade.h"

// 分页查询结果结构体
struct PeriodPageResult {
	int64_t total = 0;  // 总记录数
	std::list<std::unique_ptr<PeriodDO>>  records;// 当前页记录列表
};


class PeriodService {
public:
	// 结账
	bool savePeriod(const SavePeriodDTO::Wrapper& dto, const PayloadDTO& payload);
	// 反结账
	bool cancelPeriod(const PayloadDTO& payload);

	// 分页查询结账记录
	std::shared_ptr<PeriodPageResult> queryPeriods(int32_t pageIndex, int32_t pageSize);


};







#endif