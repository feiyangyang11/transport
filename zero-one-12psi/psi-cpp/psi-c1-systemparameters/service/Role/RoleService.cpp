#include "stdafx.h"
#include "RoleService.h"
#include "../../dao/Role/RoleDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"
#include"../../domain/dto/Role/RoleDTO.h"
#include"../../domain/vo/Role/RoleVO.h"
#include "../../../lib-mysql/include/SqlSession.h"




// ????????
std::string RoleService::saveData(const RoleAddDTO::Wrapper& dto)
{
	//??? DO ????
	RoleDO data_;
	ZO_STAR_DOMAIN_DTO_TO_DO(data_, dto, Name, name, Data, data, Root, root, Auth, auth);
	// ????ID
	UuidFacade uf;
	data_.setId(uf.genUuid());
	// ???? ID
	RoleDAO dao;
	return dao.insert(data_) == 1 ? data_.getId() : "";
}


// ???????
bool RoleService::updateData(const RoleListDTO::Wrapper& dto)
{
	// ??? DO ????
	RoleDO data_;
	ZO_STAR_DOMAIN_DTO_TO_DO(data_, dto, Name, name, Data, data, Root, root, Auth, auth, Id, id);
	// ??????????
	RoleDAO dao;
	return dao.update(data_) == 1;
}

// ???ID???????
bool RoleService::removeData(const oatpp::List<oatpp::String>& ids)
{
	RoleDAO dao;
	std::list<std::string> datas;
	for (auto one : *ids.get())
		datas.emplace_back(one.getValue({}));
	int rows = dao.deleteByIds<RoleDO>(datas);
	if (rows == ids->size())
		return true;
	return false;
}
// 检查角色名称是否已存在
bool RoleService::isRoleNameExists(const oatpp::String& name)
{
    if (!name || name->empty()) return false;

    RoleDAO dao;
    auto roles = dao.selectByName(std::string(name->c_str()));
    return !roles.empty();
}

// 检查角色ID是否已存在
bool RoleService::isRoleIDExists(const oatpp::String& id)
{
    if (!id || id->empty()) return false;

    try {
        // 直接调用已有的selectByIdtwo方法检查角色是否存在
        auto role = roleDAO.selectByIdtwo(std::string(id->c_str()));
        return role != nullptr;
    } catch (const std::exception& e) {
        // 异常情况下返回false
        return false;
    }
}
// ???????????????б????????????????????????
RoleListPageDTO::Wrapper RoleService::listByCondition(const RoleQuery::Wrapper& query)
{
    // ??????? DTO
    auto pageDto = RoleListPageDTO::createShared();

    // ??? DAO ???
    try {
        // ????????????????? SqlSession ??? COUNT ???????? DAO::count ????
        std::ostringstream countSql;
        countSql << "SELECT COUNT(*) as total_count FROM role WHERE 1=1";
        SqlParams countParams;
        if (query->name) {
            countSql << " AND name LIKE ?";
            SQLPARAMS_PUSH(countParams, "s", std::string, "%" + *query->name + "%");
        }
        if (query->data) {
            countSql << " AND data LIKE ?";
            SQLPARAMS_PUSH(countParams, "s", std::string, "%" + *query->data + "%");
        }
        SqlSession sqlSession;
        uint64_t total = sqlSession.executeQueryNumerical(countSql.str(), countParams);

        // ????б?
        std::list<RoleDO> list = roleDAO.selectRole(query);

        // 转换为 oatpp 列表（使用只含三列的 RoleListItemDTO）
        auto rows = oatpp::List<RoleListItemDTO::Wrapper>::createShared();
        for (auto& rd : list) {
            auto dto = RoleListItemDTO::createShared();
            dto->id = rd.getId().empty() ? nullptr : oatpp::String(rd.getId().c_str());
            dto->name = rd.getName().empty() ? nullptr : oatpp::String(rd.getName().c_str());
            dto->data = rd.getData().empty() ? nullptr : oatpp::String(rd.getData().c_str());
            rows->push_back(dto);
        }

        // ???÷?? DTO
        pageDto->pageIndex = query->pageIndex;
        pageDto->pageSize = query->pageSize;
        pageDto->total = (v_int64)total;
        // ?????????
        pageDto->pages = (v_int64)((total + query->pageSize - 1) / query->pageSize);
        pageDto->rows = rows;

        return pageDto;
    }
    catch (const std::exception& e) {
        // ???????????????
        return nullptr;
    }
}

// ???? ID ??????????
RoleDetailDTO::Wrapper RoleService::getById(const oatpp::String& id)
{
    if (!id || id->empty()) return nullptr;

    try {
        // ??? DAO
        auto role = roleDAO.selectByIdtwo(std::string(id->c_str()));
        if (!role) return nullptr;

        auto dto = RoleDetailDTO::createShared();
        dto->id = role->getId().empty() ? nullptr : oatpp::String(role->getId().c_str());
        dto->name = role->getName().empty() ? nullptr : oatpp::String(role->getName().c_str());
        dto->data = role->getData().empty() ? nullptr : oatpp::String(role->getData().c_str());
        dto->root = role->getRoot().empty() ? nullptr : oatpp::String(role->getRoot().c_str());
        dto->auth = role->getAuth().empty() ? nullptr : oatpp::String(role->getAuth().c_str());

        return dto;
    }
    catch (const std::exception& e) {
        return nullptr;
    }
}


