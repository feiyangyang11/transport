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
#ifndef _ORGANIZATIONDAO_H_
#define _ORGANIZATIONDAO_H_
#include "BaseDAO.h"
#include "domain/do/Organization/OrganizationDO.h"
#include "domain/dto/Organization/OrganizationDTO.h"
#include "domain/query/Organization/OrganizationQuery.h"

/*
* 组织数据操作类
*/
class OrganizationDAO : public BaseDAO
{
public:
    //获取所有组织
    std::list<PtrOrganizationDO> selectAll();
    //获取组织详情
    PtrOrganizationDO selectById(const string& id);
    //获取子组织列表
    std::list<PtrOrganizationDO> selectChildren();
    //新增组织结构
    bool insertOrganization(const OrganizationDO& OrganizationDO);
    //修改组织结构
    int updataOrganization(const OrganizationDO& data);
    //删除组织结构
    int removeOrganization(const std::string& id);
};

#endif