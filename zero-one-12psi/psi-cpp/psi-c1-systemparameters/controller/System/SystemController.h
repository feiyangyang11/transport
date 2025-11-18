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
#ifndef _SYSTEMCONTROLLER_H_
#define _SYSTEMCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"



#include "domain/query/System/SystemQuery.h"
#include "domain/vo/System/SystemVO.h"
#include "domain/dto/System/SystemDTO.h"
#include "service/System/SystemService.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("sys.tag")



class SystemController : public oatpp::web::server::api::ApiController
{
    // 定义控制器访问入口
    API_ACCESS_DECLARE(SystemController);
public:

    // 定义查询配置信息的接口描述
	ENDPOINT_INFO(queryAllSys) {
		// 定义接口标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("sys.query.getMsg"));
		// 定义默认授权参数（可选定义，如果定义了，下面ENDPOINT里面需要加入API_HANDLER_AUTH_PARAME）
		API_DEF_ADD_AUTH();
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(SystemJsonVO);
		API_DEF_ADD_TAG(API_TAG);
	}
	// 定义查询配置信息的接口
	ENDPOINT(API_M_GET, "/sys/get-msg", queryAllSys, API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeQueryAll());
	}



	// 定义保存配置信息的接口
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("sys.query.putMsg"), modifyAllSys, SystemRespJsonVO::Wrapper, API_TAG);
	// 定义保存配置信息的几口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/sys/put-msg", modifyAllSys, BODY_DTO(Vector<SystemDTO::Wrapper>, dto), executeModifyAll(dto));
    
private: // 定义接口执行函数


	SystemJsonVO::Wrapper executeQueryAll();
	SystemRespJsonVO::Wrapper executeModifyAll(const Vector<SystemDTO::Wrapper>& dto);
};



#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)

#endif // !_SYSTEMCONTROLLER_H_