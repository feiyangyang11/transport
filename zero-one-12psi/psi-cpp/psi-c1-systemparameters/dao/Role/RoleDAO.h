#pragma once
#pragma once

#ifndef _ROLE_DAO_
#define _ROLE_DAO_
#include "BaseDAO.h"
#include "../../domain/do/Role/RoleDO.h"
#include "../../domain/query/Role/RoleQuery.h"

/**
 * 角色表数据库操作实现
 */
class RoleDAO : public BaseDAO
{
private:
	//************************************
	// Method:      queryConditionBuilder
	// FullName:    SampleDAO::queryConditionBuilder
	// Access:      private 
	// Returns:     std::string 拼接查询 SQL 条件，不含 WHERE 关键字
	// Parameter:   const SampleQuery::Wrapper& query 查询参数对象
	// Parameter:   SqlParams& params 存储查询参数的条件集合
	// Description: 根据 RoleQuery 参数动态构建查询条件并返回
	//************************************
	inline std::string queryConditionBuilder(const RoleQuery::Wrapper& query, SqlParams& params);
public:
	// 统计记录总数
	uint64_t count(const RoleQuery::Wrapper& query);
	// 分页查询数据
	std::list<RoleDO> selectWithPage(const RoleQuery::Wrapper& query);
	// 通过名称查询数据
	std::list<RoleDO> selectByName(const string& name);
	// 通过 ID 查询数据
	PtrRoleDO selectById(std::string id);
	// 分页查询角色列表，支持名称和描述查询
	std::list<RoleDO> selectRole(const RoleQuery::Wrapper& query);
	// 根据 ID 查询角色详情
	PtrRoleDO selectByIdtwo(std::string id);
	// 根据 keyword 查询角色列表，10/25 伞一定不要删除
	std::list<RoleDO> selectByKeyword(const string& keyword);
	// 根据 mid 查询功能权限列表，10/31 伞一定不要删除
    std::list<PtrFunc_permDO> selectRoleFunctionPermissionsByMid(const string& mid);
	// 通过 pid 查询主模块、子模块列表，10/31 伞一定不要删除
	std::list<MenuDO> selectModuleListByPid(const string& pid);
	// 统计角色关联的用户数量
	uint64_t countUsersByRoleId(const std::string& roleId);
};
#endif // !_SAMPLE_DAO_
