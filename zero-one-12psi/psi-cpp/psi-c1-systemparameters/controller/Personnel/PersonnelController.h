#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/10/13 21:38:24

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
#ifndef _PERSONNELCONTROLLER_H_
#define _PERSONNELCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"

#include "domain/dto/Personnel/PersonnelDTO.h"
#include "domain/vo/Personnel/PersonnelVO.h"
#include"domain/query/Personnel/PersonnelQuery.h"


#include OATPP_CODEGEN_BEGIN(ApiController)



#define API_TAG ZH_WORDS_GETTER("per.tag") // "人员管理"


class PersonnelController : public oatpp::web::server::api::ApiController
{
    // 定义控制器访问入口
    API_ACCESS_DECLARE(PersonnelController);
public:
    // 添加人员接口描述
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("per.add-per.summary"), addPersonnel, PersonnelJsonVO::Wrapper, API_TAG);
    // 添加人员接口端点
    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/personnel/add", addPersonnel, BODY_DTO(PersonnelAddDTO::Wrapper, dto), executeAddPersonnel(dto));

    // 修改人员接口描述
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("per.mod-per.summary"), modPersonnel, PersonnelJsonVO::Wrapper, API_TAG);

    // 修改人员接口端点（支持批量）
    API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/personnel/modify-per", modPersonnel,
        BODY_DTO(oatpp::List<PersonnelEditDTO::Wrapper>, dtoList),
        executeModPersonnel(dtoList));


    // 查询所有人员接口描述
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("per.query-all.summary"), queryAllCus, PersonnelQuery, PersonnelListPageJsonVO::Wrapper, API_TAG);
    // 查询所有人员接口端点
    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/personnel/query-by-list", queryAllCus, PersonnelQuery, executeQueryAll(query));


    // 获取人员详细信息接口描述
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("per.query-one.summary"), queryOnePer, PersonnelDetailJsonVO::Wrapper, API_TAG,
        API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("per.field.id"), "ae65c714d48d4f34b52479f5482c0edd", true);
    );
    // 获取客户详细信息接口端点
    API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/personnel/detail", queryOnePer, QUERY(String, id), executeQueryOne(id));

    // 定义删除指定人员（支持批量）接口描述
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("personnel.delete.summary"), removePeople, PersonnelDeleteJsonVO::Wrapper, API_TAG);
    // 定义删除指定人员（支持批量）接口处理
    API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/personnel/delete", removePeople, QUERY(String, ids,"ids"), execRemovePeople(ids));

    // 定义导出数据接口描述
    ENDPOINT_INFO(exportPeople) {
        API_DEF_ADD_TITLE(ZH_WORDS_GETTER("personnel.export.summary"));
        API_DEF_ADD_AUTH();
        API_DEF_ADD_TAG(API_TAG);
        API_DEF_ADD_RSP_JSON(Void);
    }
    // 定义导出数据接口处理
    ENDPOINT(API_M_POST, "/personnel/export", exportPeople, BODY_DTO(PersonnelExportReqDTO::Wrapper, req), API_HANDLER_AUTH_PARAME) {
        return execExportPeople(req->ids);
    }

    // 定义导入数据接口描述
    API_DEF_ENDPOINT_INFO_FILE_AUTH(ZH_WORDS_GETTER("personnel.import.summary"), importPeople, PersonnelExeclAddDTO::Wrapper, PersonnelImportJsonVO::Wrapper, API_TAG);
    // 定义导入数据处理端点
    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/personnel/import", importPeople, REQUEST(std::shared_ptr<IncomingRequest>, request), execImportPeople(request));

private:
    // 定义批量删除接口执行函数
    PersonnelDeleteJsonVO::Wrapper execRemovePeople(const String& ids);
    // 导出数据
    std::shared_ptr<OutgoingResponse> execExportPeople(const List<String>& ids);
    // 导入数据
    PersonnelImportJsonVO::Wrapper execImportPeople(std::shared_ptr<IncomingRequest> request);


    // 执行添加人员操作
    PersonnelJsonVO::Wrapper executeAddPersonnel(const PersonnelAddDTO::Wrapper& dto);
    // 执行修改人员操作
    PersonnelJsonVO::Wrapper executeModPersonnel(const PersonnelEditDTO::Wrapper& dto);
    // 执行修改人员操作（支持批量）
    PersonnelJsonVO::Wrapper executeModPersonnel(const oatpp::List<PersonnelEditDTO::Wrapper>& dtoList);

    // 查询所有人员
    PersonnelListPageJsonVO::Wrapper executeQueryAll(const PersonnelQuery::Wrapper& query);
    // 获取人员详细信息
    PersonnelDetailJsonVO::Wrapper executeQueryOne(const String& id);

};


#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)

#endif // !_PERSONNELCONTROLLER_H_