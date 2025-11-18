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
#include "OrganizationService.h"
#include "tree/TreeUtil.h"
#include "../../dao/Organization/OrganizationDAO.h"
#include "TreeOrganizationMapper.h"
#include "id/UuidFacade.h"

oatpp::List<OrganizationListDTO::Wrapper> OrganizationService::listOrganization()
{
	// ��ȡ��֯����
	std::list<PtrOrganizationDO> listData = OrganizationDAO().selectAll();

	// ת��Ϊ���νṹ
	std::list<shared_ptr<TreeNode>> res = TreeUtil::listToTree<PtrOrganizationDO>(listData, TreeOrganizationMapper());

	// �����ڵ�洢���б���
	auto data = oatpp::List<OrganizationListDTO::Wrapper>::createShared();
	for (auto one : res)
	{
		data->push_back(OrganizationListDTO::Wrapper(dynamic_pointer_cast<OrganizationListDTO>(one), OrganizationListDTO::Wrapper::Class::getType()));
	}
	return data;
}

OrganizationDetailDTO::Wrapper OrganizationService::DatailOrganization(const oatpp::String& id)
{
	OrganizationDAO od;
	auto data = od.selectById(id.getValue(""));

	if (!data) return nullptr;

	auto dto = OrganizationDetailDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, data, id, Id, pid, Pid, name, Name, sort, Sort, remark, Data);

	// 获取所有组织数据
	std::list<PtrOrganizationDO> allOrgs = OrganizationDAO().selectAll();
	
	std::list<shared_ptr<TreeNode>> res = TreeUtil::listToTree<PtrOrganizationDO>(allOrgs, TreeOrganizationMapper1());
	
	for (auto one : res)
	{
		dto->children->push_back(OrganizationTreeDTO::Wrapper(dynamic_pointer_cast<OrganizationTreeDTO>(one), OrganizationTreeDTO::Wrapper::Class::getType()));
	}

	return dto;
}

oatpp::List<OrganizationTreeDTO::Wrapper> OrganizationService::treeOrganization()
{
	// ��ȡ��֯����
	std::list<PtrOrganizationDO> listData = OrganizationDAO().selectAll();

	// ת��Ϊ���νṹ
	std::list<shared_ptr<TreeNode>> res = TreeUtil::listToTree<PtrOrganizationDO>(listData, TreeOrganizationMapper1());

	// �����ڵ�洢���б���
	auto data = oatpp::List<OrganizationTreeDTO::Wrapper>::createShared();
	for (auto one : res)
	{
		data->push_back(OrganizationTreeDTO::Wrapper(dynamic_pointer_cast<OrganizationTreeDTO>(one), OrganizationTreeDTO::Wrapper::Class::getType()));
	}
	return data;
}

// 确保默认根组织存在的辅助方法
void ensureRootOrganizationExists() {
	OrganizationDAO dao;
	// 检查默认根组织是否存在
	auto rootOrg = dao.selectById(DEFAULT_ROOT_ORG_ID);
	if (!rootOrg) {
		// 如果不存在，创建默认根组织
		OrganizationDO rootDO;
		rootDO.setId(DEFAULT_ROOT_ORG_ID);
		rootDO.setPid(""); // 根组织没有父组织
		rootDO.setName("default_root_organization");
		rootDO.setSort(0);
		rootDO.setData("sys_default_root_organization");
		// 直接调用DAO方法插入，跳过验证（因为根组织是特殊的）
		try {
			char sqlBuffer[1024] = { 0 };
			string sqlTemplate = "INSERT INTO `frame` (`id`,`pid`,`name`,`sort`,`data`) VALUES('%s','%s','%s',%d,'%s')";
			snprintf(
				sqlBuffer,
				sizeof(sqlBuffer),
				sqlTemplate.c_str(),
				rootDO.getId().c_str(),
				rootDO.getPid().c_str(),
				rootDO.getName().c_str(),
				rootDO.getSort(),
				rootDO.getData().c_str()
			);
			SqlSession* session = dao.getSqlSession();
			session->executeUpdate(sqlBuffer);
		} catch (...) {
			// 创建失败时静默处理，后续操作会正常失败
		}
	}
}

