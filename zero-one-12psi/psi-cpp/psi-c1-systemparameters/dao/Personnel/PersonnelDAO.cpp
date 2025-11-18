#include "stdafx.h"
#include "PersonnelDAO.h"
#include "domain/query/Personnel/PersonnelQuery.h"
#include "PersonnelMapper.h"
#include "id/UuidFacade.h"

std::string PersonnelDAO::queryConditionBuilder(const PersonnelQuery::Wrapper& query, SqlParams& params)
{
    stringstream sqlCondition;
    sqlCondition << " WHERE 1=1";
    if (query->name) {

        sqlCondition << " AND `name`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
    }
    if (query->py) {

        sqlCondition << " AND `py`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->py.getValue(""));
    }
    if (query->number) {

        sqlCondition << " AND `number`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->number.getValue(""));
    }
    if (query->frame) {

        sqlCondition << " AND `frame`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->frame.getValue(""));
    }
    if (query->sex) {

        sqlCondition << " AND sex=?";
        SQLPARAMS_PUSH(params, "i", std::string, query->sex.getValue(0));
    }
    if (query->tel) {

        sqlCondition << " AND `tel`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->tel.getValue(""));
    }
    if (query->add) {

        sqlCondition << " AND `add`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->add.getValue(""));
    }
    if (query->card) {

        sqlCondition << " AND `card`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->card.getValue(""));
    }
    if (query->data) {

        sqlCondition << " AND `data`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->data.getValue(""));
    }
    /*if (query->more) {

        sqlCondition << " AND `more`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->more.getValue(""));
    }*/
    return sqlCondition.str();
}


bool PersonnelDAO::insert(const PersonnelFileDO& one)
{
    SqlSession session;
    std::string sql = R"(
        INSERT INTO people
        (`id`,`name`, `py`, `number`, `frame`, `sex`, `tel`, `add`, `card`, `data`, `more`)
        SELECT ?, ?, ?, ?, f.id, ?, ?, ?, ?, ?, ?
        FROM frame f
        WHERE f.name = ?
    )";
    
    // 构造参数列表
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, one.getId());
    SQLPARAMS_PUSH(params, "s", std::string, one.getName());
    SQLPARAMS_PUSH(params, "s", std::string, one.getPy());
    SQLPARAMS_PUSH(params, "s", std::string, one.getNumber());
    SQLPARAMS_PUSH(params, "i", int, static_cast<int>(one.getSex()));
    SQLPARAMS_PUSH(params, "s", std::string, one.getTel());
    SQLPARAMS_PUSH(params, "s", std::string, one.getAdd());
    SQLPARAMS_PUSH(params, "s", std::string, one.getCard());
    SQLPARAMS_PUSH(params, "s", std::string, one.getData());
    SQLPARAMS_PUSH(params, "s", std::string, one.getMore());
    SQLPARAMS_PUSH(params, "s", std::string, one.getFrame());
    int result = session.executeUpdate(sql, params);
    return result > 0;
}

bool PersonnelDAO::updateById(const std::shared_ptr<PersonnelFileDO>& po)
{
    SqlSession session;
    std::string sql = R"(
        UPDATE people
        SET name=?, py=?, number=?, frame=?, sex=?, tel=?, add=?, card=?, data=?, more=?
        WHERE id=?
    )";

    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, po->getName());
    SQLPARAMS_PUSH(params, "s", std::string, po->getPy());
    SQLPARAMS_PUSH(params, "s", std::string, po->getNumber());
    SQLPARAMS_PUSH(params, "s", std::string, po->getFrame());
    SQLPARAMS_PUSH(params, "i", int, static_cast<int>(po->getSex()));
    SQLPARAMS_PUSH(params, "s", std::string, po->getTel());
    SQLPARAMS_PUSH(params, "s", std::string, po->getAdd());
    SQLPARAMS_PUSH(params, "s", std::string, po->getCard());
    SQLPARAMS_PUSH(params, "s", std::string, po->getData());
    SQLPARAMS_PUSH(params, "s", std::string, po->getMore());
    SQLPARAMS_PUSH(params, "s", std::string, po->getId());

    int result = session.executeUpdate(sql, params);
    return result > 0;
}

