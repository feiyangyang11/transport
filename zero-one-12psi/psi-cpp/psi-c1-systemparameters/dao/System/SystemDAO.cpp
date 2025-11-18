
#include "SystemDAO.h"
#include "domain/do/System/SystemDO.h"
#include "SystemMapper.h"


uint64_t SystemDAO::count() {
	std::string sql = "SELECT COUNT(*) FROM sys;";
	return sqlSession->execute(sql);
}


list<PtrSystemDO> SystemDAO::selectAllSys() {
	std::string sql = "SELECT id, name, info, data FROM sys;";
	return sqlSession->executeQuery<PtrSystemDO>(sql, SystemMapper());
}

oatpp::Int32 SystemDAO::updateById(const list<PtrSystemDO>& data) {
	std::string sql = "UPDATE sys SET name=?, info=?, data=? WHERE id=?;";
	std::string idSql = "SELECT COUNT(*) FROM `sys` WHERE `id` = ?;";
	sqlSession->beginTransaction();
	for (auto& one : data) {
		auto cnt = sqlSession->executeQueryNumerical(idSql, "%s", one->getId());
		cout << "cnt = " << cnt << endl;
		if (cnt == 0) {
			sqlSession->rollbackTransaction();
			return oatpp::Int32(5435);
		}
		bool result = sqlSession->executeUpdate(sql, "%s%s%s%s", one->getName(), one->getInfo(), one->getRemark(), one->getId());
		if (result < 0) {
			sqlSession->rollbackTransaction();
			return oatpp::Int32(500);
		}
	}
	sqlSession->commitTransaction();
	return oatpp::Int32(0);
}