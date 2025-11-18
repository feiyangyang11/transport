






















#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/12 19:41:36

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
#ifndef _USERDO_H_
#define _USERDO_H_

#include "../DoInclude.h"
#include "../File/FileDO.h"

/**
 * 测试用户数据实体
 */
class UserDO : public BaseDO
{
	// 用户ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 用户名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 拼音信息
	MYSQL_SYNTHESIZE(string, py, Py);
	// 手机号码
	MYSQL_SYNTHESIZE(string, tel, Tel);
	// 所属组织
	MYSQL_SYNTHESIZE(string, frame, Frame);
	// 所属角色
	MYSQL_SYNTHESIZE(string, role, Role);
	// 登陆账号
	MYSQL_SYNTHESIZE(string, user, User);
	// 登陆密码
	MYSQL_SYNTHESIZE(string, pwd, Pwd);
	// 用户头像
	MYSQL_SYNTHESIZE(string, img, Img);
	// 秘钥信息
	MYSQL_SYNTHESIZE(string, token, Token);
	// 秘钥时效
	MYSQL_SYNTHESIZE(int, expire, Expire);
	// 备注信息
	MYSQL_SYNTHESIZE(string, data, Data);
	// 扩展信息
	MYSQL_SYNTHESIZE(string, more, More);
	// 关联一个文件实体，存储头像文件信息
	CC_SYNTHESIZE(PtrFileDO, file, File);
public:
	UserDO() : BaseDO("user") 
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("py", "s", py);
		MYSQL_ADD_FIELD("tel", "s", tel);
		MYSQL_ADD_FIELD("frame", "s", frame);
		MYSQL_ADD_FIELD("role", "s", role);
		MYSQL_ADD_FIELD("user", "s", user);
		MYSQL_ADD_FIELD("pwd", "s", pwd);
		MYSQL_ADD_FIELD("img", "s", img);
		MYSQL_ADD_FIELD("token", "s", token);
		MYSQL_ADD_FIELD("expire", "i", expire);
		MYSQL_ADD_FIELD("data", "s", data);
		MYSQL_ADD_FIELD("more", "s", more);
	}
};

// 定义一个用户实体的智能指针
typedef std::shared_ptr<UserDO> PtrUserDO;

#endif // !_USERDO_H_
