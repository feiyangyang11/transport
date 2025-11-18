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

#include "stdafx.h"
#include "OrganizationMapper.h"
#include "OrganizationDAO.h"

std::list<PtrOrganizationDO> OrganizationDAO::selectAll()
{
    try
    {
        string sql = "select id,pid,name,sort,data from frame ORDER BY sort ASC;";
        return sqlSession->executeQuery<PtrOrganizationDO>(sql, OrgMapper());
    }
    catch (const std::exception& e)
    {
        std::string errMsg = "组织列表查询失败: " + std::string(e.what());
        throw std::runtime_error(errMsg);
    }
}

PtrOrganizationDO OrganizationDAO::selectById(const string& id) {
    try
    {
        string sql = "select id,pid,name,sort,data from frame where id=?;";
        return sqlSession->executeQueryOne<PtrOrganizationDO>(sql, OrgMapper(), "%s", id);
    }
    catch (const std::exception& e)
    {
        std::string errMsg = "组织详情查询失败: " + std::string(e.what());
        throw std::runtime_error(errMsg);
    }
}

bool OrganizationDAO::insertOrganization(const OrganizationDO& organizationDO)
{
    string id = organizationDO.getId();
    string remark = organizationDO.getData();
    int sort = organizationDO.getSort();
    string pid = organizationDO.getPid();
    string name = organizationDO.getName();

    // 检查必要字段，pid可以为空（用于第一个根组织）
    if (id.empty() || sort < 0 || name.empty())
    {
        return false;
    }

    char sqlBuffer[1024] = { 0 };
    string sqlTemplate = "INSERT INTO `frame` (`id`,`pid`,`name`,`sort`,`data`) VALUES('%s','%s','%s',%d,'%s')";
    snprintf(
        sqlBuffer,
        sizeof(sqlBuffer),
        sqlTemplate.c_str(),
        id.c_str(),
        pid.c_str(),
        name.c_str(),
        sort,
        remark.c_str()
    );

    SqlSession* session = getSqlSession();
    int affectedRows = session->executeUpdate(sqlBuffer);
    return affectedRows > 0;
}

int OrganizationDAO::updataOrganization(const OrganizationDO& organizationDO)
{
    // Check if id is empty
    string id = organizationDO.getId();
    if (id.empty())
    {
        std::cerr << "Organization ID cannot be empty." << std::endl;
        return 0;
    }

    try
    {
        // Get values from OrganizationDO
        string pid = organizationDO.getPid();
        string name = organizationDO.getName();
        int sort = organizationDO.getSort();
        string remark = organizationDO.getData();

        // Create update SQL statement
        char sqlBuffer[1024] = { 0 };
        string sqlTemplate = "UPDATE `frame` SET `pid`='%s', `name`='%s', `sort`=%d, `Data`='%s' WHERE `id`='%s'";

        snprintf(
            sqlBuffer,
            sizeof(sqlBuffer),
            sqlTemplate.c_str(),
            pid.c_str(),
            name.c_str(),
            sort,
            remark.c_str(),
            id.c_str()
        );

        // Execute update
        SqlSession* session = getSqlSession();
        int affectedRows = session->executeUpdate(sqlBuffer);

        // Log result
        if (affectedRows > 0)
        {
            std::cout << "Organization with ID " << id << " updated successfully." << std::endl;
        }
        else
        {
            std::cout << "No organization found with ID " << id << "." << std::endl;
        }

        return affectedRows;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error updating organization with ID " << id << ": " << e.what() << std::endl;
        return 0;
    }
}

int OrganizationDAO::removeOrganization(const std::string& id)
{
    if (id.empty())
    {
        std::cerr << "Organization ID cannot be empty." << std::endl;
        return 0;
    }

    try
    {
        char sqlBuffer[1024] = { 0 };
        string sqlTemplate = "DELETE FROM `frame` WHERE `id`='%s'";

        snprintf(
            sqlBuffer,
            sizeof(sqlBuffer),
            sqlTemplate.c_str(),
            id.c_str()
        );

        SqlSession* session = getSqlSession();
        int affectedRows = session->executeUpdate(sqlBuffer);

        return affectedRows;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error deleting organization with ID " << id << ": " << e.what() << std::endl;
        return 0;
    }
}