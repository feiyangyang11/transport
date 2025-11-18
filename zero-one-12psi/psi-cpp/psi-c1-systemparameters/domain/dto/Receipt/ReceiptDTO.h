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
#ifndef _RECEIPTDTO_H
#define _RECEIPTDTO_H

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)
/**
* 单据查询数据传输模型
*/
class ReceiptgetDTO : public oatpp::DTO
{
    DTO_INIT(ReceiptgetDTO, DTO);
    
    //单据类型
    API_DTO_FIELD_DEFAULT(String, numberType, ZH_WORDS_GETTER("receipt.field.NumberType"));
   
    //单据编号
    API_DTO_FIELD_DEFAULT(Int32, number, ZH_WORDS_GETTER("receipt.field.number"));

    //单据创建时间
    API_DTO_FIELD_DEFAULT(String, create_time, ZH_WORDS_GETTER("receipt.field.Create_time"));
};

/**
* 单据查询分页数据传输模型
*/
class ReceiptPageDTO : public PageDTO<ReceiptgetDTO::Wrapper>
{
    DTO_INIT(ReceiptPageDTO, PageDTO<ReceiptgetDTO::Wrapper>);
};

/**
* 定义一个插入单据编号的数据传输模型
*/
class ReceiptAddNumberDTO : public oatpp::DTO
{
    DTO_INIT(ReceiptAddNumberDTO, DTO);
    // 单据类型(后期数据库生成单据编号传输给前端)
    API_DTO_FIELD_DEFAULT(String, NumberType, ZH_WORDS_GETTER("receipt.field.NumberType"));

};

#include OATPP_CODEGEN_END(DTO)

#endif // !_SAMPLECONTROLLER_H_