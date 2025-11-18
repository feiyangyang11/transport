#pragma once
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
#ifndef _RECEIPTCONTROLLER_H_
#define _RECEIPTCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/Receipt/ReceiptDTO.h"
#include "domain/vo/Receipt/ReceiptVO.h"
#include "domain/query/Receipt/ReceiptQuery.h"
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("receipt.tag")
class ReceiptController : public oatpp::web::server::api::ApiController
{
    // 定义控制器访问入口
    API_ACCESS_DECLARE(ReceiptController);
public://定义接口
    // 定义查询所有单据信息接口描述
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("receipt.query-all.summary"), queryAllDocument, ReceiptQuery, ReceiptPageJsonVO::Wrapper, API_TAG);
    // 查询所有单据信息，分页显示接口端点
    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/number-type/query-all", queryAllDocument, ReceiptQuery, executeQueryAll(query));

    //定义新增单据编号接口描述
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("receipt.add-number.summary"), AddReceiptNumber, ReceiptgetJsonVO::Wrapper, API_TAG);
    //新增单据编号接口端点
    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/number-type/get-number", AddReceiptNumber, BODY_DTO(ReceiptAddNumberDTO::Wrapper, dto), executeAddNumber(dto));

    //定义删除单据编号接口描述
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("receipt.delete-number.summary"), RemoveReceiptNumber, StringJsonVO::Wrapper, API_TAG);
    //删除单据编号接口端点
    API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/number-type/remove-number",RemoveReceiptNumber, BODY_DTO(ReceiptgetDTO::Wrapper, dto), execRemove(dto));

private: // 定义接口执行函数
    //查询所有单据信息
    ReceiptPageJsonVO::Wrapper executeQueryAll(const ReceiptQuery::Wrapper& receiptQuery);

    //新增单据编号
    ReceiptgetJsonVO::Wrapper executeAddNumber(const ReceiptAddNumberDTO::Wrapper& dto);

    //删除单据编号
    StringJsonVO::Wrapper execRemove(const ReceiptgetDTO::Wrapper &dto);
};
#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_RECEIPTCONTROLLER_H_