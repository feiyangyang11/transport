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
#ifndef _PERSONNELDTO_H_
#define _PERSONNELDTO_H_

#include "../../GlobalInclude.h"
// 人员增删模型
#include OATPP_CODEGEN_BEGIN(DTO)

// 人员新增数据传输模型
class PersonnelAddDTO : public oatpp::DTO
{
	DTO_INIT(PersonnelAddDTO, DTO);
	// 人员名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("per.field.name"));
	// 人员编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("per.field.number"));
	// 所属组织
	API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("per.field.frame"));
	// 人员性别
	API_DTO_FIELD_DEFAULT(String, sex, ZH_WORDS_GETTER("per.field.sex"));
	// 联系电话
	API_DTO_FIELD_DEFAULT(String, tel, ZH_WORDS_GETTER("per.field.tel"));
	// 联系地址
	API_DTO_FIELD_DEFAULT(String, add, ZH_WORDS_GETTER("per.field.add"));
	// 身份证号
	API_DTO_FIELD_DEFAULT(String, card, ZH_WORDS_GETTER("per.field.card"));
	// 备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("per.field.data"));
};

// 删除


/**
 * 人员列表数据传输模型
 */
class PersonnelListDTO : public oatpp::DTO
{
	DTO_INIT(PersonnelListDTO, DTO);
	// 人员id
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("per.field, id"));
	// 所属组织
	API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("per.field.frame"));
	// 人员名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("per.field.name"));
	// 拼音信息
	// API_DTO_FIELD_DEFAULT(String, py, ZH_WORDS_GETTER("per.field.py"));
	// 人员编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("per.field.number"));
	// 人员性别
	API_DTO_FIELD_DEFAULT(Int8, sex, ZH_WORDS_GETTER("per.field.sex"));
	// 人员联系电话
	API_DTO_FIELD_DEFAULT(String, tel, ZH_WORDS_GETTER("per.field.tel"));
	// 人员联系地址
	API_DTO_FIELD_DEFAULT(String, add, ZH_WORDS_GETTER("per.field.add"));
	// 身份证号
	API_DTO_FIELD_DEFAULT(String, card, ZH_WORDS_GETTER("per.field.card"));
	// 备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("per.field.data"));
};

/**
 * 人员列表分页数据传输模型
 */
class PersonnelListPageDTO : public PageDTO<PersonnelListDTO::Wrapper>
{
	DTO_INIT(PersonnelListPageDTO, PageDTO<PersonnelListDTO::Wrapper>);
};

/**
 * 人员详情数据传输模型
 */
class PersonnelDetailDTO : public PersonnelListDTO
{
	DTO_INIT(PersonnelDetailDTO, PersonnelListDTO);
	// 客户ID
	// API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("per.field.id"));
};



/**
 * 上传人员信息文件对象
 */
class PersonnelExeclAddDTO : public oatpp::DTO
{
	DTO_INIT(PersonnelExeclAddDTO, DTO);
	// 人员名称
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, file, ZH_WORDS_GETTER("personnel.file.name"), true);
};
/**
 * 文件导入时所用人员信息对象
 */
class PersonnelImportDTO : public oatpp::DTO
{
	DTO_INIT(PersonnelImportDTO, DTO);
	// 人员名称
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("personnel.field.name"), true);
	// 拼音信息
	API_DTO_FIELD_REQUIRE(String, py, ZH_WORDS_GETTER("personnel.field.py"), false);
	// 人员编号
	API_DTO_FIELD_REQUIRE(String, number, ZH_WORDS_GETTER("personnel.field.number"), true);
	// 所属组织
	API_DTO_FIELD_REQUIRE(String, frame, ZH_WORDS_GETTER("personnel.field.frame"), true);
	// 人员性别
	API_DTO_FIELD_REQUIRE(Int8, sex, ZH_WORDS_GETTER("personnel.field.sex"), false);
	// 联系电话
	API_DTO_FIELD_REQUIRE(String, tel, ZH_WORDS_GETTER("personnel.field.tel"), false);
	// 联系地址
	API_DTO_FIELD_REQUIRE(String, add, ZH_WORDS_GETTER("personnel.field.add"), false);
	// 身份证号
	API_DTO_FIELD_REQUIRE(String, card, ZH_WORDS_GETTER("personnel.field.card"), false);
	// 备注信息
	API_DTO_FIELD_REQUIRE(String, data, ZH_WORDS_GETTER("personnel.field.data"), false);
	// 扩展信息
	API_DTO_FIELD_REQUIRE(String, more, ZH_WORDS_GETTER("personnel.field.more"), false);
};

/**
 * 文件导出时所用人员信息对象
 */
class PersonnelExportDTO : public oatpp::DTO
{
	DTO_INIT(PersonnelExportDTO, DTO);
	// 人员名称
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("personnel.field.name"), true);
	// 人员编号
	API_DTO_FIELD_REQUIRE(String, number, ZH_WORDS_GETTER("personnel.field.number"), true);
	// 所属组织
	API_DTO_FIELD_REQUIRE(String, frame, ZH_WORDS_GETTER("personnel.field.frame"), true);
	// 人员性别
	API_DTO_FIELD_REQUIRE(Int8, sex, ZH_WORDS_GETTER("personnel.field.sex"), false);
	// 联系电话
	API_DTO_FIELD_REQUIRE(String, tel, ZH_WORDS_GETTER("personnel.field.tel"), false);
	// 联系地址
	API_DTO_FIELD_REQUIRE(String, add, ZH_WORDS_GETTER("personnel.field.add"), false);
	// 身份证号
	API_DTO_FIELD_REQUIRE(String, card, ZH_WORDS_GETTER("personnel.field.card"), false);
	// 备注信息
	API_DTO_FIELD_REQUIRE(String, data, ZH_WORDS_GETTER("personnel.field.data"), false);
};


// 人员修改数据传输模型
class PersonnelEditDTO : public oatpp::DTO
{
	DTO_INIT(PersonnelEditDTO, DTO);
	// 客户ID
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("per.field.id"));
	// 人员名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("per.field.name"));
	// 人员编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("per.field.number"));
	// 所属组织
	API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("per.field.frame"));
	// 人员性别
	API_DTO_FIELD_DEFAULT(String, sex, ZH_WORDS_GETTER("per.field.sex"));
	// 联系电话
	API_DTO_FIELD_DEFAULT(String, tel, ZH_WORDS_GETTER("per.field.tel"));
	// 联系地址
	API_DTO_FIELD_DEFAULT(String, add, ZH_WORDS_GETTER("per.field.add"));
	// 身份证号
	API_DTO_FIELD_DEFAULT(String, card, ZH_WORDS_GETTER("per.field.card"));
	// 备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("per.field.data"));
};

// 文件导出请求数据对象
class PersonnelExportReqDTO :public oatpp::DTO {
	DTO_INIT(PersonnelExportReqDTO, oatpp::DTO);
	//删除人员编号数组
	API_DTO_FIELD_REQUIRE(oatpp::List<oatpp::String>, ids, ZH_WORDS_GETTER("personnel.file.ids"),true);
};

#include OATPP_CODEGEN_END(DTO)

#endif // 