bool PersonnelDAO::existsByNumber(const oatpp::String& number)
{
    if (!number || number->empty()) return false;
    SqlSession session;
    std::string sql = "SELECT COUNT(*) FROM people WHERE `number`=?";

    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, number->c_str());
    uint64_t count = session.executeQueryNumerical(sql, params);
    return count > 0;
}

PtrPersonnelFileDO PersonnelDAO::selectById(const string& id)
{
    std::string sql = R"(
        SELECT 
            p.`id`,
            p.`name`,
            p.`py`,
            p.`number`,
            f.`name` AS `frame`,
            p.`sex`,
            p.`tel`,
            p.`add`,
            p.`card`,
            p.`data`,
            p.`more`
        FROM people p
        LEFT JOIN frame f ON p.`frame` = f.`id`
        WHERE p.`id` = ?
    )";
    return sqlSession->executeQueryOne<PtrPersonnelFileDO>(sql, PtrPersonnelFileMapper(), "%s", id);
}


bool PersonnelDAO::deleteById(const string& id)
{
    string sql = "DELETE FROM people WHERE `id`=?";
    return sqlSession->executeUpdate(sql, "%s", id);
}

bool PersonnelDAO::insert(const std::shared_ptr<PersonnelFileDO>& po)
{
    if (!po) return false;
    return insert(*po); // 调用上面的重载
}

bool PersonnelDAO::existsById(const oatpp::String& id)
{
    if (!id || id->empty()) return false;
    SqlSession session;
    std::string sql = "SELECT COUNT(*) FROM people WHERE `id`=?";

    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, id->c_str());
    uint64_t count = session.executeQueryNumerical(sql, params);
    return count > 0;
}

bool PersonnelDAO::isFrameExist(const oatpp::String& frame)
{
    if (!frame || frame->empty()) return false;
    SqlSession session;
    std::string sql = "SELECT COUNT(*) FROM frame WHERE `name`=?";

    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, frame->c_str());
    uint64_t count = session.executeQueryNumerical(sql, params);
    return count > 0;
}

uint64_t PersonnelDAO::count(const PersonnelQuery::Wrapper& query)
{
    SqlParams params;
    string sql = "SELECT COUNT(*) FROM People ";
    // 构建查询条件
    sql += queryConditionBuilder(query, params);
    // 执行查询
    return sqlSession->executeQueryNumerical(sql, params);
}

// DAO层：分页查询
// 功能：根据查询条件分页查询people表的数据
// DAO层：分页查询
// 功能：根据查询条件分页查询people表的数据
std::list<PersonnelFileDO> PersonnelDAO::selectWithPage(const PersonnelQuery::Wrapper& query)
{
    SqlParams params;
    string sql = "SELECT id,name,py,number,frame,sex,tel,`add`,`card`,`data`,`more` FROM people ";
    // 构建查询条件
    sql += queryConditionBuilder(query, params);
    // 构建排序语句
    // sql += " ORDER BY IFNULL(`update_time`, `create_time`) DESC, `id` DESC ";
    // 构建分页条件
    //sql += " LIMIT " + std::to_string(((query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10)) + "," + std::to_string(query->pageSize.getValue(10)));
    // 计算分页参数
    int offset = (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10);
    int count = query->pageSize.getValue(10);

    // 正确拼接 LIMIT 子句
    sql += " LIMIT " + std::to_string(offset) + ", " + std::to_string(count);
    // 执行查询
    return sqlSession->executeQuery<PersonnelFileDO>(sql, PersonnelMapper(), params);
}

//std::list<PersonnelFileDO> PersonnelDAO::selectByName(const string& name)
//{
//	string sql = "SELECT id,name,sex,age FROM sample WHERE `name` LIKE CONCAT('%',?,'%')";
//	return sqlSession->executeQuery<PersonnelFileDO>(sql, PersonnelMapper(), "%s", name);
//}



std::list<PersonnelFileDO> PersonnelDAO::selectByName(const string& name)
{
    // 方式1：使用CONCAT函数
    string sql = "SELECT id, name, py, number, frame, sex, tel, add, card, data, more FROM sample "
        "WHERE `name` LIKE CONCAT('%', ?, '%')";

    return sqlSession->executeQuery<PersonnelFileDO>(sql, PersonnelMapper(), "%s", name);
    // 参数格式："%s" 表示一个字符串参数
}
