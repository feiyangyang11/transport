#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/10/18 19:25:14

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
#ifndef _OrganizationDTO_H_
#define _OrganizationDTO_H_


#include "tree/TreeNode.h"
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 组织列表数据传输模型
 */
class OrganizationListDTO : public oatpp::DTO, public TreeNode
{
	DTO_INIT(OrganizationListDTO, DTO);
	//组织id
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("organization.field.id"));
	//组织名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("organization.field.name"));
	//组织排序
	API_DTO_FIELD_DEFAULT(Int64, sort, ZH_WORDS_GETTER("organization.field.sort"));
	//备注信息
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("organization.field.remark"));
	//子组织
	API_DTO_FIELD(List<OrganizationListDTO::Wrapper>, children, ZH_WORDS_GETTER("organization.field.children"), false, {});
public:
	void addChild(shared_ptr<TreeNode> child) override
	{
		children->push_back(Wrapper(dynamic_pointer_cast<OrganizationListDTO>(child), Wrapper::Class::getType()));
	}
};

/**
 * 组织结构树数据传输模型
 */
class OrganizationTreeDTO : public oatpp::DTO, public TreeNode
{
	DTO_INIT(OrganizationTreeDTO, DTO);
	//组织id
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("organization.field.id"));
	//组织名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("organization.field.name"));
	//子组织
	API_DTO_FIELD(List<OrganizationTreeDTO::Wrapper>, children, ZH_WORDS_GETTER("organization.field.children"), false, {});

public:
	void addChild(shared_ptr<TreeNode> child) override
	{
		children->push_back(Wrapper(dynamic_pointer_cast<OrganizationTreeDTO>(child), Wrapper::Class::getType()));
	}
};

//新增组织
class OrganizationAddDTO : public oatpp::DTO
{
	DTO_INIT(OrganizationAddDTO, DTO);
	//新添组织名称
	DTO_FIELD(String, name);
	//名称长度限制：2-50个字符
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("organization.field.name");
		info->required = true;
	};
	//新添组织排序
	DTO_FIELD(Int64, sort);
	//排序值范围限制：1-9999
	DTO_FIELD_INFO(sort) {
		info->description = ZH_WORDS_GETTER("organization.field.sort");
		info->required = true;
	};
	//新添组织备注信息
	DTO_FIELD(String, remark);
	//备注长度限制：不超过200个字符
	DTO_FIELD_INFO(remark) {
		info->description = ZH_WORDS_GETTER("organization.field.data");
	};
	//新添所属组织
	DTO_FIELD(String, pid);
	//PID格式验证：不能为空且必须是有效的ID格式
	DTO_FIELD_INFO(pid) {
		info->description = ZH_WORDS_GETTER("organization.field.pid");
		info->required = true;
	};
};

/*
* 组织更新数据传输模型（不包含id字段，id通过URL路径参数传递）
*/
class OrganizationUpdateDTO : public oatpp::DTO
{
	DTO_INIT(OrganizationUpdateDTO, DTO);
	//组织名称
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("organization.field.name");
		info->required = true;
	};
	//所属组织
	DTO_FIELD(String, pid);
	DTO_FIELD_INFO(pid) {
		info->description = ZH_WORDS_GETTER("organization.field.pid");
		info->required = true;
	};
	//组织排序
	DTO_FIELD(Int64, sort);
	DTO_FIELD_INFO(sort) {
		info->description = ZH_WORDS_GETTER("organization.field.sort");
		info->required = true;
	};
	//组织备注信息
	DTO_FIELD(String, remark);
	DTO_FIELD_INFO(remark) {
		info->description = ZH_WORDS_GETTER("organization.field.remark");
	};
};
/*
* 组织详情数据传输模型
*/
class OrganizationDetailDTO : public OrganizationTreeDTO
{
	DTO_INIT(OrganizationDetailDTO, OrganizationTreeDTO);
	//所属组织
	API_DTO_FIELD_DEFAULT(String, pid, ZH_WORDS_GETTER("organization.field.pid"));
	//组织排序
	API_DTO_FIELD_DEFAULT(Int64, sort, ZH_WORDS_GETTER("organization.field.sort"));
	//组织备注信息
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("organization.field.remark"));
	//组织列表
	API_DTO_FIELD(List<OrganizationTreeDTO::Wrapper>, children, ZH_WORDS_GETTER("organization.field.children"), false, {});
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_OrganizationDTO_H_