#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/10/13 21:38:24

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0
	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _USERCONTROLLER_H_
#define _USERCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/query/user/UserQuery.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/User/UserVO.h"

using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER ("user.tag")

class UserController : public oatpp::web::server::api::ApiController
{
    // 定义控制器访问入口
    API_ACCESS_DECLARE(UserController);

public:
	// 定义新增用户接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("user.add-user.summary"), addUser, UserJsonVO::Wrapper, API_TAG, API_DEF_ADD_AUTH(););

	// 定义新增接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/user/add-user", addUser, BODY_DTO(UserAddDTO::Wrapper,dto), executeAddUser(dto));

	// 定义修改用户接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("user.mod-user.summary"), modUser, UserJsonVO::Wrapper, API_TAG,API_DEF_ADD_AUTH(););

	// 定义修改接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/user/mod-user", modUser, BODY_DTO(UserModDTO::Wrapper, dto), executeModUser(dto));

	//// 定义删除用户接口描述
	//API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("user.del-user.summary"), delUser, UserJsonVO::Wrapper, API_TAG, API_DEF_ADD_AUTH(););

	//// 定义删除接口端点
	//API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/user/del-user", delUser, QUERY(String, id), executeDelUser(id));
	// 接口描述（带查询参数声明）
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("user.del-user.summary"), delUser, UserJsonVO::Wrapper, API_TAG, API_DEF_ADD_AUTH();
	API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("user.field.id"), "ae65c714d48d4f34b52479f5482c0edd", true);
		);
	// 接口端点（QUERY 对应查询参数 URL）
	API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/user/del-user", delUser, QUERY(String, id), executeDelUser(id));

	// 定义查询所有用户信息接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("user.query-all.summary"), queryAllUser, UserQuery, UserPageJsonVO::Wrapper, API_TAG);

	// 定义查询所有用户信息接口端点
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/user/query-all", queryAllUser, UserQuery, executeQueryAll(query));

	// 定义获取用户详细信息接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("user.query-one.summary"), queryOneUser, UserDetailJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("user.field.id"), "ae65c714d48d4f34b52479f5482c0edd", true);
	);
	// 定义获取用户详细信息接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/user/query-one", queryOneUser, QUERY(String, id), executeQueryOne(id));

private: // 定义接口执行函数

	UserPageJsonVO::Wrapper executeQueryAll(const UserQuery::Wrapper& query);
	UserDetailJsonVO::Wrapper executeQueryOne(const String& id);

	UserJsonVO::Wrapper executeAddUser(const UserAddDTO::Wrapper& dto);
	UserJsonVO::Wrapper executeModUser(const UserModDTO::Wrapper& dto);
	UserJsonVO::Wrapper executeDelUser(const String& id);
};
	

#undef API_TAG




#include OATPP_CODEGEN_END(ApiController)

#endif // !_USERCONTROLLER_H_