
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
#ifndef _ORGANIZATIONDO_H_
#define _ORGANIZATIONDO_H_

#include "../DoInclude.h"

/**
 * 人员管理文件存储数据模型
 */
class OrganizationDO : public BaseDO
{
	// 组织id唯一标识
	MYSQL_SYNTHESIZE(string, id, Id);
	// 组织所属id
	MYSQL_SYNTHESIZE(string, pid, Pid);
	// 组织名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 组织排序
	MYSQL_SYNTHESIZE(int, sort, Sort);
	// 备注信息
	// MYSQL_SYNTHESIZE(string, data, Data);
	MYSQL_SYNTHESIZE(string, remark, Data);
public:
	OrganizationDO() : BaseDO("frame")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("pid", "s", pid);
		MYSQL_ADD_FIELD_NULLABLE("name", "s", name, false);
		MYSQL_ADD_FIELD("sort", "i", sort);
		MYSQL_ADD_FIELD("data", "s", remark);
	}
};

// 定义一个组织实体的智能指针
typedef std::shared_ptr<OrganizationDO> PtrOrganizationDO;

#endif // !_ORGANIZATIONDO_H_