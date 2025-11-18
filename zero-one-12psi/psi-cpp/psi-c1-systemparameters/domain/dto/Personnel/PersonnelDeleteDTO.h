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
#ifndef _PERSONNELDELETEDTO_H_
#define _PERSONNELDELETEDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 人员删除详情信息模型
class PeopleDeleteDetailDTO : public oatpp::DTO
{
	DTO_INIT(PeopleDeleteDetailDTO, DTO);
	// 删除人员id
	API_DTO_FIELD_DEFAULT(String, personId, ZH_WORDS_GETTER("personnel.delete.personId"));
	// 删除是否成功
	API_DTO_FIELD_DEFAULT(Boolean, success, ZH_WORDS_GETTER("personnel.delete.success"));
	// 删除信息
	API_DTO_FIELD_DEFAULT(String, message, ZH_WORDS_GETTER("personnel.delete.message"));
};

// 人员批量删除报告模型
class PeopleDeleteReportDTO : public oatpp::DTO
{
	DTO_INIT(PeopleDeleteReportDTO, DTO);
	// 删除条数
	API_DTO_FIELD_DEFAULT(Int32, total, ZH_WORDS_GETTER("personnel.delete.total"));
	// 删除成功条数
	API_DTO_FIELD_DEFAULT(Int32, succnt, ZH_WORDS_GETTER("personnel.delete.succnt"));
	// 删除失败条数
	API_DTO_FIELD_DEFAULT(Int32, failed, ZH_WORDS_GETTER("personnel.delete.failed"));
	// 具体删除信息
	API_DTO_FIELD_DEFAULT(oatpp::List<PeopleDeleteDetailDTO::Wrapper>, details, ZH_WORDS_GETTER("personnel.delete.details"));
};

#include OATPP_CODEGEN_END(DTO)

#endif // _PERSONNELDELETEDTO_H_













