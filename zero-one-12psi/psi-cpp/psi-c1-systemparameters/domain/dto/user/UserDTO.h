#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2023/10/13 21:38:24

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
#ifndef _USERDTO_H_
#define _USERDTO_H_

#include "../../GlobalInclude.h"
//用户增、删、改模型
#include OATPP_CODEGEN_BEGIN(DTO)
//新增用户
class UserAddDTO : public oatpp::DTO
{
	DTO_INIT(UserAddDTO, DTO);
	//客户ID
	//API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("user.field.id"));
	//用户名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("user.field.name"));
	//所属架构
	API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("user.field.frame"));
	//用户角色
	API_DTO_FIELD_DEFAULT(String, role, ZH_WORDS_GETTER("user.field.role"));
	//用户账号
	API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("user.field.user"));
	//手机号码
	API_DTO_FIELD_DEFAULT(String, tel, ZH_WORDS_GETTER("user.field.tel"));
	//用户密码
	API_DTO_FIELD_DEFAULT(String, pwd, ZH_WORDS_GETTER("user.field.pwd"));
	//用户头像
	API_DTO_FIELD_DEFAULT(String, img, ZH_WORDS_GETTER("user.field.img"));
	//备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("user.field.data"));
	//拼音信息
	API_DTO_FIELD_DEFAULT(String, py, ZH_WORDS_GETTER("user.field.py"));
	//扩展信息
	API_DTO_FIELD_DEFAULT(String, more, ZH_WORDS_GETTER("user.field.more"));

};
//修改用户
class UserModDTO : public UserAddDTO
{
	DTO_INIT(UserModDTO, UserAddDTO);
	//客户ID
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("user.field.id"));
};
//删除用户--略


class UserDTO :public oatpp::DTO
{
	DTO_INIT(UserDTO, DTO);
	// 用户ID
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("user.field.id"));
	//用户名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("user.field.name"));
	//所属组织
	API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("user.field.frame"));
	//用户角色
	API_DTO_FIELD_DEFAULT(String, role, ZH_WORDS_GETTER("user.field.role"));
	//用户账号
	API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("user.field.user"));
	//手机号码
	API_DTO_FIELD_DEFAULT(String, tel, ZH_WORDS_GETTER("user.field.tel"));
	//备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("user.field.data"));
};

/**
 * 定义一个用户信息分页传输对象
 */
class UserPageDTO : public PageDTO<UserDTO::Wrapper>
{
	DTO_INIT(UserPageDTO, PageDTO<UserDTO::Wrapper>);
};

/**
 * 定义一个用户详细信息数据传输模型
 */
class UserDetailDTO :public UserDTO
{
	DTO_INIT(UserDetailDTO, UserDTO);
	//用户密码
	API_DTO_FIELD_DEFAULT(String, pwd, ZH_WORDS_GETTER("user.field.pwd"));
	//用户头像
	API_DTO_FIELD_DEFAULT(String, img, ZH_WORDS_GETTER("user.field.img"));
	//用户头像地址
	API_DTO_FIELD_DEFAULT(String, imgUrl, ZH_WORDS_GETTER("user.field.imgUrl"));
};



#include OATPP_CODEGEN_END(DTO)

#endif // 
