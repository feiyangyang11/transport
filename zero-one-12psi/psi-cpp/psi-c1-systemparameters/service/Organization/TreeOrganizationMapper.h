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
#ifndef _TREEORGANIZATIONMAPPER_H_
#define _TREEORGANIZATIONMAPPER_H_

#include "tree/TreeNodeMapper.h"
#include "../../domain/do/Organization/OrganizationDO.h"
#include "../../domain/dto/Organization/OrganizationDTO.h"

class TreeOrganizationMapper : public TreeNodeMapper<PtrOrganizationDO>
{
public:
	shared_ptr<TreeNode> objectMapper(PtrOrganizationDO source) const override
	{
		// 创建结果数据对象
		auto res = make_shared<OrganizationListDTO>();
		// 计算层级结构属性映射
		res->_id(source->getId());
		res->_pid(source->getPid());
		// 扩展属性映射
		res->name = source->getName();
		res->sort = source->getSort();
		res->remark = source->getData();
		res->id = source->getId();
		return res;
	}
};

class TreeOrganizationMapper1 : public TreeNodeMapper<PtrOrganizationDO>
{
public:
	shared_ptr<TreeNode> objectMapper(PtrOrganizationDO source) const override
	{
		// 创建结果数据对象
		auto res = make_shared<OrganizationTreeDTO>();
		// 计算层级结构属性映射
		res->_id(source->getId());
		res->_pid(source->getPid());
		// 扩展属性映射
		res->name = source->getName();
		res->id = source->getId();
		return res;
	}
};

#endif // !_TREEORGANIZATIONMAPPER_H_