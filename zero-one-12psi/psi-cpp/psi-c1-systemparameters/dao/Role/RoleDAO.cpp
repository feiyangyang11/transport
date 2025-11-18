#include "RoleDAO.h"
#include "stdafx.h"
#include "RoleMapper.h"
#include "../../../lib-mysql/include/SqlSession.h"

inline std::string RoleDAO::queryConditionBuilder(const RoleQuery::Wrapper& query, SqlParams& params)
{
	return std::string();
}

std::list<RoleDO> RoleDAO::selectWithPage(const RoleQuery::Wrapper& query)
{
	return std::list<RoleDO>();
}

std::list<RoleDO> RoleDAO::selectByName(const string& name)
{
    return std::list<RoleDO>();
}

PtrRoleDO RoleDAO::selectById(std::string id)
{
    return PtrRoleDO();
}

// 分页查询角色列表，支持名称和描述查询（只返回 id,name,data）
std::list<RoleDO> RoleDAO::selectRole(const RoleQuery::Wrapper& query)
{
    std::ostringstream sql;
    sql << "SELECT id, name, data FROM role WHERE 1=1";

    SqlParams params;

    // 添加查询条件 - 按名称模糊查询
    if (query->name) {
        sql << " AND name LIKE ?";
        SQLPARAMS_PUSH(params, "s", std::string, "%" + *query->name + "%");
    }

    // 添加查询条件 - 按数据描述查询
    if (query->data) {
        sql << " AND data LIKE ?";
        SQLPARAMS_PUSH(params, "s", std::string, "%" + *query->data + "%");
    }

    // 添加分页（注意：LIMIT ? OFFSET ? 可能需要数据库驱动支持参数化 LIMIT）
    sql << " LIMIT ? OFFSET ?";
    SQLPARAMS_PUSH(params, "ull", uint64_t, query->pageSize);
    SQLPARAMS_PUSH(params, "ull", uint64_t, (query->pageIndex - 1) * query->pageSize);

    // 使用简化 mapper（只读 3 列）
    RoleSimpleMapper mapper;
    return sqlSession->executeQuery<RoleDO, RoleSimpleMapper>(sql.str(), mapper, params);
}

// 根据 ID 查询角色（保持完整列）
PtrRoleDO RoleDAO::selectByIdtwo(std::string id)
{
    std::ostringstream sql;
    sql << "SELECT id, name, data, root, auth FROM role WHERE id = ?";

    RoleMapper mapper;
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, id);

    RoleDO result = sqlSession->executeQueryOne<RoleDO, RoleMapper>(sql.str(), mapper, params);

    if (!result.getId().empty()) {
        return std::make_shared<RoleDO>(std::move(result));
    }

    return nullptr;
}

std::list<RoleDO> RoleDAO::selectByKeyword(const string& keyword)
{
    std::ostringstream sql;
    sql << "SELECT id, name, data, root, auth FROM role";

    SqlParams params;

    if (!keyword.empty()) {
        sql << " WHERE name LIKE ?";
        SQLPARAMS_PUSH(params, "s", std::string, "%" + keyword + "%");
    }

    RoleMapper mapper;
    return sqlSession->executeQuery<RoleDO, RoleMapper>(sql.str(), mapper, params);
}

// 根据 mid 查询子功能权限列表，10/31 伞一定不要删除
std::list<PtrFunc_permDO> RoleDAO::selectRoleFunctionPermissionsByMid(const string& mid)
{
    std::ostringstream sql;
    sql << "SELECT id, mid, name, url, sort, is_enable, remark FROM func_perm";
    SqlParams params;
    if (!mid.empty()) {
        sql << " WHERE mid = ?";
        SQLPARAMS_PUSH(params, "s", std::string, mid);
    }
    PtrFunc_permMapper mapper;
    //return {};
    return sqlSession->executeQuery<PtrFunc_permDO, PtrFunc_permMapper>(sql.str(), mapper, params);
    /*if (!result.empty()) {
        return result;
    }
    return std::list<Func_permDo>();*/
}

// 通过 pid 查询主模块、子模块列表，10/31 伞一定不要删除
std::list<MenuDO> RoleDAO::selectModuleListByPid(const string& pid)
{
    std::ostringstream sql;
    sql << "SELECT id, pid, name, `key`, model, `type`, resource, sort, ico, root, data FROM menu";
    SqlParams params;
    if (!pid.empty()) {
        sql << " WHERE pid = ?";
        SQLPARAMS_PUSH(params, "s", std::string, pid);
    }
    MenuMapper mapper;
    //return {};
    return sqlSession->executeQuery<MenuDO, MenuMapper>(sql.str(), mapper, params);
   /* if (!result.empty()) {
        return result;
    }
    return std::list<MenuDo>();*/
}

// 统计角色关联的用户数量
uint64_t RoleDAO::countUsersByRoleId(const std::string& roleId)
{
    if (roleId.empty()) return 0;

    try {
        // 先获取角色详情以获取角色名称
        auto role = selectByIdtwo(roleId);
        if (!role || role->getName().empty()) {
            return 0; // 跳过无法获取名称的角色
        }

        // 查询与当前角色名称关联的用户数量
        std::ostringstream sql;
        sql << "SELECT COUNT(*) FROM user WHERE role = ?";

        SqlParams params;
        SQLPARAMS_PUSH(params, "s", std::string, role->getName());

        return sqlSession->executeQueryNumerical(sql.str(), params);
    }
    catch (const std::exception& e) {
        return 0;
    }
}