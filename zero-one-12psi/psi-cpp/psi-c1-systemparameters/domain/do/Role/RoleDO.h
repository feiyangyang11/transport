#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/12 19:47:24

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
# ifndef _ROLEDO_H_
# define _ROLEDO_H_
# include "../DoInclude.h"
/**
 * 系统角色数据对象（DO）
 */
class RoleDO :public BaseDO
{

	// 角色 id 唯一标识
	MYSQL_SYNTHESIZE(string, id, Id);
	// 角色名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 角色备注
	MYSQL_SYNTHESIZE(string, data_, Data);
	// 角色是否有根权限
	MYSQL_SYNTHESIZE(string, root, Root);
	// 角色拥有的权限
	MYSQL_SYNTHESIZE(string, auth, Auth);
public:
	RoleDO() : BaseDO("role")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD_NULLABLE("name", "s", name, false);
		// MYSQL_ADD_FIELD("data", "s", data);
		MYSQL_ADD_FIELD("data", "s", data_);
		MYSQL_ADD_FIELD("root", "s", root);
		MYSQL_ADD_FIELD("auth", "s", auth);
	}
};
typedef std::shared_ptr<RoleDO> PtrRoleDO;

// func_perm表的DO，10/31 伞一定不要删除
class Func_permDO :public BaseDO
{
	// 权限id
	MYSQL_SYNTHESIZE(string, id, Id);
	// 所属菜单id
	MYSQL_SYNTHESIZE(string, mid, Mid);
	// 功能权限名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 访问地址
	MYSQL_SYNTHESIZE(string, url, Url);
	// 排序
	MYSQL_SYNTHESIZE(string, sort, Sort);
	// 是否启用 1表示启用 0表示禁用
	MYSQL_SYNTHESIZE(string, is_enable, Is_enable);
	// 备注
	MYSQL_SYNTHESIZE(string, remark, Remark);
public:
	Func_permDO() : BaseDO("func_perm")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("mid", "s", mid);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("url", "s", url);
        MYSQL_ADD_FIELD("sort", "s", sort);
        MYSQL_ADD_FIELD("is_enable", "s", is_enable);
        MYSQL_ADD_FIELD("remark", "s", remark);
    }
};
typedef std::shared_ptr<Func_permDO> PtrFunc_permDO;

// menu表的DO，10/31 伞一定不要删除
class MenuDO :public BaseDO
{ 
    // 菜单id
	MYSQL_SYNTHESIZE(string, id, Id);
	// 所属菜单id
	MYSQL_SYNTHESIZE(string, pid, Pid);
	// 菜单名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 菜单标识
	MYSQL_SYNTHESIZE(string, key, Key);
	// 菜单模式[0:标签模式|1:新页模式]
	MYSQL_SYNTHESIZE(string, model, Model);
	// 菜单类型[0:独立菜单|1:附属菜单]
	MYSQL_SYNTHESIZE(string, type, Type);
	// 菜单地址
	MYSQL_SYNTHESIZE(string, resource, Resource);
    // 菜单排序
	MYSQL_SYNTHESIZE(string, sort, Sort);
    // 菜单图标
	MYSQL_SYNTHESIZE(string, ico, Ico);
    // 权限标识
	MYSQL_SYNTHESIZE(string, root, Root);
    // 备注信息
	MYSQL_SYNTHESIZE(string, menu_data, Data);
public:
	MenuDO() : BaseDO("menu")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("pid", "s", pid);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("key", "s", key);
		MYSQL_ADD_FIELD("model", "s", model);
		MYSQL_ADD_FIELD("type", "s", type);
		MYSQL_ADD_FIELD("resource", "s", resource);
		MYSQL_ADD_FIELD("sort", "s", sort);
		MYSQL_ADD_FIELD("ico", "s", ico);
		MYSQL_ADD_FIELD("root", "s", root);
		MYSQL_ADD_FIELD("data", "s", menu_data);
	}
};
typedef std::shared_ptr<MenuDO> PtrMenuDO;
# endif // !_ROLEDO_H_
