#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/19 15:17:39

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
#ifndef _USERMAPPER_H_
#define _USERMAPPER_H_
#include "Mapper.h"
#include "domain/do/user/UserDO.h"
#include "domain/do/File/FileDO.h"
class UserMapper : public Mapper<PtrUserDO>
{
public:
	PtrUserDO mapper(ResultSet* resultSet) const override
	{
		PtrUserDO userDO = std::make_shared<UserDO>();
		userDO->setName(resultSet->getString("name"));      // 用户名称
		userDO->setTel(resultSet->getString("tel"));        // 手机号码
		userDO->setFrame(resultSet->getString("frame"));    // 所属组织
		userDO->setRole(resultSet->getString("role"));      // 所属角色
		userDO->setUser(resultSet->getString("user"));      // 登录账号
		userDO->setData(resultSet->getString("data"));      // 备注信息
		userDO->setId(resultSet->getString("id"));      // 

		return userDO;
	}
};
class CommonUserMapper : public Mapper<PtrUserDO>
{
public:
	PtrUserDO mapper(ResultSet* resultSet) const override
	{
		PtrUserDO userDO = std::make_shared<UserDO>();
		userDO->setName(resultSet->getString("name"));    // 所属组织
		return userDO;
	}
};
class FrameOnlyUserMapper : public Mapper<PtrUserDO>
{
public:
	PtrUserDO mapper(ResultSet* resultSet) const override
	{
		PtrUserDO userDO = std::make_shared<UserDO>();
		userDO->setFrame(resultSet->getString("id"));    // 所属组织
		return userDO;
	}
};
class RoleOnlyUserMapper : public Mapper<PtrUserDO>
{
public:
	PtrUserDO mapper(ResultSet* resultSet) const override
	{
		PtrUserDO userDO = std::make_shared<UserDO>();
		userDO->setRole(resultSet->getString("id"));    // 角色
		return userDO;
	}
};


#endif // !_USERMAPPER_H_