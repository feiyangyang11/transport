/*
@author: AC
@date:2025/10/17
@file:PeriodController.h
*/

#ifndef _PERIOD_CONTROLLER_H_
#define _PERIOD_CONTROLLER_H_
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "domain/vo/period/PeriodVO.h"
#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/period/PeriodQuery.h"
#include "domain/dto/period/PeriodDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("period.tag")

class PeriodController : public oatpp::web::server::api::ApiController {
	// 定义控制器访问入口
	API_ACCESS_DECLARE(PeriodController);
public:
	// 结账端点
	ENDPOINT_INFO(savePeriod) {
		// 添加安全验证
		info->addSecurityRequirement("bearer_auth");
		// 标题
		info->summary = ZH_WORDS_GETTER("period.save.summary");
		// 标签
		info->addTag(API_TAG);
		// 响应
		info->addResponse<PeriodJsonVO::Wrapper>(Status::CODE_200, "application/json");
	}
	ENDPOINT("POST", "/periods/save", savePeriod, BODY_DTO(SavePeriodDTO::Wrapper, dto), AUTHORIZATION(std::shared_ptr<CustomerAuthorizeObject>, authObject)) {
		return createDtoResponse(Status::CODE_200, execSavePeriod(dto,authObject->getPayload()));
	}

	// 反结账端点
	ENDPOINT_INFO(deletePeriod) {
		// 添加安全验证
		info->addSecurityRequirement("bearer_auth");
		// 标题
		info->summary = ZH_WORDS_GETTER("period.delete.summary");
		// 标签
		info->addTag(API_TAG);
		// 响应
		info->addResponse<PeriodJsonVO::Wrapper>(Status::CODE_200, "application/json");
	}
	ENDPOINT("DELETE", "/periods/delete", deletePeriod,AUTHORIZATION(std::shared_ptr<CustomerAuthorizeObject>, authObject)) {
		return createDtoResponse(Status::CODE_200, execDeletePeriod(authObject->getPayload()));
	}

	// 分页查询
	ENDPOINT_INFO(queryPeriods) {
		// 添加安全验证
		info->addSecurityRequirement("bearer_auth");
		// 标题
		info->summary = ZH_WORDS_GETTER("period.get.summary");
		// 标签
		info->addTag(API_TAG);
		// 响应
		info->addResponse<PeriodRecordPageRespVO::Wrapper>(Status::CODE_200, "application/json");
	}
	ENDPOINT("GET", "/periods/query", queryPeriods, QUERY(Int32, pageIndex, "pageIndex", 1), QUERY(Int32, pageSize, "pageSize", 20),AUTHORIZATION(std::shared_ptr<CustomerAuthorizeObject>, authObject)) {
		auto dto = PeriodRecordPageReqDTO::createShared();
		dto->pageIndex = pageIndex;
		dto->pageSize = pageSize;
        return createDtoResponse(Status::CODE_200, execQueryPeriods(dto));
	}
private:
	// 结账操作
	PeriodJsonVO::Wrapper execSavePeriod(const SavePeriodDTO::Wrapper& dto, const PayloadDTO& payload);
	// 反结账操作
	PeriodJsonVO::Wrapper execDeletePeriod(const PayloadDTO& payload);
	// 分页查询
	PeriodRecordPageRespVO::Wrapper execQueryPeriods(const PeriodRecordPageReqDTO::Wrapper& dto);
};



#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)


#endif