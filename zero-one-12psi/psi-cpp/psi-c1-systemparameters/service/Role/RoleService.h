#pragma once

#ifndef _ROLE_SERVICE_
#define _ROLE_SERVICE_
#include"domain/query/Role/RoleQuery.h"
#include"domain/vo/Role/RoleVO.h"
#include "domain/dto/Role/RoleDTO.h"
#include "dao/Role/RoleDAO.h"

/**
 * ?????????
 */
class RoleService
{
public:

	// ????????
	std::string saveData(const RoleAddDTO::Wrapper& dto);
	// ????????
	bool updateData(const RoleListDTO::Wrapper& dto);
	// ???? ID ???????
	bool removeData(const oatpp::List<oatpp::String>& ids);
	
	// 检查角色名称是否已存在
	bool isRoleNameExists(const oatpp::String& name);
	
	// 检查角色ID是否已存在
	bool isRoleIDExists(const oatpp::String& id);

	// ???????????????б????????????????????????
	RoleListPageDTO::Wrapper listByCondition(const RoleQuery::Wrapper& query);

	// ???? ID ??????????
	RoleDetailDTO::Wrapper getById(const oatpp::String& id);

	// ??????????????б?
	RoleNameListDTO::Wrapper getRoleListByKeyword(const oatpp::String& keyword);

	// 返回可用的权限，10/31 伞一定不要删除
	RoleFunctionPermissionseDTO::Wrapper getRoleFunctionPermissions();
	// 检查角色是否关联用户
	uint64_t checkRoleUserRelation(const oatpp::String& roleId);
private:
	RoleDAO roleDAO;

};

#endif // !_SAMPLE_SERVICE_

