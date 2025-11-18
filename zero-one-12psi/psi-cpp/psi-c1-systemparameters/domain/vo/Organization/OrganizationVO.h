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
#ifndef _ORGANIZATIONVO_H_
#define _ORGANIZATIONVO_H_

#include "../../GlobalInclude.h"
#include "domain/dto/Organization/OrganizationDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/*
* 组织详情显示Json,用于响应给客户端的Json对象
*/
class OrganizationDetailJsonVO : public JsonVO<OrganizationDetailDTO::Wrapper> {
    DTO_INIT(OrganizationDetailJsonVO, JsonVO<OrganizationDetailDTO::Wrapper>);
};


/**
 * 组织列表显示JsonVO，用于响应给客户端的Json对象
 */
class OrganizationListJsonVO : public JsonVO<List<Object<OrganizationListDTO>>> {
	DTO_INIT(OrganizationListJsonVO, JsonVO<List<Object<OrganizationListDTO>>>);

public:
	OrganizationListJsonVO() {
		this->data = {};
	}
};


/**
 * 组织结构树显示JsonVO，用于响应给客户端的Json对象
 */
class OrganizationTreeJsonVO : public JsonVO<List<Object<OrganizationTreeDTO>>> {
	DTO_INIT(OrganizationTreeJsonVO, JsonVO<List<Object<OrganizationTreeDTO>>>);

public:
	OrganizationTreeJsonVO() {
		this->data = {};
	}
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_ORGANIZATIONVO_H_