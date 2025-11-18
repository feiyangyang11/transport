#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/10/18 19:34:41

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
#ifndef _PERSONNELVO_H_
#define _PERSONNELVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/Personnel/PersonnelDTO.h"
#include "../../dto/Personnel/PersonnelImportReportDTO.h"
#include "../../dto/Personnel/PersonnelDeleteDTO.h"
using namespace oatpp;
#include OATPP_CODEGEN_BEGIN(DTO)

class PersonnelJsonVO : public StringJsonVO
{
	DTO_INIT(PersonnelJsonVO, StringJsonVO);
	//状态码
	API_DTO_FIELD_DEFAULT(Int32, code, 1);
	//响应消息
	API_DTO_FIELD_DEFAULT(String, message, "");
	//响应数据（id）
	API_DTO_FIELD_DEFAULT(String, data, "");
};



/**
 * 人员列表分页显示JsonVO，用于响应给客户端的Json对象
 */
class PersonnelListPageJsonVO : public JsonVO<PersonnelListPageDTO::Wrapper> {
	DTO_INIT(PersonnelListPageJsonVO, JsonVO<PersonnelListPageDTO::Wrapper>);
};

/**
 * 人员详情显示JsonVO，用于响应给客户端的Json对象
 */
class PersonnelDetailJsonVO : public JsonVO<PersonnelDetailDTO::Wrapper> {
	DTO_INIT(PersonnelDetailJsonVO, JsonVO<PersonnelDetailDTO::Wrapper>);
};

/**
 * 导入人员数据结果显示JsonVO，用于响应给客户端的Json对象
 */
class PersonnelImportJsonVO : public JsonVO<PeopleImportReportDTO::Wrapper> {
	DTO_INIT(PersonnelImportJsonVO, JsonVO<PeopleImportReportDTO::Wrapper>);
};

/**
 * 批量删除人员数据结果显示JsonVO，用于响应给客户端的Json对象
 */
class PersonnelDeleteJsonVO : public JsonVO<PeopleDeleteReportDTO::Wrapper> {
	DTO_INIT(PersonnelDeleteJsonVO, JsonVO<PeopleDeleteReportDTO::Wrapper>);
};

//class PersonnelAddJsonVO : public StringJsonVO
//{
//	DTO_INIT(PersonnelAddJsonVO, StringJsonVO);
//
//};
//

//class PersonnelDelJsonVO : public PersonnelAddJsonVO
//{
//	DTO_INIT(PersonnelDelJsonVO, PersonnelAddJsonVO);
//};



#include OATPP_CODEGEN_END(DTO)
#endif // !_PERSONNELVO_H