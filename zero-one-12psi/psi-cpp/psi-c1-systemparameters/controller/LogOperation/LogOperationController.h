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
#ifndef _LOGOPERATIONCONTROLLER_H_
#define _LOGOPERATIONCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "../../domain/dto/LogOperation/LogOperationDTO.h"
#include "../../domain/query/LogOperation/LogOperationQuery.h"
#include "../../domain/do/LogOperation/LogOperationDO.h"
#include "../../domain/vo/LogOperation/LogOperationVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG1 ZH_WORDS_GETTER("log.tag.t1")

class LogOperationController : public oatpp::web::server::api::ApiController
{
    // 定义控制器访问入口
    API_ACCESS_DECLARE(LogOperationController);
public:
    ENDPOINT_INFO(queryLog)
    {
        // 定义接口标题
        API_DEF_ADD_TITLE(ZH_WORDS_GETTER("log.get.summary"));
        // 定义默认授权参数（可选定义，如果定义了，下面ENDPOINT里面需要加入API_HANDLER_AUTH_PARAME）
        API_DEF_ADD_AUTH();
        // 定义响应参数格式
        API_DEF_ADD_RSP_JSON_WRAPPER(LogOperationPageJsonVO);
        // 定义标签
        API_DEF_ADD_TAG(API_TAG1);
        // 定义分页查询参数描述
        API_DEF_ADD_PAGE_PARAMS();
        // 定义其他查询参数描述
        API_DEF_ADD_QUERY_PARAMS(String, "user", ZH_WORDS_GETTER("log.field.user"), ZH_WORDS_GETTER("log.example.user"), false);
        API_DEF_ADD_QUERY_PARAMS(String, "info", ZH_WORDS_GETTER("log.field.info"), ZH_WORDS_GETTER("log.example.info"), false);
        API_DEF_ADD_QUERY_PARAMS(String, "begintime", ZH_WORDS_GETTER("log.field.begintime"), ZH_WORDS_GETTER("log.example.begintime"), false);
        API_DEF_ADD_QUERY_PARAMS(String, "endtime", ZH_WORDS_GETTER("log.field.endtime"), ZH_WORDS_GETTER("log.example.endtime"), false);
    }
    // 定义查询接口处理
    ENDPOINT(API_M_GET, "/log/query-log", queryLog, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME)
    {
        API_HANDLER_QUERY_PARAM(logQuery, LogOperationQuery, queryParams);
        API_HANDLER_RESP_VO(execQueryLog(logQuery));
    }

    ENDPOINT_INFO(addLog)
    {
        API_DEF_ADD_TITLE(ZH_WORDS_GETTER("log.post.summary"));
        API_DEF_ADD_AUTH();
        API_DEF_ADD_RSP_JSON_WRAPPER(LogOperationResponseJsonVO);
        API_DEF_ADD_TAG(API_TAG1);
    }
    // 定义新增接口处理
    ENDPOINT(API_M_POST, "/log/logs", addLog, BODY_DTO(LogOperationAddDTO::Wrapper, dto), API_HANDLER_AUTH_PARAME)
    {
        API_HANDLER_RESP_VO(execAddLog(dto, authObject->getPayload()));
    }

    ENDPOINT_INFO(deleteAllLogs)
    {
        API_DEF_ADD_TITLE(ZH_WORDS_GETTER("log.delete.summary"));
        API_DEF_ADD_AUTH();
        API_DEF_ADD_RSP_JSON_WRAPPER(LogOperationResultJsonVO);
        API_DEF_ADD_QUERY_PARAMS(String, "confirm", ZH_WORDS_GETTER("log.field.confirm"),
            ZH_WORDS_GETTER("log.example.confirm"), true);
        API_DEF_ADD_TAG(API_TAG1);
    }
    // 定义清空接口处理
    ENDPOINT(API_M_DEL, "/log/clear", deleteAllLogs, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME)
    {
        std::string confirm = queryParams.get("confirm").getValue("false");
        //std::string confirm = "";
        API_HANDLER_RESP_VO(execClear(authObject->getPayload(), confirm));
    }

private: // 定义接口执行函数
    //查询执行函数
    LogOperationPageJsonVO::Wrapper execQueryLog(const LogOperationQuery::Wrapper& query);
    //新增执行函数
    LogOperationResponseJsonVO::Wrapper execAddLog(const LogOperationAddDTO::Wrapper& dto, const PayloadDTO& payload);
    //清空执行函数
    LogOperationResultJsonVO::Wrapper execClear(const PayloadDTO& payload, const std::string& confirm);
};

#undef API_TAG1

#include OATPP_CODEGEN_END(ApiController)

#endif // !_LOGOPERATIONCONTROLLER_H_