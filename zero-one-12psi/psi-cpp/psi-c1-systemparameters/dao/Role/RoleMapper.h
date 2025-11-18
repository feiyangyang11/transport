#pragma once

#ifndef _ROLE_MAPPER_
#define _ROLE_MAPPER_

#include "Mapper.h"
#include "../../domain/do/Role/RoleDO.h"

/**
 * 角色表字段匹配映射器
 */
class RoleMapper : public Mapper<RoleDO>
{
public:
	RoleDO mapper(ResultSet* resultSet) const override
	{
		RoleDO data;
		data.setId(resultSet->getString(1));
		data.setName(resultSet->getString(2));
		data.setData(resultSet->getString(3));
		data.setRoot(resultSet->getString(4));
		data.setAuth(resultSet->getString(5));
		return data;
	}
};
/**
 *  角色表字段匹配映射器
 */
class PtrRoleMapper : public Mapper<PtrRoleDO>
{
public:
	PtrRoleDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<RoleDO>();
		data->setId(resultSet->getString(1));
		data->setName(resultSet->getString(2));
		data->setData(resultSet->getString(3));
		data->setRoot(resultSet->getString(4));
		data->setAuth(resultSet->getString(5)); 
		return data;
	}
};
/**
 * 简化版 mapper，仅映射 id, name, data（三列）
 * 用于只返回三列的分页/列表查询，避免列索引越界或多余读取
 */
class RoleSimpleMapper : public Mapper<RoleDO>
{
public:
	RoleDO mapper(ResultSet* resultSet) const override
	{
		RoleDO data;
		data.setId(resultSet->getString(1));
		data.setName(resultSet->getString(2));
		data.setData(resultSet->getString(3));
		// 对于简化查询，root/auth 置空
		data.setRoot(std::string());
		data.setAuth(std::string());
		return data;
	}
};

/**
 * 简化版 mapper 返回 shared_ptr<RoleDO>
 */
class PtrRoleSimpleMapper : public Mapper<PtrRoleDO>
{
public:
	PtrRoleDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<RoleDO>();
		data->setId(resultSet->getString(1));
		data->setName(resultSet->getString(2));
		data->setData(resultSet->getString(3));
		data->setRoot(std::string());
		data->setAuth(std::string());
		return data;
	}
};

/**10/31 伞一定不要删除
 * func_perm表字段匹配映射器
 */
class Func_permMapper : public Mapper<Func_permDO>
{
public:
	Func_permDO mapper(ResultSet* resultSet) const override
	{
		Func_permDO data;
		data.setId(resultSet->getString(1));
		data.setMid(resultSet->getString(2));
		data.setName(resultSet->getString(3));
		data.setUrl(resultSet->getString(4));
		data.setSort(resultSet->getString(5));
		data.setIs_enable(resultSet->getString(6));
		data.setRemark(resultSet->getString(7));
		return data;
	}
};

/**10/31 伞一定不要删除
 * func_perm表字段匹配映射器
 */
class PtrFunc_permMapper : public Mapper<PtrFunc_permDO>
{
public:
	PtrFunc_permDO mapper(ResultSet* resultSet) const override
	{
		PtrFunc_permDO data = std::make_shared<Func_permDO>();
		data->setId(resultSet->getString(1));
		data->setMid(resultSet->getString(2));
		data->setName(resultSet->getString(3));
		data->setUrl(resultSet->getString(4));
		data->setSort(resultSet->getString(5));
		data->setIs_enable(resultSet->getString(6));
		data->setRemark(resultSet->getString(7));
		return data;
	}
};

/**10/31 伞一定不要删除
 * menu表字段匹配映射器
 */
class MenuMapper : public Mapper<MenuDO>
{
public:
	MenuDO mapper(ResultSet* resultSet) const override
	{
		MenuDO data;
		data.setId(resultSet->getString(1));
		data.setPid(resultSet->getString(2));
		data.setName(resultSet->getString(3));
		data.setKey(resultSet->getString(4));
		data.setModel(resultSet->getString(5));
		data.setType(resultSet->getString(6));
		data.setResource(resultSet->getString(7));
		data.setSort(resultSet->getString(8));
		data.setIco(resultSet->getString(9));
		data.setRoot(resultSet->getString(10));
		data.setData(resultSet->getString(11));
		return data;
	}
};

#endif // !_SAMPLE_MAPPER_