

#pragma once
#ifndef _ROLEDTO_H_
#define _ROLEDTO_H_

#include"../../GlobalInclude.h"
#include"../../query/Role/RoleQuery.h"
#include <alibabacloud/core/Signer.h>
#include OATPP_CODEGEN_BEGIN(DTO)

// 定义一个添加角色信息的数据传输模型
class RoleAddDTO : public  oatpp::DTO
{
    DTO_INIT(RoleAddDTO, DTO);

    // 角色名称
    API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("role.field.name"), true);
    // 角色备注
    API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("role.field.data"));
    //角色功能权限
    API_DTO_FIELD_DEFAULT(String, root, ZH_WORDS_GETTER("role.field.root"));
    //角色数据权限
    API_DTO_FIELD_DEFAULT(String, auth, ZH_WORDS_GETTER("role.field.auth"));

    //关联一个PayloadDTO负载数据对象
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);

};

// 角色数据传输对象
class RoleListDTO : public RoleAddDTO {
    DTO_INIT(RoleListDTO, RoleAddDTO)
        // 角色ID
        API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("common.field.id"));

};
class RoleListItemDTO : public oatpp::DTO {
    DTO_INIT(RoleListItemDTO, DTO);
    API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("common.field.id"));
    API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("role.field.name"));
    API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("role.field.data"));
};

// 列表分页 DTO 改为基于 RoleListItemDTO
class RoleListPageDTO : public PageDTO<RoleListItemDTO::Wrapper>
{
    DTO_INIT(RoleListPageDTO, PageDTO<RoleListItemDTO::Wrapper>)
};

//角色详情
class RoleDetailDTO : public RoleAddDTO {
    DTO_INIT(RoleDetailDTO, RoleAddDTO)
        // 角色ID
    API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("common.field.id"));
};

// 权限树权限项节点的DTO，一定不要删除(10/29，伞)
class PermissionTreeItemsNodeDTO : public oatpp::DTO
{
    DTO_INIT(PermissionTreeItemsNodeDTO, DTO);
    // 权限ID
    API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("role.field.permission-item-field-id"));
    // 权限名称
    API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("role.field.permission-item-field-name"));
    // 权限是否禁用
    API_DTO_FIELD_DEFAULT(String, is_enable, ZH_WORDS_GETTER("role.field.permission-item-field-isenable"));
};

// 权限树子模块节点的DTO，一定不要删除(10/29，伞)
class PermissionTreeSubModuleNodeDTO : public oatpp::DTO
{
    DTO_INIT(PermissionTreeSubModuleNodeDTO, DTO);
    // 子模块ID
    API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("role.field.permission-submodule-field-id"));
    //// 子模块所属菜单ID
    //API_DTO_FIELD_DEFAULT(String, pid, ZH_WORDS_GETTER("role.field.permission-submodule-field-pid"));
    // 子模块名称
    API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("role.field.permission-submodule-field-name"));
    // 权限项列表
    API_DTO_FIELD_DEFAULT(List<PermissionTreeItemsNodeDTO::Wrapper>, children, ZH_WORDS_GETTER("role.field.permission-submodule-field-children"));
};

// 角色权限树模块节点的DTO，一定不要删除(10/29，伞)
class PermissionTreeMainModuleNodeDTO : public oatpp::DTO
{
    DTO_INIT(PermissionTreeMainModuleNodeDTO, DTO);
    // 主模块ID
    API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("role.field.permission-mainmodule-field-id"));
    //// 主模块所属菜单ID
    //API_DTO_FIELD_DEFAULT(String, pid, ZH_WORDS_GETTER("role.field.permission-mainmodule-field-pid"));
    // 主模块名称
    API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("role.field.permission-mainmodule-field-name"));
    // 子模块
    API_DTO_FIELD_DEFAULT(List<PermissionTreeSubModuleNodeDTO::Wrapper>, children, ZH_WORDS_GETTER("role.field.permission-mainmodule-field-children"));
public:
    PermissionTreeMainModuleNodeDTO() {}
};

// 角色功能权限数据的DTO，一定不要删除(10/31，伞)
class RoleFunctionPermissionseDTO : public oatpp::DTO
{
    DTO_INIT(RoleFunctionPermissionseDTO, DTO);
    // 功能权限列表
    API_DTO_FIELD_DEFAULT(List<PermissionTreeMainModuleNodeDTO::Wrapper>, functionPermissions, ZH_WORDS_GETTER("role.field.function-permissions"));
public:
    RoleFunctionPermissionseDTO()
    {
        
    }
};

/**一定不要删除(10/29，伞)
 * 获取角色功能权限数据传输模型
*/
class RoleFunctionPermissionsDTO : public oatpp::DTO
{
    DTO_INIT(RoleFunctionPermissionsDTO, DTO);
    // 功能权限的json格式字符串
    API_DTO_FIELD_DEFAULT(String, functionPermissions, ZH_WORDS_GETTER("role.field.fieldfunctionPermissions"));
};

/**伞 一定要保留这个
 * 获取角色名称列表（条件）节点的数据传输模型，返回时要用
 */
class RoleNameListNodeDTO : public oatpp::DTO
{
    DTO_INIT(RoleNameListNodeDTO, DTO);
    // 角色ID
    API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("role.field.id"));
    // 角色名称
    API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("role.field.name"));
};
/**伞 一定要保留这个
 * 获取角色名称列表（条件）的数据传输模型，返回时要用
 */
class RoleNameListDTO :public oatpp::DTO
{
    DTO_INIT(RoleNameListDTO, DTO)
    API_DTO_FIELD_DEFAULT(List<RoleNameListNodeDTO::Wrapper>, roleNameList, ZH_WORDS_GETTER("role.field.role-name-list"));
};

// 删除成功结果DTO
class DeleteResultDTO : public oatpp::DTO {
    DTO_INIT(DeleteResultDTO, DTO);

    // 删除的ID
    DTO_FIELD(String, deletedId, "deletedId") = nullptr;

    // 删除的名称
    DTO_FIELD(String, deletedName, "deletedName") = nullptr;

    //用户数量
    DTO_FIELD(UInt64, userCount, "userCount") = nullptr;
};
#include OATPP_CODEGEN_END(DTO)
#endif