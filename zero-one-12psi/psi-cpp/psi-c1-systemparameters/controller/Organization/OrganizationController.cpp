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
#include "stdafx.h"
#include "OrganizationController.h"
#include "../../service/Organization/OrganizationService.h"
#include "domain/vo/BaseJsonVO.h"

// ��ѯ������֯
OrganizationListJsonVO::Wrapper OrganizationController::executeQueryAll()
{
	// ����һ��JsonVO����
	auto vo = OrganizationListJsonVO::createShared();
	// ������֯����
	OrganizationService ms;
	auto menu = ms.listOrganization();
	if (menu)
		vo->success(ms.listOrganization());
	else
		vo->fail({});
	// ��Ӧ���
	return vo;
}

// ��ȡ��֯��ϸ��Ϣ
OrganizationDetailJsonVO::Wrapper OrganizationController::executeQueryOne(const String& id)
{
	//����һ��JsonVO����
	auto vo = OrganizationDetailJsonVO::createShared();
	//������֯����
	OrganizationService ms;
	auto result = ms.DatailOrganization(id);
	if (result)
		vo->success(ms.DatailOrganization(id));
	else
		vo->fail({});

	return vo;
}

//��ȡ��֯�ṹ��
OrganizationTreeJsonVO::Wrapper OrganizationController::executeQueryTree()
{
	// ����һ��JsonVO����
	auto vo = OrganizationTreeJsonVO::createShared();
	// ������֯����
	OrganizationService ms;
	auto menu = ms.treeOrganization();
	if (menu)
		vo->success(ms.treeOrganization());
	else
		vo->fail({});
	// ��Ӧ���
	return vo;
}

StringJsonVO::Wrapper OrganizationController::execAdd(const OrganizationAddDTO::Wrapper& dto)
{
    // 创建响应对象
    auto jvo = StringJsonVO::createShared();

    // 调用服务层进行新增操作
    OrganizationService service;
    std::string id = service.saveOrganization(dto);

    // 根据结果返回不同的响应
    if (!id.empty()) {
        jvo->success(id);
    }
    else {
        // 返回更明确的错误信息
        jvo->init(nullptr, RS_PARAMS_INVALID);
    }

    return jvo;
}
StringJsonVO::Wrapper OrganizationController::execcha(const String& id, const OrganizationUpdateDTO::Wrapper& dto)
{
    // 创建响应对象
    auto jvo = StringJsonVO::createShared();

    if (id == nullptr || id->empty())
    {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        return jvo;
    }

    // 创建一个新的DTO副本，以便在必要时修改pid
    auto updatedDto = OrganizationUpdateDTO::createShared();
    updatedDto->name = dto->name;
    updatedDto->sort = dto->sort;
    updatedDto->remark = dto->remark;
    
    // 如果用户提供了pid，则使用用户提供的值；否则设为nullptr，由service层处理使用默认根组织ID
    if (dto->pid && !dto->pid->empty()) {
        updatedDto->pid = dto->pid;
    }

    OrganizationService service;

    if (service.updataOrganization(updatedDto, id)) {
        jvo->success(id);
    }
    else
    {
        jvo->init(nullptr, RS_FAIL);
    }

    return jvo;
}
BooleanJsonVO::Wrapper OrganizationController::execdel(const String& id)
{
    auto jvo = BooleanJsonVO::createShared();

    if (id->empty())
    {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        jvo->message = "Organization ID cannot be empty";
        return jvo;
    }

    OrganizationService service;

    try {
        int result = service.removeOrganization(id);
        if (result == 1) {
            jvo->init(true, RS_SUCCESS);
            jvo->message = "Delete successful";
        }
        else if (result == 2) {
            jvo->init(false, RS_FAIL);
            jvo->message = "Cannot delete because there are sub-organizations";
        }
        else if (result == 3) {
            jvo->init(false, RS_FAIL);
            jvo->message = "Organization does not exist";
        }
        else if (result == 4) {
            jvo->init(false, RS_FAIL);
            jvo->message = "Default root organization cannot be deleted";
        }
        else {
            jvo->init(false, RS_FAIL);
            jvo->message = "Delete failed";
        }
    }
    catch (const std::exception& e) {
        jvo->init(false, RS_SERVER_ERROR);
        jvo->message = "Delete failed: " + std::string(e.what());
    }
    // 返回结果
    return jvo;
}




