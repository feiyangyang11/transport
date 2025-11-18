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
#include "LogOperationController.h"
#include "../../service/LogOperation/LogOperationService.h"
#include "SimpleDateTimeFormat.h"
#include <iostream>

LogOperationPageJsonVO::Wrapper LogOperationController::execQueryLog(const LogOperationQuery::Wrapper& query)
{
	//定义返回对象
	auto vo = LogOperationPageJsonVO::createShared();
	auto failDTO = LogOperationPageDTO::createShared();
	failDTO->initAll(1, 10, -1, -1, {});
	try {
		//执行
		LogOperationService service;
		auto result = service.listAll(query);
		//检验
		vo->success(result);
	}
	catch (const std::exception& e) {
		std::cerr << "[execQueryLog异常]：" << e.what() << std::endl; // 后端日志输出
		vo->fail(failDTO);
	}
	catch (...) {
		std::cerr << "[execQueryLog未知异常]" << std::endl;
		vo->fail(failDTO);
	}
	
	//响应结果
	return vo;
}

LogOperationResponseJsonVO::Wrapper LogOperationController::execAddLog(const LogOperationAddDTO::Wrapper& dto, const PayloadDTO& payload)
{
	//定义返回对象
	auto vo = LogOperationResponseJsonVO::createShared();
	auto failDTO = LogOperationResponseDTO::createShared();
	failDTO->operationTime = String(SimpleDateTimeFormat::format());
	try {
		if (!dto->user) { // 检查 user 是否为 null
			throw std::runtime_error("user field cannot be null");
		}
		if (!dto->info) { // 检查 info 是否为 null
			throw std::runtime_error("info field cannot be null");
		}

		//执行
		LogOperationService service;
		dto->setPayload(&payload);
		auto res = service.saveData(dto);
		//检验
		if (res->operationTime != "")
		{
			vo->success(res);
		}
		else
		{
			vo->fail(res);
		}
	}
	catch (const std::exception& e) {
		std::cerr << "[execAddLog异常]：" << e.what() << std::endl; // 后端日志输出
		vo->fail(failDTO);
	}
	catch (...) {
		std::cerr << "[execAddLog未知异常]" << std::endl;
		vo->fail(failDTO);
	}
	
	//响应结果
	return vo;
}

LogOperationResultJsonVO::Wrapper LogOperationController::execClear(const PayloadDTO& payload,const std::string& confirm)
{
	//定义返回对象
	auto vo = LogOperationResultJsonVO::createShared();
	auto failDTO = LogOperationResultDTO::createShared();
	failDTO->operationTime = String(SimpleDateTimeFormat::format());
	failDTO->clearedCount = String("0");
	try
	{
		//校验 confirm 必需参数
		if (confirm != "true") {  // 确保 confirm 为 true
			vo->fail(failDTO);
			return vo;
		}
		//管理员权限控制
		bool isAdmin = false;
		/*std::cout << payload.getUsername() << std::endl;*/
		const std::list<std::string>& authorities = payload.getAuthorities();
		// 遍历权限列表，检查是否存在管理员权限
		for (const auto& auth : authorities) {
			if (auth == "SUPER_ADMIN")
			{
				isAdmin = true;
				break;
			}
		}
		if (!isAdmin) {
			vo->fail(failDTO);
			return vo;
		}
		//执行
		LogOperationService service;
		auto result = service.deleteAll();
		////检验
		if (result->clearedCount != "-1" && result->clearedCount)
		{
			vo->success(result);
		}
		else {
			vo->fail(result);
		}
	}
	catch (const std::exception& e) {
		std::cerr << "[execClear异常]：" << e.what() << std::endl; // 后端日志输出
		vo->fail(failDTO);
	}
	catch (...) {
		std::cerr << "[execClear未知异常]" << std::endl;
		vo->fail(failDTO);
	}
	//响应结果
	return vo;
}
