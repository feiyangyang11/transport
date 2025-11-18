

#pragma once
#ifndef _ROLEVO_H_
#define _ROLEVO_H_
#include"../../GlobalInclude.h"
#include"../../dto/Role/RoleDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

//角色列表分页数据json，用于接口返回值
class RoleListPageJsonVO : public JsonVO<RoleListPageDTO::Wrapper>
{
	DTO_INIT(RoleListPageJsonVO, JsonVO<RoleListPageDTO::Wrapper>)
};
//角色详情数据json，用于接口返回值
class RoleDetailJsonVO : public JsonVO<RoleDetailDTO::Wrapper>
{
	DTO_INIT(RoleDetailJsonVO, JsonVO<RoleDetailDTO::Wrapper>)
};

/*
//角色列表分页数据json，用于接口返回值
class RoleListPageJsonVO : public JsonVO<RoleListPageDTO::Wrapper>
{
	DTO_INIT(RoleListPageJsonVO, JsonVO<RoleListPageDTO::Wrapper>)
};
*/

class RoleListJsonVO : public oatpp::DTO
{
	DTO_INIT(RoleListJsonVO, DTO);

};

/**
 * 角色列表分页显示JsonVO，用于像一个给客户端的Json对象
*
class RoleListPageJsonVO : public JsonVO<RoleListPageDTO::Wrapper> {
	DTO_INIT(RoleListPageJsonVO, JsonVO<RoleListPageDTO::Wrapper>);
};
*/

/**
 * 功能权限数据显示JsonVO，用于像一个给客户端的Json对象，一定不要删除(10/29，伞)
*/
class RoleFunctionPermissionsJsonVO : public JsonVO<RoleFunctionPermissionseDTO::Wrapper> {
	DTO_INIT(RoleFunctionPermissionsJsonVO, JsonVO<RoleFunctionPermissionseDTO::Wrapper>);
};

/**
 * 角色名称列表分页数据json，用于接口返回值
 */
class RoleNameListJsonVO : public JsonVO<RoleNameListDTO::Wrapper>
{
	DTO_INIT(RoleNameListJsonVO, JsonVO<RoleNameListDTO::Wrapper>);

};


#include OATPP_CODEGEN_END(DTO)
#endif // !_ROLEVO



































