/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/19 14:41:24

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
#include "UserDAO.h"
#include "UserMapper.h"
#include "UserDetailMapper.h"

uint64_t UserDAO::count(const UserQuery::Wrapper& query)
{
	string sql = "SELECT count(id) FROM `user` ";
	SqlParams params;
	bool hasCondition = false;

	// 拼接多条件（与查询所有用户保持一致的条件逻辑）
	if (query->name)
	{
		sql += hasCondition ? "AND" : "WHERE";
		sql += " `name` LIKE CONCAT('%',?,'%') ";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
		hasCondition = true;
	}
	if (query->tel)
	{
		sql += hasCondition ? "AND" : "WHERE";
		sql += " tel LIKE CONCAT('%',?,'%') ";
		SQLPARAMS_PUSH(params, "s", std::string, query->tel.getValue(""));
		hasCondition = true;
	}
	if (query->user)
	{
		sql += hasCondition ? "AND" : "WHERE";
		sql += " `user` LIKE CONCAT('%',?,'%') ";
		SQLPARAMS_PUSH(params, "s", std::string, query->user.getValue(""));
		hasCondition = true;
	}
	if (query->data)
	{
		sql += hasCondition ? "AND" : "WHERE";
		sql += " `data` LIKE CONCAT('%',?,'%') ";
		SQLPARAMS_PUSH(params, "s", std::string, query->data.getValue(""));
		hasCondition = true;
	}

	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<PtrUserDO> UserDAO::selectAll(const UserQuery::Wrapper& query)
{
	// 查询字段：用户名称、所属组织、所属角色、登录账号、手机号码、备注信息
	string sql = "SELECT su.id, su.`name`, su.frame, su.role, su.`user`, su.tel, su.`data` "
		"FROM `user` su ";

	SqlParams params;
	bool hasCondition = false;

	// 拼接查询条件：用户名称、手机号码、用户账号、备注信息（均为模糊查询）
	if (query->name)
	{
		sql += hasCondition ? "AND" : "WHERE";
		sql += " su.`name` LIKE CONCAT('%',?,'%') ";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
		hasCondition = true;
	}
	if (query->tel)
	{
		sql += hasCondition ? "AND" : "WHERE";
		sql += " su.tel LIKE CONCAT('%',?,'%') ";
		SQLPARAMS_PUSH(params, "s", std::string, query->tel.getValue(""));
		hasCondition = true;
	}
	if (query->user)
	{
		sql += hasCondition ? "AND" : "WHERE";
		sql += " su.`user` LIKE CONCAT('%',?,'%') ";
		SQLPARAMS_PUSH(params, "s", std::string, query->user.getValue(""));
		hasCondition = true;
	}
	if (query->data)
	{
		sql += hasCondition ? "AND" : "WHERE";
		sql += " su.`data` LIKE CONCAT('%',?,'%') ";
		SQLPARAMS_PUSH(params, "s", std::string, query->data.getValue(""));
		hasCondition = true;
	}

	// 保留分页逻辑
	sql += "LIMIT ?,?";
	SQLPARAMS_PUSH(params, "ull", uint64_t, (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10));
	SQLPARAMS_PUSH(params, "ull", uint64_t, query->pageSize.getValue(10));

	return sqlSession->executeQuery<PtrUserDO>(sql, UserMapper(), params);
}

PtrUserDO UserDAO::selectById(const string& id)
{
	// 查询字段：用户名称、所属组织、所属角色、用户账号、手机号码、用户密码、用户头像、备注信息
	string sql = "SELECT su.id, su.`name`, su.frame, su.role, su.`user`, su.tel, su.pwd, su.img, su.`data`, "
		"an.save_path AS avatar_save_path, an.`name` AS avatar_name "  // 保留头像关联信息
		"FROM `user` su "
		"LEFT JOIN annex an ON su.img = an.id "  // 关联附件表获取头像路径
		"WHERE su.id = ?";  // 修正原代码的字符串拼接错误

	return sqlSession->executeQueryOne<PtrUserDO>(sql, UserDetailMapper(), "%s", id);
}



PtrUserDO UserDAO::countByColumn(const string columnName,const string& columnValue) {
	string sql = "";
	SqlParams params;
	//frame字段要去frame表查
	if (columnName == "frame") {
		sql = "SELECT id FROM frame WHERE id = ? LIMIT 1";
		SQLPARAMS_PUSH(params, "s", std::string, columnValue);
		return sqlSession->executeQueryOne<PtrUserDO>(sql, FrameOnlyUserMapper(), params);
	}
	//role字段要去role表查
	if (columnName == "role") {
		sql = "SELECT id FROM role WHERE id = ? LIMIT 1";
		SQLPARAMS_PUSH(params, "s", std::string, columnValue);
		return sqlSession->executeQueryOne<PtrUserDO>(sql, RoleOnlyUserMapper(), params);
	}
	//user字段是sql关键字，需要特殊处理
	if (columnName == "user") {
		sql = "SELECT name FROM `user` WHERE `user` = ? LIMIT 1";
		SQLPARAMS_PUSH(params, "s", std::string, columnValue);
		return sqlSession->executeQueryOne<PtrUserDO>(sql, CommonUserMapper(), params);
	}
//----------------------------------------------------------------------------------------//
	//其他字段都查user表（查哪个字段都行，这里随便选了name），只是条件不一样
	if (columnName == "tel") {
		sql = "SELECT name FROM `user` WHERE tel = ? LIMIT 1";
		SQLPARAMS_PUSH(params, "s", std::string, columnValue);
		return sqlSession->executeQueryOne<PtrUserDO>(sql, CommonUserMapper(), params);
	}
	if (columnName == "id") {
		sql = "SELECT name FROM `user` WHERE id = ? LIMIT 1";
		SQLPARAMS_PUSH(params, "s", std::string, columnValue);
		return sqlSession->executeQueryOne<PtrUserDO>(sql, CommonUserMapper(), params);
	}
	//传入的字段是其他的话就返回空
	return nullptr;
	//return 0;
}
bool UserDAO::insertOne(const PtrUserDO& user)
{
	// 构建插入SQL，使用?作为参数占位符
	string sql = "INSERT INTO `user` ("
		"id, name, py, tel, frame, role, `user`, pwd, img, data,token,expire,more) "  // 注意user是关键字，用`反引号包裹
		" VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?,?,?,?)";

	// 定义参数列表
	SqlParams params;
	// 绑定参数（顺序与SQL中?的顺序一致）
	SQLPARAMS_PUSH(params, "s", std::string, user->getId());         // id
	SQLPARAMS_PUSH(params, "s", std::string, user->getName());         // 用户名
	SQLPARAMS_PUSH(params, "s", std::string, user->getPy());           // 拼音（假设py是拼音字段）
	SQLPARAMS_PUSH(params, "s", std::string, user->getTel());          // 电话
	SQLPARAMS_PUSH(params, "s", std::string, user->getFrame());        // 框架（假设是字符串类型）
	SQLPARAMS_PUSH(params, "s", std::string, user->getRole());         // 角色
	SQLPARAMS_PUSH(params, "s", std::string, user->getUser());         // 账号（注意字段名是user）
	SQLPARAMS_PUSH(params, "s", std::string, user->getPwd());          // 密码
	SQLPARAMS_PUSH(params, "s", std::string, user->getImg());          // 头像附件ID（关联annex表的id）
	SQLPARAMS_PUSH(params, "s", std::string, user->getData());          // 备注
	SQLPARAMS_PUSH(params, "s", std::string, user->getToken());          // 密钥
	SQLPARAMS_PUSH(params, "i", std::int32_t, user->getExpire());          // 密钥时长
	SQLPARAMS_PUSH(params, "s", std::string, user->getMore());          // 扩展

	// 执行插入操作，返回是否成功（影响行数>0则视为成功）
	int affectedRows = sqlSession->executeUpdate(sql, params);

	return affectedRows > 0;
	//return true;
}
bool UserDAO::updateOne(const PtrUserDO& user)
{
	// 构建插入SQL，使用?作为参数占位符
	string sql = "UPDATE `user` SET ";
	bool isChanged = false;
	SqlParams params;
	// 绑定参数（顺序与SQL中?的顺序一致）
	if (!user->getName().empty()) {
		sql += "name = ? , ";
		SQLPARAMS_PUSH(params, "s", std::string, user->getName());         // 用户名
		isChanged = true;
	}
	if (!user->getPy().empty()) {
		sql += "py = ? , ";
		SQLPARAMS_PUSH(params, "s", std::string, user->getPy());           // 拼音（假设py是拼音字段）
		isChanged = true;
	}
	if (!user->getTel().empty()) {
		sql += "tel = ? , ";
		SQLPARAMS_PUSH(params, "s", std::string, user->getTel());          // 电话
		isChanged = true;
	}
	if (!user->getFrame().empty()) {
		sql += "frame = ? , ";
		SQLPARAMS_PUSH(params, "s", std::string, user->getFrame());        // 组织
		isChanged = true;
	}
	if (!user->getRole().empty()) {
		sql += "role = ? , ";
		SQLPARAMS_PUSH(params, "s", std::string, user->getRole());         // 角色
		isChanged = true;
	}
	if (!user->getUser().empty()) {
		sql += "`user` = ? , ";
		SQLPARAMS_PUSH(params, "s", std::string, user->getUser());         // 账号（注意字段名是user）
		isChanged = true;
	}
	if (!user->getPwd().empty()) {
		sql += "pwd = ? , ";
		SQLPARAMS_PUSH(params, "s", std::string, user->getPwd());          // 密码
		isChanged = true;
	}
	if (!user->getImg().empty()) {
		sql += "img = ? , ";
		SQLPARAMS_PUSH(params, "s", std::string, user->getImg());          // 头像附件ID（关联annex表的id）
		isChanged = true;
	}
	if (!user->getData().empty()) {
		sql += "data = ? , ";
		SQLPARAMS_PUSH(params, "s", std::string, user->getData());          // 备注
		isChanged = true;
	}
	//if (!user->getToken().empty()) {
	//	sql += "token = ? , ";
	//	SQLPARAMS_PUSH(params, "s", std::string, user->getToken());          // 密钥
	//	isChanged = true;
	//}
	//if (user->getExpire() > 0) {
	//	sql += "expire = ? , ";
	//	SQLPARAMS_PUSH(params, "i", std::int32_t, user->getExpire());          // 密钥时长
	//	isChanged = true;
	//}
	if (!user->getMore().empty()) {
		sql += "more = ? , ";
		SQLPARAMS_PUSH(params, "s", std::string, user->getMore());          // 扩展
		isChanged = true;
	}
	if (!isChanged) {
		//没有更新
		return false;
	}
	sql = sql.substr(0, sql.size() - 2);// 去掉最后的逗号和空格
	sql += " WHERE id = ?";
	SQLPARAMS_PUSH(params, "s", std::string, user->getId());         

	// 执行插入操作，返回是否成功（影响行数>0则视为成功）
	int64_t affectedRows = sqlSession->executeUpdate(sql, params);

	return affectedRows > 0;
	//return true;
}
bool UserDAO::deleteOneById(const std::string& id) {
	string sql = "DELETE FROM `user` WHERE id = ?";
	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, id);

	int64_t affectedRows = sqlSession->executeUpdate(sql, params);
	return affectedRows > 0;
	//return true;
}

