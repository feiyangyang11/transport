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
#ifndef _ORGANIZATIONCONTROLLER_H_
#define _ORGANIZATIONCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/Organization/OrganizationQuery.h"
#include "domain/vo/Organization/OrganizationVO.h"
#include "domain/dto/Organization/OrganizationDTO.h"
#include "domain/do/Organization/OrganizationDO.h"
#include "domain/vo/BaseJsonVO.h"


#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("organization.tag")



class OrganizationController : public oatpp::web::server::api::ApiController
{
    // ����������������
    API_ACCESS_DECLARE(OrganizationController);

public: //����ӿ�

    // ��ȡ��֯�б��ӿ�����
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("organization.query-all.summary"), queryAllorganization, OrganizationListJsonVO::Wrapper, API_TAG);
    // ��ȡ��֯�б��ӿڶ˵�
    API_HANDLER_ENDPOINT_NOPARAM_AUTH(API_M_GET, "/organization/query-by-list", queryAllorganization, executeQueryAll());

    // ��ȡ��֯��ϸ��Ϣ�ӿ����� 
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("organization.query-one.summary"), queryOneOrganization, OrganizationDetailJsonVO::Wrapper, API_TAG,
        API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("cus.field.id"), "ae65c714d48d4f34b52479f5482c0edd", true);
    );
    // ��ȡ��֯��ϸ��Ϣ�ӿڶ˵�
    API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/organization/detail", queryOneOrganization, QUERY(String, id), executeQueryOne(id));

    //��ȡ��֯�ṹ���ӿ�����
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("organization.query-tree.summary"), queryOrganizationTree, OrganizationTreeJsonVO::Wrapper, API_TAG);
    //��ȡ��֯�ṹ���ӿڶ˿�
    API_HANDLER_ENDPOINT_NOPARAM_AUTH(API_M_GET, "/organization/tree", queryOrganizationTree, executeQueryTree());

    //添加组织接口描述
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("org.add"), addOrganization, StringJsonVO::Wrapper, API_TAG, API_DEF_ADD_AUTH(););
    //添加组织接口定义
    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/organization/add", addOrganization, BODY_DTO(OrganizationAddDTO::Wrapper, dto), execAdd(dto));
    //修改组织接口描述
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("org.cha"), chaOrganization, StringJsonVO::Wrapper, API_TAG,
        API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("cus.field.id"), "", true);
    API_DEF_ADD_AUTH();
        );
    //修改组织接口定义
    ENDPOINT(API_M_PUT, "/organization/update", chaOrganization, QUERY(String, id), BODY_DTO(OrganizationUpdateDTO::Wrapper, dto), API_HANDLER_AUTH_PARAME) {
        API_HANDLER_RESP_VO(execcha(id, dto));
    }

    //删除组织接口描述
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("org.del"), delOrganization, BooleanJsonVO::Wrapper, API_TAG,
        API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("cus.field.id"), "", true);
    API_DEF_ADD_AUTH();
        );
    //删除组织接口定义
    API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/organization/delete", delOrganization, QUERY(String, id), execdel(id));

private: // ����ӿ�ִ�к���

    //添加组织
    StringJsonVO::Wrapper execAdd(const OrganizationAddDTO::Wrapper& dto);
    //修改组织
    StringJsonVO::Wrapper execcha(const String& id, const OrganizationUpdateDTO::Wrapper& dto);
    //删除组织
    BooleanJsonVO::Wrapper execdel(const String& id);

   // ��ȡ������֯
    OrganizationListJsonVO::Wrapper executeQueryAll();
    // ��ȡ��֯��ϸ��Ϣ
    OrganizationDetailJsonVO::Wrapper executeQueryOne(const String& id);
    //��ȡ��֯�ṹ��
    OrganizationTreeJsonVO::Wrapper executeQueryTree();

};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)

#endif // !_ORGANIZATIONCONTROLLER_H_