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
#ifndef _PERSONNELDO_H_
#define _PERSONNELDO_H_
#include "../DoInclude.h"

/**
 * 人员管理文件存储数据模型
 */
class PersonnelFileDO :public BaseDO
{
	// 人员id唯一标识
	MYSQL_SYNTHESIZE(string, id, Id);
	// 人员名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 人员拼音信息
	MYSQL_SYNTHESIZE(string, py, Py);
	// 人员编号
	MYSQL_SYNTHESIZE(string, number, Number);
	// 人员所属组织
	MYSQL_SYNTHESIZE(string, frame, Frame);
	// 人员性别
	MYSQL_SYNTHESIZE(int8_t, sex, Sex);
	// 联系电话
	MYSQL_SYNTHESIZE(string, tel, Tel);
	// 联系地址
	MYSQL_SYNTHESIZE(string, add, Add);
	// 身份证号
	MYSQL_SYNTHESIZE(string, card, Card);
	// 备注信息
	MYSQL_SYNTHESIZE(string, data, Data);
	// 扩展信息
	MYSQL_SYNTHESIZE(string, more, More);
public:
	PersonnelFileDO() : BaseDO("people")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD_NULLABLE("name", "s", name, false);
		MYSQL_ADD_FIELD_NULLABLE("number", "s", number, false);
		MYSQL_ADD_FIELD_NULLABLE("frame", "s", frame, false);
		MYSQL_ADD_FIELD("py", "s", py);
		MYSQL_ADD_FIELD("sex", "i", sex);
		MYSQL_ADD_FIELD("tel", "s", tel);
		MYSQL_ADD_FIELD("add", "s", add);
		MYSQL_ADD_FIELD("card", "s", card);
		MYSQL_ADD_FIELD("data", "s", data);
		MYSQL_ADD_FIELD("more", "s", more);
	}
};

// 定义一个智能指针别名方便使用
typedef std::shared_ptr<PersonnelFileDO> PtrPersonnelFileDO;

#endif // !_PERSONNELDO_H_