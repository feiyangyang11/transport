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
#ifndef _RECEIPTVO_H
#define _RECEIPTVO_H

#include "../../GlobalInclude.h"
#include"../../dto/Receipt/ReceiptDTO.h"


#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 单据查询显示JsonVO，用于响应给客户端的Json对象
 */
class ReceiptgetJsonVO : public JsonVO<ReceiptgetDTO::Wrapper> {
    DTO_INIT(ReceiptgetJsonVO, JsonVO<ReceiptgetDTO::Wrapper>);
};

/**
 * 单据查询分页显示JsonVO，用于响应给客户端的Json对象
 */
class ReceiptPageJsonVO : public JsonVO<ReceiptPageDTO::Wrapper>
{
    DTO_INIT(ReceiptPageJsonVO, JsonVO<ReceiptPageDTO::Wrapper>);

};


#include OATPP_CODEGEN_END(DTO)

#endif // !_SAMPLECONTROLLER_H_