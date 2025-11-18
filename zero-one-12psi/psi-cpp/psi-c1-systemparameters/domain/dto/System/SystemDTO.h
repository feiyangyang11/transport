





























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
#ifndef _SYSTEMDTO_H_
#define _SYSTEMDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)




// 定义获取时的传输模型
class SystemDTO : public oatpp::DTO
{
    DTO_INIT(SystemDTO, DTO);
    API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("sys.field.id"));
    API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("sys.field.name"));
    API_DTO_FIELD_DEFAULT(String, info, ZH_WORDS_GETTER("sys.field.info"));
    API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("sys.field.data"));

};





#include OATPP_CODEGEN_END(DTO)

#endif // !_SYSTEMDTO_H_
