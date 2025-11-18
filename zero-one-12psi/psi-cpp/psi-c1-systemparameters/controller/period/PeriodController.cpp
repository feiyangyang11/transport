/*
@author: AC
@date:2025/10/17
@file:PeriodDO.h
*/

#include "PeriodController.h"
#include "domain/vo/period/PeriodVO.h"
#include "service/period/PeriodService.h"
#include "ResultStatus.h"

// 结账操作
PeriodJsonVO::Wrapper PeriodController::execSavePeriod(const SavePeriodDTO::Wrapper& dto, const PayloadDTO& payload) {
	std::string checkData = dto->data ? dto->data->c_str() : "";
	// 检查日期是否为空
	if (checkData.empty()) {
		PeriodJsonVO::Wrapper resVO = PeriodJsonVO::createShared();
		resVO->init("", RS_PARAMS_INVALID);	// 上传参数异常
		return resVO;
	}
    // 检查日期是否合法（格式：YYYY-MM-DD）
    // 1. 格式校验：长度、分隔符位置
    if (checkData.length() != 10) {
        PeriodJsonVO::Wrapper resVO = PeriodJsonVO::createShared();
        resVO->init("", RS_PARAMS_INVALID);	// 格式长度错误
        return resVO;
    }
    if (checkData[4] != '-' || checkData[7] != '-') {
        PeriodJsonVO::Wrapper resVO = PeriodJsonVO::createShared();
        resVO->init("", RS_PARAMS_INVALID);	// 分隔符位置错误
        return resVO;
    }

    // 2. 提取年、月、日字符串并校验是否为纯数字
    string yearStr = checkData.substr(0, 4);   // 年份部分（0-3索引）
    string monthStr = checkData.substr(5, 2);  // 月份部分（5-6索引）
    string dayStr = checkData.substr(8, 2);    // 日期部分（8-9索引）

    // 工具函数：检查字符串是否全为数字
    auto isAllDigits = [](const string& s) {
        for (char c : s) {
            if (!isdigit(c)) return false;
        }
        return true;
        };
    if (!isAllDigits(yearStr) || !isAllDigits(monthStr) || !isAllDigits(dayStr)) {
        PeriodJsonVO::Wrapper resVO = PeriodJsonVO::createShared();
        resVO->init("", RS_PARAMS_INVALID);	// 包含非数字字符
        return resVO;
    }

    // 3. 转换为整数并校验范围
    int year, month, day;
    try {
        year = stoi(yearStr);
        month = stoi(monthStr);
        day = stoi(dayStr);
    }
    catch (...) {
        // 转换失败（如数字超出int范围）
        PeriodJsonVO::Wrapper resVO = PeriodJsonVO::createShared();
        resVO->init("", RS_PARAMS_INVALID);
        return resVO;
    }

    // 校验年、月的基本范围
    if (year < 1 || month < 1 || month > 12) {
        PeriodJsonVO::Wrapper resVO = PeriodJsonVO::createShared();
        resVO->init("", RS_PARAMS_INVALID);	// 年或月超出有效范围
        return resVO;
    }

    // 4. 校验日期是否符合当月天数（考虑闰年）
    int maxDay;
    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        maxDay = 31;  // 大月31天
        break;
    case 4: case 6: case 9: case 11:
        maxDay = 30;  // 小月30天
        break;
    case 2:  // 2月需判断闰年
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            maxDay = 29;  // 闰年29天
        }
        else {
            maxDay = 28;  // 平年28天
        }
        break;
    default:
        maxDay = 0;  // 不会执行（已校验month范围）
    }

    if (day < 1 || day > maxDay) {
        PeriodJsonVO::Wrapper resVO = PeriodJsonVO::createShared();
        resVO->init("", RS_PARAMS_INVALID);	// 日期超出当月最大天数
        return resVO;
    }

    // 所有校验通过，日期合法

	PeriodService service;
	bool saveSuccess = service.savePeriod(dto, payload);
	PeriodJsonVO::Wrapper resVO = PeriodJsonVO::createShared();
	if (saveSuccess) {
		resVO->success(checkData);
	}
	else {
		resVO->init("", ResultStatus(u8"结账失败", 9999));
	}
	return resVO;
}



// 反结账操作
PeriodJsonVO::Wrapper PeriodController::execDeletePeriod(const PayloadDTO& payload) {
	PeriodService service;
	bool saveSuccess = service.cancelPeriod(payload);
	PeriodJsonVO::Wrapper resVO = PeriodJsonVO::createShared();
	if (saveSuccess) {
		resVO->success(u8"反结账成功");
	}
	else {
		resVO->init("", ResultStatus(u8"反结账失败", 9999));
	}
	return resVO;
}


// 分页查询实现
/*PeriodRecordPageRespVO::Wrapper PeriodController::execQueryPeriods(const PeriodRecordPageReqDTO::Wrapper& dto) {
    // 创建响应VO对象（初始化状态为成功）
    auto respVO = PeriodRecordPageRespVO::createShared();
    respVO->state = "success";  // 默认成功状态

    // 处理分页参数
    int32_t pageIndex = dto->pageIndex ? *dto->pageIndex : 1;  // 页码默认1
    int32_t pageSize = dto->pageSize ? *dto->pageSize : 20;    // 每页条数默认30
    if (pageIndex < 1) pageIndex = 1;
    if (pageSize < 1 || pageSize > 300) pageSize = 30;  // 限制最大条数为300

    // 调用服务层获取分页数据
    PeriodService service;

    std::shared_ptr<PeriodPageResult> res = service.queryPeriods(pageIndex, pageSize);
    auto periodList = res->records;
	auto totalCount = res->total;

    // 转换DO列表为VO列表（将数据库实体转换为前端展示实体）
    auto recordList = oatpp::List<PeriodRecordVO::Wrapper>::createShared();
    for (const auto& periodDO : periodList) {
        auto recordVO = PeriodRecordVO::createShared();
        // 填充VO字段
        recordVO->date = periodDO.getDate();        // 日期直接复用
        recordVO->time = periodDO.getTime();        // 时间直接复用
        recordVO->user = periodDO.getUser();		// 操作人直接复用

        recordList->push_back(recordVO);
    }

    // 填充响应VO的总记录数和数据列表
    respVO->count = oatpp::Int64(totalCount);  // 总记录数
    respVO->info = recordList;                 // 当前页数据列表

    // 返回响应对象
    return respVO;
}*/

PeriodRecordPageRespVO::Wrapper PeriodController::execQueryPeriods(const PeriodRecordPageReqDTO::Wrapper& dto) {
    auto respVO = PeriodRecordPageRespVO::createShared();
    respVO->state = "success";

    int32_t pageIndex = dto->pageIndex ? *dto->pageIndex : 1;
    int32_t pageSize = dto->pageSize ? *dto->pageSize : 20;
    if (pageIndex < 1) pageIndex = 1;
    if (pageSize < 1 || pageSize > 300) pageSize = 30;

    PeriodService service;
    auto res = service.queryPeriods(pageIndex, pageSize);
    auto& periodList = res->records;  // 智能指针列表
    auto totalCount = res->total;

    auto recordList = oatpp::List<PeriodRecordVO::Wrapper>::createShared();
    // 遍历智能指针列表
    for (const auto& periodDO : periodList) {
        auto recordVO = PeriodRecordVO::createShared();
        recordVO->date = periodDO->getDate();
        recordVO->time = periodDO->getTime();
        recordVO->user = periodDO->getUser();

        recordList->push_back(recordVO);
    }

    respVO->count = oatpp::Int64(totalCount);
    respVO->info = recordList;

    return respVO;
}