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
#ifndef _RECEIPTQUERY_H_
#define _RECEIPTQUERY_H_

#include "../../GlobalInclude.h"
#include"../../../../lib-oatpp/include/domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)
//分页单据查询
class ReceiptQuery : public PageQuery
{
    DTO_INIT(ReceiptQuery, PageQuery);
    //单据类型查询条件
    API_DTO_FIELD_DEFAULT(String, NumberType, ZH_WORDS_GETTER("receipt.field.NumberType"));

};


#include OATPP_CODEGEN_END(DTO)

#endif // !_SAMPLECONTROLLER_H_