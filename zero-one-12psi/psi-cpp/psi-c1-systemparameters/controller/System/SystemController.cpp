/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/10/13 21:38:24

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#include "stdafx.h"
#include "SystemController.h"

#include "./SystemController.h"

SystemJsonVO::Wrapper SystemController::executeQueryAll() {
	SystemService systemService;
	auto responseVO = SystemJsonVO::createShared();
	auto result = systemService.listAll();
	responseVO->success(result);
	return responseVO;
}
SystemRespJsonVO::Wrapper SystemController::executeModifyAll(const Vector<SystemDTO::Wrapper>& dto) {
	SystemService systemService;
	auto responseVO = SystemRespJsonVO::createShared();
	// 检查参数是否为空
    if (dto->empty()) {
        responseVO->init(nullptr, RS_PARAMS_INVALID);
        return responseVO;
    }
    for (auto& one : *dto) {
        if (!one->id) {		// id为空了
            responseVO->NoId(5444);
            return responseVO;
        }
        if (one->id->size() > 48) {		// id太长了
            responseVO->ExceedId(oatpp::Int32(5443));
            return responseVO;
        }
        if ((one->id == "e7eb5c8d86594bb6935ffea74aa41176") && (!one->name)) {  // 缺少必要字段
            responseVO->lackof(oatpp::Int32(5334));
            return responseVO;
        }
        if ((one->id == "f6dd31284c5f492f8682ee2097360796") && (!one->name)) {  // 缺少必要字段
            responseVO->lackof(oatpp::Int32(5334));
            return responseVO;
        }
        if ((one->id == "e7eb5c8d86594bb6935ffea74aa41176") && (one->name = "name") && (!one->info || one->info == "")) {	// 系统名称不能为空
            responseVO->unknownSystemName(oatpp::Int32(5437));
            return responseVO;
        }
        if ((one->id == "f6dd31284c5f492f8682ee2097360796") && (one->name = "company") && (!one->info || one->info == "")) {	// 公司名称不能为空
            responseVO->unknownCompanyName(oatpp::Int32(5436));
            return responseVO;
        }
        if (one->info && (one->info->size() > 1024)) {		// info太长了
            responseVO->ExceedInfo(oatpp::Int32(5442));
            return responseVO;
        }
        if (one->remark && (one->remark->size() > 64)) {		// data太长了
            responseVO->ExceedData(oatpp::Int32(5440));
            return responseVO;
        }
        if (one->name && (one->name->size() > 64)) {		// name太长了
            responseVO->ExceedName(oatpp::Int32(5441));
            return responseVO;
        }
    }
    Int32 result = systemService.updateById(dto);

    switch (result) {
    case 0:  // 成功（假设原success方法继承自JsonVO，此处保持原有逻辑）
        responseVO->success(oatpp::Int32(0));
        break;
    case 5444:  // 缺少Id（RS_IDNOTFOUND）
        responseVO->NoId(oatpp::Int32(5444));
        break;
    case 5443:  // Id过长（RS_IDEXCEED）
        responseVO->ExceedId(oatpp::Int32(5443));
        break;
    case 5442:  // Info过长（RS_INFOEXCEED）
        responseVO->ExceedInfo(oatpp::Int32(5442));
        break;
    case 5441:  // Name过长（RS_NAMEEXCEED）
        responseVO->ExceedName(oatpp::Int32(5441));
        break;
    case 5440:  // Data过长（RS_DATAEXCEED）
        responseVO->ExceedData(oatpp::Int32(5440));
        break;
    case 5439:  // 缺少Name（RS_NAMENOTFOUND）
        responseVO->NoName(oatpp::Int32(5439));
        break;
    case 5438:  // 缺少Info（RS_INFONOTFOUND）
        responseVO->NoInfo(oatpp::Int32(5438));
        break;
    case 5437:  // 系统名称不能为空（RS_SYSTEMNAMENOTFOUND）
        responseVO->unknownSystemName(oatpp::Int32(5437));
        break;
    case 5436:  // 公司名称不能为空（RS_COMPANYNAMENOTFOUND）
        responseVO->unknownCompanyName(oatpp::Int32(5436));
        break;
    case 5435:
        responseVO->unknownId(oatpp::Int32(5435));
        break;
    case -1:   // 未知错误（RS_UNKNOWNERROR）
        responseVO->unknownError(oatpp::Int32(-1));
        break;
    case -2:   // SQL错误（RS_SQLERROR）
        responseVO->sqlError(oatpp::Int32(-2));
        break;
    default:   // 未定义的错误码，统一按未知错误处理
        responseVO->unknownError(oatpp::Int32(result));  // 传递原始错误码便于排查
        break;
    }
	return responseVO;
}