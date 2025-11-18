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
#ifndef _PERSONNELIMPORTREPORTDTO_H_
#define _PERSONNELIMPORTREPORTDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 人员导入新增错误模型
class PeopleImportErrorDTO : public oatpp::DTO
{
	DTO_INIT(PeopleImportErrorDTO, DTO);
	// 错误行
	API_DTO_FIELD_DEFAULT(Int32, row, ZH_WORDS_GETTER("personnel.error.row"));
	// 错误参数
	API_DTO_FIELD_DEFAULT(String, field, ZH_WORDS_GETTER("personnel.error.field"));
	// 错误值
	API_DTO_FIELD_DEFAULT(String, value, ZH_WORDS_GETTER("personnel.error.value"));
	// 错误信息
	API_DTO_FIELD_DEFAULT(String, message, ZH_WORDS_GETTER("personnel.error.message"));
};

// 人员导入报告模型
class PeopleImportReportDTO : public oatpp::DTO
{
	DTO_INIT(PeopleImportReportDTO, DTO);
	// 导入条数
	API_DTO_FIELD_DEFAULT(Int32, total, ZH_WORDS_GETTER("personnel.report.total"));
	// 成功条数
	API_DTO_FIELD_DEFAULT(Int32, success, ZH_WORDS_GETTER("personnel.report.success"));
	// 失败条数
	API_DTO_FIELD_DEFAULT(Int32, failed, ZH_WORDS_GETTER("personnel.report.failed"));
	// 具体错误信息
	API_DTO_FIELD_DEFAULT(oatpp::List<PeopleImportErrorDTO::Wrapper>, errors, ZH_WORDS_GETTER("personnel.report.errors"));
};

#include OATPP_CODEGEN_END(DTO)

#endif // _PERSONNELIMPORTREPORTDTO_H_













