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
#ifndef _USERDETAILMAPPER_H_
#define _USERDETAILMAPPER_H_
#include "Mapper.h"
#include "domain/do/user/UserDO.h"
#include "domain/do/File/FileDO.h"
class UserDetailMapper : public Mapper<PtrUserDO>
{
public:
	PtrUserDO mapper(ResultSet* resultSet) const override
	{
		PtrUserDO userDO = std::make_shared<UserDO>();
		userDO->setId(resultSet->getString("id"));
		userDO->setName(resultSet->getString("name"));      // 用户名称         // 拼音信息
		userDO->setTel(resultSet->getString("tel"));        // 手机号码
		userDO->setFrame(resultSet->getString("frame"));    // 所属组织（默认'0'）
		userDO->setRole(resultSet->getString("role"));      // 所属角色
		userDO->setUser(resultSet->getString("user"));      // 登录账号
		userDO->setPwd(resultSet->getString("pwd"));        // 登录密码
		userDO->setData(resultSet->getString("data"));      // 备注信息
		userDO->setImg(resultSet->getString("img"));        // 头像关联annex.id
		// 头像文件信息
		if (!userDO->getImg().empty()) {
			PtrFileDO fd = std::make_shared<FileDO>();
			fd->setId(userDO->getImg());               // FileDO.id = annex.id（即user.img）
			fd->setName(resultSet->getString("avatar_name"));    // 附件文件名（annex.name的别名）
			fd->setSavePath(resultSet->getString("avatar_save_path"));  // 附件存储路径（annex.save_path的别名）
			userDO->setFile(fd);  // 将附件信息设置到UserDO
		}

		return userDO;
	}
};

#endif // !_USERDETAILMAPPER_H_