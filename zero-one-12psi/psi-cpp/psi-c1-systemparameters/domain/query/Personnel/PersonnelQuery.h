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
#ifndef _PERSONNELQUERY_H_
#define _PERSONNELQUERY_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 人员分页查询对象
 */
class PersonnelQuery : public PageQuery
{
	DTO_INIT(PersonnelQuery, PageQuery);
	// id
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("per.field.id"));
	// 人员名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("per.field.name"));
	// 拼音信息
	API_DTO_FIELD_DEFAULT(String, py, ZH_WORDS_GETTER("per.field.py"));
	// 人员编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("per.field.number"));
	// 所属组织
	API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("per.field.frame"));
	// 人员性别
	API_DTO_FIELD_DEFAULT(String, sex, ZH_WORDS_GETTER("per.field.sex"));
	// 人员联系电话
	API_DTO_FIELD_DEFAULT(String, tel, ZH_WORDS_GETTER("per.field.tel"));
	// 人员联系地址
	API_DTO_FIELD_DEFAULT(String, add, ZH_WORDS_GETTER("per.field.add"));
	// 身份证号
	API_DTO_FIELD_DEFAULT(String, card, ZH_WORDS_GETTER("per.field.card"));
	// 备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("per.field.data"));

};

#include OATPP_CODEGEN_END(DTO)

#endif // !_GOODSQUERY_H_