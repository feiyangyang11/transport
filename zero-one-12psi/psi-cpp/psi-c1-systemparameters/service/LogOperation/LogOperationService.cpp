#include "stdafx.h"
#include "LogOperationService.h"
#include "../../dao/LogOperation/LogOperationDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

LogOperationPageDTO::Wrapper LogOperationService::listAll(const LogOperationQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = LogOperationPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;
	//查询总条数
	LogOperationDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}
	//分页查询
	pages->total = count;
	pages->calcPages();
	list<LogOperationDO> result = dao.selectWithPage(query);

	for (auto& sub : result)
	{
		auto dto = LogOperationDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id, user, User,time, Time, info, Info);
		pages->addData(dto);
	}
	return pages;
}

LogOperationResponseDTO::Wrapper LogOperationService::saveData(const LogOperationAddDTO::Wrapper& dto)
{
	//定义保存的对象
	LogOperationDO data;
	UuidFacade uf;
	std::string uuid = uf.genUuid();
	if (uuid.empty()) {
		throw std::runtime_error("failed to generate uuid");
	}
	//获取时间
	std::string operationTime = SimpleDateTimeFormat::format();
	if (operationTime.empty()) {
		throw std::runtime_error("failed to generate operation time");
	}
	data.setId(uuid);
	data.setUser(dto->user.getValue(""));
	data.setTime(operationTime);
	data.setInfo(dto->info.getValue(""));
	
	//执行
	LogOperationDAO dao;
	auto result = LogOperationResponseDTO::createShared();
	if (dao.insert(data) == 1)
	{
		result->operationTime = operationTime;
	}
	else {
		result->operationTime = "";
	}

	return result;
}

LogOperationResultDTO::Wrapper LogOperationService::deleteAll()
{
	auto dto = LogOperationResultDTO::createShared();
	//获取时间
	std::string operationTime = SimpleDateTimeFormat::format();
	if (operationTime.empty()) {
		throw std::runtime_error("failed to generate operation time");
	}
	LogOperationDAO dao;
	int affectedRows = dao.removeAll();
	dto->operationTime = operationTime;
	dto->clearedCount = oatpp::String(std::to_string(affectedRows));
	if (!dto->operationTime) dto->operationTime = "";
	if (!dto->clearedCount) dto->clearedCount = "-1";
	return dto;
}
