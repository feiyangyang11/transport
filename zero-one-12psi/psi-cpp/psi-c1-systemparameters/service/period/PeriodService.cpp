/*
@author: AC
@date:2025/10/17
@file:PeriodService.h
*/
#include "stdafx.h"
#include "PeriodService.h"
#include "SimpleDateTimeFormat.h"
#include "id/UuidFacade.h"

bool PeriodService::savePeriod(const SavePeriodDTO::Wrapper& dto, const PayloadDTO& payload) {
	// 结账日期
	std::string checkDate = dto->data ? dto->data->c_str() : "";

	// 检查该日期是否已结账（避免重复结账）
	PeriodDAO dao;
	if (dao.existsByDate(checkDate)) return false;

	PeriodDO periodDO;
	UuidFacade uf1;
	periodDO.setId(uf1.genUuid());
	periodDO.setDate(checkDate);
	string time_ = SimpleDateTimeFormat::format("%Y-%m-%d %H:%M:%S");
	size_t pos = time_.find(" ");
	periodDO.setTime(time_.substr(0,pos));
	periodDO.setUser(payload.getUsername());
	// 插入结账数据
	if (dao.insertPeriod(periodDO)) {
		// 插入操作日志
		UuidFacade uf2;
		periodDO.setId(uf2.genUuid());
		periodDO.setTime(time_);
		if (!dao.insertLog(periodDO, u8"结账成功")) {
			return false;
		}
	}
	else {
		dao.insertLog(periodDO, u8"结账失败");
		return false;
	}
	return true;
}


// 反结账：自动撤销最新结账日期
bool PeriodService::cancelPeriod(const PayloadDTO& payload) {
	PeriodDAO dao;
	// 查询数据库中最新的结账日期
	std::string latestDate = dao.getLatestPeriodDate();
	// 检查是否有可反结账的记录（最新日期为空=无结账记录）
	if (latestDate.empty()) {
		std::cerr << "cancelPeriod: 无任何结账记录，无法反结账" << std::endl;
		return false;
	}

	// 准备反结账相关数据
	std::string currentTime = SimpleDateTimeFormat::format("%Y-%m-%d %H:%M:%S");
	PeriodDO periodDO;

	try {
		// 3. 第三步：删除最新日期的结账记录
		bool deleteSuccess = dao.deletePeriodByDate(latestDate);
		if (deleteSuccess) {
			// 4. 反结账成功：插入成功日志
			UuidFacade uf;
			periodDO.setId(uf.genUuid());
			periodDO.setTime(currentTime);
			periodDO.setUser(payload.getUsername());
			periodDO.setDate(latestDate);       // 记录被反结账的最新日期（便于追溯）
			// 插入日志：明确标注“撤销最新日期”
			if (dao.insertLog(periodDO, u8"反结账成功：撤销最新结账日期【" + latestDate + u8"】")) {
				std::cout << "cancelPeriod: 反结账成功，已撤销最新日期【" << latestDate << "】" << std::endl;
				return true;
			}
			else {
				std::cerr << "cancelPeriod: 反结账成功，但操作日志插入失败" << std::endl;
				return false;
			}
		}
		else {
			// 5. 反结账失败：删除最新日期记录失败，插入失败日志
			UuidFacade uf;
			periodDO.setId(uf.genUuid());
			periodDO.setTime(currentTime);
			periodDO.setUser(payload.getUsername());
			periodDO.setDate(latestDate);
			dao.insertLog(periodDO, u8"反结账失败：删除最新日期【" + latestDate + u8"】的结账记录失败");
			std::cerr << "cancelPeriod: 反结账失败，无法删除最新日期【" << latestDate << "】的记录" << std::endl;
			return false;
		}
	}
	catch (const std::exception& e) {
		// 6. 异常处理：捕获数据库错误（如连接中断），插入异常日志
		UuidFacade uf;
		periodDO.setId(uf.genUuid());
		periodDO.setTime(currentTime);
		periodDO.setUser(payload.getUsername());
		periodDO.setDate(latestDate);
		dao.insertLog(periodDO, u8"反结账异常：" + std::string(e.what()) + u8"（涉及日期：" + latestDate + u8"）");
		std::cerr << "cancelPeriod 异常：" << e.what() << "（最新日期：" << latestDate << "）" << std::endl;
		return false;
	}
}


// 分页查询结账记录
std::shared_ptr<PeriodPageResult> PeriodService::queryPeriods(int32_t pageIndex, int32_t pageSize) {
	auto result = std::make_shared<PeriodPageResult>();
	PeriodDAO dao;

	int32_t offset = (pageIndex < 1) ? 0 : (pageIndex - 1) * pageSize;

	// 获取总记录数和智能指针列表
	result->total = dao.countAll();
	result->records = dao.queryByPage(offset, pageSize);

	return result;
}