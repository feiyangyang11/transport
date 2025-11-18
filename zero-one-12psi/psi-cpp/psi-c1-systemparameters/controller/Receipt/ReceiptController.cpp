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
#include "ReceiptController.h"
#include"../../service/Receipt/ReceiptService.h"
#include"../../domain/vo/Receipt/ReceiptVO.h"
//查询单据信息
ReceiptPageJsonVO::Wrapper ReceiptController::executeQueryAll(const ReceiptQuery::Wrapper& receiptQuery)
{
	//创建Serverice对象，调用查询函数
	ReceiptService service;
	auto result = service.listAll(receiptQuery);
	//此时查询数据在serverice中，返回的是DTO对象
	//创建相应VO对象
	auto jvo = ReceiptPageJsonVO::createShared();
	
	jvo->success(result);
	
	
	return jvo;
}

ReceiptgetJsonVO::Wrapper ReceiptController::executeAddNumber(const ReceiptAddNumberDTO::Wrapper& dto)
{
	//创建service对象，调用插入函数
	ReceiptService service;

	//返回DTO类型数据
	auto result = service.addNumber(dto);

	//创建相对应的vo对象
	auto jvo = ReceiptgetJsonVO::createShared();
	
	jvo->success(result);

	//返回响应
	return jvo;
}

StringJsonVO::Wrapper ReceiptController::execRemove(const ReceiptgetDTO::Wrapper& dto)
{
	//创建service层对象，调用删除函数
	ReceiptService service;
	//返回对应数据
	auto result = service.removeNumber(dto);

	//创建相对应的vo对象
	auto jvo = StringJsonVO::createShared();

	if (result)
	{
		jvo->success("success");
	}
	else
	{
		jvo->success("fail");
	}


	return jvo;
}
