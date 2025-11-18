
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
#ifndef _SYSTEMVO_H_
#define _SYSTEMVO_H_

#include "../../GlobalInclude.h"

#include "domain/dto/System/SystemDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)


#ifdef LINUX
#define RS_IDNOTFOUND ResultStatus("no Id expired", 5444)
#define RS_IDEXCEED ResultStatus(u8"Id过长", 5443)
#define RS_INFOEXCEED ResultStatus(u8"Info过长", 5442)
#define RS_NAMEEXCEED ResultStatus(u8"Name过长", 5441)
#define RS_DATAEXCEED ResultStatus(u8"Data过长", 5440)
#define RS_NAMENOTFOUND ResultStatus(u8"缺少Name", 5439)
#define RS_INFONOTFOUND ResultStatus(u8"缺少Info", 5438)
#define RS_SYSTEMNAMENOTFOUND ResultStatus(u8"系统名称不能为空", 5437)
#define RS_COMPANYNAMENOTFOUND ResultStatus(u8"公司名称不能为空", 5436)
#define RS_IDISERROR ResultStatus(u8"传入数据的id有误", 5435)
#define RS_LACKOF ResultStatus(u8"缺少关键字段", 5434)
#define RS_UNKNOWNERROR ResultStatus(u8"未知错误", -1)
#define RS_SQLERROR ResultStatus(u8"SQL语句执行时出现错误", -2)
#else
#define RS_IDNOTFOUND ResultStatus(u8"缺少Id", 5444)
#define RS_IDEXCEED ResultStatus(u8"Id过长", 5443)
#define RS_INFOEXCEED ResultStatus(u8"Info过长", 5442)
#define RS_NAMEEXCEED ResultStatus(u8"Name过长", 5441)
#define RS_DATAEXCEED ResultStatus(u8"Data过长", 5440)
#define RS_NAMENOTFOUND ResultStatus(u8"缺少Name", 5439)
#define RS_INFONOTFOUND ResultStatus(u8"缺少Info", 5438)
#define RS_SYSTEMNAMENOTFOUND ResultStatus(u8"系统名称不能为空", 5437)
#define RS_COMPANYNAMENOTFOUND ResultStatus(u8"公司名称不能为空", 5436)
#define RS_IDISERROR ResultStatus(u8"传入数据的id有误", 5435)
#define RS_LACKOF ResultStatus(u8"缺少关键字段", 5434)
#define RS_UNKNOWNERROR ResultStatus(u8"未知错误", -1)
#define RS_SQLERROR ResultStatus(u8"SQL语句执行时出现错误", -2)
#endif



// 查询时的模型
class SystemJsonVO : public JsonVO<oatpp::Vector<oatpp::Object<SystemDTO>>> {
    DTO_INIT(SystemJsonVO, JsonVO<oatpp::Vector<oatpp::Object<SystemDTO>>>);
    
};

// 定义更加方便我返回消息的模型的前置模型
template<class T>
class SystemRespVO : public JsonVO<T> {
    // 初始化定义
    DTO_INIT(SystemRespVO, JsonVO<T>);

public:
    // 构建缺少id的消息
    void NoId(T data) {
        this->setStatus(RS_IDNOTFOUND);
        this->data = data;
    }
    // 构建缺少info的消息
    void NoInfo(T data) {
        this->setStatus(RS_INFONOTFOUND);
        this->data = data;
    }
    // 构建缺少name的消息
    void NoName(T data) {
        this->setStatus(RS_NAMENOTFOUND);
        this->data = data;
    }
    // 构建id过长的消息
    void ExceedId(T data) {
        this->setStatus(RS_IDEXCEED);
        this->data = data;
    }
    // 构建info过长的消息
    void ExceedInfo(T data) {
        this->setStatus(RS_INFOEXCEED);
        this->data = data;
    }
    // 构建name过长的消息
    void ExceedName(T data) {
        this->setStatus(RS_NAMEEXCEED);
        this->data = data;
    }
    // 构建data过长的消息
    void ExceedData(T data) {
        this->setStatus(RS_DATAEXCEED);
        this->data = data;
    }
    // 构建未知错误的消息
    void unknownError(T data) {
        this->setStatus(RS_UNKNOWNERROR);
        this->data = data;
    }
    // 构建系统名称不能为空的消息
    void unknownSystemName(T data) {
        this->setStatus(RS_SYSTEMNAMENOTFOUND);
        this->data = data;
    }
    // 构建修改的id找不到的消息
    void unknownId(T data) {
        this->setStatus(RS_IDISERROR);
        this->data = data;
    }
    // 构建公司名称不能为空的消息
    void unknownCompanyName(T data) {
        this->setStatus(RS_COMPANYNAMENOTFOUND);
        this->data = data;
    }
    // 构建缺少关键字段的消息
    void lackof(T data) {
        this->setStatus(RS_LACKOF);
        this->data = data;
    }
    // 构建SQL语句执行时出现错误的消息
    void sqlError(T data) {
        this->setStatus(RS_SQLERROR);
        this->data = data;
    }
};

// 定义更加方便我返回消息的模型
class SystemRespJsonVO : public SystemRespVO<Int32> {
    DTO_INIT(SystemRespJsonVO, SystemRespVO<Int32>);
};
 

#include OATPP_CODEGEN_END(DTO)

#endif // !_SYSTEMVO_H_