// ??????????????б?
RoleNameListDTO::Wrapper RoleService::getRoleListByKeyword(const oatpp::String& keyword)
{
    try {
        // ??????? DAO
        std::string keywordStr = keyword ? std::string(keyword->c_str()) : "";
        std::list<RoleDO> roleList = roleDAO.selectByKeyword(keywordStr);

        // ???? RoleNameListDTO
        auto roleNameListDto = RoleNameListDTO::createShared();
        auto roleNameNodes = oatpp::List<RoleNameListNodeDTO::Wrapper>::createShared();

        // ??? DO ?? DTO
        for (const auto& role : roleList) {
            auto node = RoleNameListNodeDTO::createShared();
            node->id = role.getId().empty() ? nullptr : oatpp::String(role.getId().c_str());
            node->name = role.getName().empty() ? nullptr : oatpp::String(role.getName().c_str());
            roleNameNodes->push_back(node);
        }

        roleNameListDto->roleNameList = roleNameNodes;
        return roleNameListDto;
    }
    catch (const std::exception& e) {
        return nullptr;
    }
}

// 返回可用的权限，10/31 伞一定不要删除
RoleFunctionPermissionseDTO::Wrapper RoleService::getRoleFunctionPermissions()
{
    try {
        const string mainPid = "000";
        auto roleFunctionPermissionsDto = RoleFunctionPermissionseDTO::createShared();

        // 1. 查询主模块
        // 定义不被包含的模块
        const vector<string> excludePids = { "058", "064" };
        const vector<string> excludeNames = { "首页", "系统配置" };
        std::list<MenuDO> mainModuleList = roleDAO.selectModuleListByPid(mainPid);
        for (auto it = mainModuleList.begin(); it != mainModuleList.end(); it++) {
            for (int i = 0; i < excludePids.size(); i++) {
                if (excludePids[i] == it->getId() || excludeNames[i] == it->getName()) {
                    it = mainModuleList.erase(it);
                }
            }
        }
        auto mainModuleNodes = oatpp::List<PermissionTreeMainModuleNodeDTO::Wrapper>::createShared();

        // 填充主模块节点
        
        bool is_continue = 0;
        for (const auto& mainModule : mainModuleList) {
            auto node = PermissionTreeMainModuleNodeDTO::createShared();
            is_continue = 0;
            for (int i = 0; i < excludePids.size(); i++) {
                if (excludePids[i] == mainModule.getId() || excludeNames[i] == mainModule.getName()) {

                    is_continue = 1;
                    break;
                }
            }
            if (is_continue == 1) continue;
            node->id = mainModule.getId().empty() ? nullptr : oatpp::String(mainModule.getId().c_str());
            node->name = mainModule.getName().empty() ? nullptr : oatpp::String(mainModule.getName().c_str());
            // 主模块的子列表，每个主模块有独立子列表，避免共享
            node->children = oatpp::List<PermissionTreeSubModuleNodeDTO::Wrapper>::createShared();
            mainModuleNodes->push_back(node);
        }

        // 2. 查询子模块，填充子模块节点
        auto mainModuleIt = mainModuleNodes->begin(); // 遍历主模块节点的迭代器
        for (const auto& mainModule : mainModuleList) {
            if (mainModuleIt == mainModuleNodes->end()) break;
            auto currentMainNode = *mainModuleIt;

            // 查询当前主模块下的子模块
            std::list<MenuDO> subModuleList = roleDAO.selectModuleListByPid(mainModule.getId());

            // 填充当前主模块的子模块节点
            for (const auto& subModule : subModuleList) {
                auto subNode = PermissionTreeSubModuleNodeDTO::createShared();
                subNode->id = subModule.getId().empty() ? nullptr : oatpp::String(subModule.getId().c_str());
                subNode->name = subModule.getName().empty() ? nullptr : oatpp::String(subModule.getName().c_str());
                // 权限项子列表
                subNode->children = oatpp::List<PermissionTreeItemsNodeDTO::Wrapper>::createShared();
                currentMainNode->children->push_back(subNode);

                // 3. 查询当前子模块下的权限项
                std::list<std::shared_ptr<Func_permDO>> permissionItems = roleDAO.selectRoleFunctionPermissionsByMid(subModule.getId());

                // 填充当前子模块的权限项节点
                for (const auto& permDo : permissionItems) {
                    auto itemNode = PermissionTreeItemsNodeDTO::createShared();
                    itemNode->id = permDo->getId().empty() ? nullptr : oatpp::String(permDo->getId().c_str());
                    itemNode->name = permDo->getName().empty() ? nullptr : oatpp::String(permDo->getName().c_str());
                    itemNode->is_enable = permDo->getIs_enable().empty() ? nullptr : oatpp::String(permDo->getIs_enable().c_str());
                    subNode->children->push_back(itemNode);
                }
            }
            ++mainModuleIt;
        }

        roleFunctionPermissionsDto->functionPermissions = mainModuleNodes;
        return roleFunctionPermissionsDto;
    }
    catch (const std::exception& e) {
        perror("获取角色权限失败");
        return nullptr;
    }
}

// 检查角色是否关联用户
uint64_t RoleService::checkRoleUserRelation(const oatpp::String& roleId)
{
    if (!roleId || roleId->empty()) return 0;

    try {
        // 先检查角色是否存在
        auto role = roleDAO.selectByIdtwo(std::string(roleId->c_str()));
        if (!role) return 0;

        // 如果角色存在，查询关联用户数量
        return roleDAO.countUsersByRoleId(std::string(roleId->c_str()));
    }
    catch (const std::exception& e) {
        return 0;
    }
}