std::string OrganizationService::saveOrganization(const OrganizationAddDTO::Wrapper& dto)
{
	// 确保默认根组织存在
	ensureRootOrganizationExists();
	
	// 业务逻辑验证：处理pid
	OrganizationDAO dao;
	std::string pid;
	
	if (dto->pid && !dto->pid->empty()) {
		// 用户提供了pid，验证父组织是否存在
		pid = dto->pid.getValue("");
		auto parentOrg = dao.selectById(pid);
		if (!parentOrg) {
			// 父组织不存在
			return ""; // 返回空表示验证失败
		}
	} else {
		// 用户未提供pid，使用默认根组织ID
		pid = DEFAULT_ROOT_ORG_ID;
	}

	// 生成唯一ID
	UuidFacade uf;
	auto id = uf.genUuid();

	// 数据传输与保存
	OrganizationDO odo;
	odo.setId(id);
	odo.setPid(pid); // 使用已确定的pid
	// 从DTO映射其他字段
	if (dto->name) odo.setName(dto->name.getValue(""));
	if (dto->sort) odo.setSort(dto->sort.getValue(0));
	if (dto->remark) odo.setData(dto->remark.getValue(""));
	
	if (dao.insertOrganization(odo)) return id;
	return "";
}
bool OrganizationService::updataOrganization(const OrganizationUpdateDTO::Wrapper& dto, const oatpp::String& id)
{
	// 字段验证
	// 验证组织名称
	if (!dto->name || dto->name->empty()) {
		return false; // 组织名称不能为空
	}

	// 验证排序值
	if (dto->sort && (dto->sort < 1 || dto->sort > 9999)) {
		return false; // 排序值必须在1-9999之间
	}

	// 确保默认根组织存在
	ensureRootOrganizationExists();

	// 业务逻辑验证：处理pid
	OrganizationDAO dao;
	std::string pid;
	
	if (dto->pid && !dto->pid->empty()) {
		// 用户提供了pid，验证父组织是否存在
		pid = dto->pid.getValue("");
		
		// 检查是否将组织设置为自己的父组织
		if (pid == id.getValue("")) {
			return false; // 不能将组织设置为自己的父组织
		}
		
		// 检查父组织是否存在
		auto parentOrg = dao.selectById(pid);
		if (!parentOrg) {
			// 父组织不存在
			return false; // 返回false表示验证失败
		}
		
		// 检查是否会形成循环引用（组织不能成为自己的祖先）
		std::string currentId = pid;
		while (true) {
			auto org = dao.selectById(currentId);
			if (!org || org->getPid().empty()) {
				break; // 到达根组织，没有循环引用
			}
			if (org->getPid() == id.getValue("")) {
				return false; // 检测到循环引用
			}
			currentId = org->getPid();
		}
	} else {
		// 用户未提供pid，使用默认根组织ID
		pid = DEFAULT_ROOT_ORG_ID;
	}

	OrganizationDO data;
	// Set id field from URL parameter
	data.setId(id);
	// 使用已确定的pid
	data.setPid(pid);
	// 从DTO映射其他字段
	if (dto->name) data.setName(dto->name.getValue(""));
	if (dto->sort) data.setSort(dto->sort.getValue(0));
	if (dto->remark) data.setData(dto->remark.getValue(""));

	// Call the correct method name
	return dao.updataOrganization(data) == 1;
}
int OrganizationService::removeOrganization(const oatpp::String& id)
{
	OrganizationDAO dao;
	std::string orgId = id.getValue("");

	// 特殊检查：默认根组织不能删除
	if (orgId == DEFAULT_ROOT_ORG_ID) {
		return 4; // 默认根组织不能删除
	}

	// 检查组织是否存在
	PtrOrganizationDO organization = dao.selectById(orgId);
	if (!organization) {
		return 3; // 组织不存在
	}

	// 检查是否有子组织
	std::list<PtrOrganizationDO> allOrgs = dao.selectAll();
	for (const auto& org : allOrgs) {
		if (org->getPid() == orgId) {
			return 2; // 存在子组织
		}
	}

	// 执行删除操作
	int rows = dao.removeOrganization(orgId);
	if (rows > 0) {
		return 1; // 删除成功
	}

	return 0; // 删除失败
}

bool OrganizationService::removeOrganization(const oatpp::List<oatpp::String>& ids)
{
	// 保留原方法以保持兼容性，但在内部使用新的单ID删除逻辑
	// 注意：批量删除时，如果有任何一个组织存在子组织或不存在，整个操作将失败
	for (auto one : *ids.get()) {
		int result = removeOrganization(one);
		if (result != 1) {
			return false; // 任何一个删除失败，整个批量操作失败
		}
	}
	return true;
}