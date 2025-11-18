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
#ifndef _ROLECONTROLLER_H_
#define _ROLECONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include"domain/query/Role/RoleQuery.h"
#include"domain/vo/Role/RoleVO.h"
#include "domain/dto/Role/RoleDTO.h"
using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("role.tag")

class RoleController : public oatpp::web::server::api::ApiController
{
    // 声明 API 访问器
    API_ACCESS_DECLARE(RoleController);
public:
    // 定义添加角色接口信息
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("role.add-role.summary"), addRole, StringJsonVO::Wrapper, API_TAG);
    // 实现添加角色接口处理
    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/role/add-role", addRole, BODY_DTO(RoleAddDTO::Wrapper, dto), executeAddRole(dto, authObject->getPayload()));

    // 定义删除角色接口信息
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("role.delete.summary"), removeRole, ListJsonVO<String>::Wrapper, API_TAG);
    // 实现删除角色接口处理
    API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/role/delete-role", removeRole, BODY_DTO(List<String>, ids), execRemoveRole(ids));

    // 定义修改角色接口信息
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("role.put.summary"), modifyRole, StringJsonVO::Wrapper, API_TAG);
    // 实现修改角色接口处理
    API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/role/modify-role", modifyRole, BODY_DTO(RoleListDTO::Wrapper, dto), execModifyRole(dto, authObject->getPayload()));
    
    // 定义查询所有角色接口信息
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("role.query-all.summary"), queryAllRole, RoleQuery, RoleListPageJsonVO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/role/query-all", queryAllRole, RoleQuery, executeQueryALL(query));
    // 定义查询单个角色接口信息
   // RoleController.h
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("role.query-detail.summary"),
        queryOneRole,
        RoleDetailJsonVO::Wrapper,
        API_TAG,
        API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("role.field.id"), "", true);
    );
    API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/role/detail", queryOneRole, QUERY(String, id), executeQueryDetail(id));

    // 定义获取角色列表接口信息
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("role.list.summary"), getRoleList, RoleListQuery, RoleNameListJsonVO::Wrapper, API_TAG);
    // 实现获取角色列表接口处理
    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/role/list", getRoleList, RoleListQuery, execGetRoleList(query));
    
    // 获取角色权限接口信息，一定不要删除 (10/29，伞)
    ENDPOINT_INFO(getRolePermission) {
        // 定义接口标题
        API_DEF_ADD_TITLE(ZH_WORDS_GETTER("role.permission.summary"));
        // 定义默认授权参数（可选定义，如果定义了，下面ENDPOINT里面需要加入API_HANDLER_AUTH_PARAME）
        API_DEF_ADD_AUTH();
        // 定义响应参数格式
        API_DEF_ADD_RSP_JSON_WRAPPER(RoleFunctionPermissionsJsonVO);
        API_DEF_ADD_TAG(API_TAG);
    }
    //API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("role.permission.summary"), getRolePermission, RoleFunctionPermissionsJsonVO::Wrapper, API_TAG,
    //    /*API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("role.field.id"), "", false);*/
    //);
    // 实现获取角色权限接口，一定不要删除 (10/29，伞)
    ENDPOINT(API_M_GET, "/role/permission", getRolePermission, API_HANDLER_AUTH_PARAME) {
        API_HANDLER_RESP_VO(execGetRolePermission());
    }
    //API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/role/permission", getRolePermission, QUERY(String, id), execGetRolePermission());
private: // 接口实现方法

    
    // 执行添加角色
    StringJsonVO::Wrapper executeAddRole(const RoleAddDTO::Wrapper& dto, const PayloadDTO& payload);

    // 执行删除角色
    ListJsonVO<DeleteResultDTO::Wrapper>::Wrapper execRemoveRole(const List<String>& ids);

    
    // 执行修改角色
    StringJsonVO::Wrapper execModifyRole(const RoleListDTO::Wrapper& dto, const PayloadDTO& payload);

    // 执行查询所有角色
    RoleListPageJsonVO::Wrapper executeQueryALL(const RoleQuery::Wrapper& query);
    // 执行查询单个角色详情
    RoleDetailJsonVO::Wrapper executeQueryDetail(const String& id);

    // 执行获取角色列表
    RoleNameListJsonVO::Wrapper execGetRoleList(const RoleListQuery::Wrapper& query);

    // 执行获取角色权限，一定不要删除(10/29，伞)
    RoleFunctionPermissionsJsonVO::Wrapper execGetRolePermission();
};
#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_ROLECONTROLLER_H_