#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/10/18 19:25:14

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
#ifndef _ORGANIZATIONSERVICE_H_
#define _ORGANIZATIONSERVICE_H_

#include "../../dao/Organization/OrganizationDAO.h"
#include "../../domain/dto/Organization/OrganizationDTO.h"

// 默认根组织ID常量
#define DEFAULT_ROOT_ORG_ID "root_organization_id"

/*
* ?????????
*/
class OrganizationService
{
public:
    //???????��?
    oatpp::List<OrganizationListDTO::Wrapper> listOrganization();
    //??????????
    OrganizationDetailDTO::Wrapper DatailOrganization(const oatpp::String &id);
    //??????????
    oatpp::List<OrganizationTreeDTO::Wrapper> treeOrganization();
    // ???????
    std::string saveOrganization(const OrganizationAddDTO::Wrapper& dto);
    // �޸���֯
    bool updataOrganization(const OrganizationUpdateDTO::Wrapper& dto, const oatpp::String& id);
    // ?????? - ����ֵ��1-ɾ���ɹ���2-��������֯��3-��֯�����ڣ�0-ɾ��ʧ��
    int removeOrganization(const oatpp::String& id);

    // ����ɾ����֯������ԭ�����Ա��ּ����ԣ�
    bool removeOrganization(const oatpp::List<oatpp::String>& ids);
};



#endif // !_ORGANIZATIONSERVICE_H_
