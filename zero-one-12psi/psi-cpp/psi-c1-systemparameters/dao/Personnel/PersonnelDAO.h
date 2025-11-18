#pragma once
/*
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
#ifndef _PERSONNEL_DAO_
#define _PERSONNEL_DAO_
#include "BaseDAO.h"
#include "domain/do/Personnel/PersonnelDO.h"
#include "domain/query/Personnel/PersonnelQuery.h"

/**
 * 人员管理数据库操作实现
 */
class PersonnelDAO : public BaseDAO
{
private:
	//************************************
	// Method:      queryConditionBuilder
	// FullName:    PersonnelDAO::queryConditionBuilder
	// Access:      private 
	// Returns:     std::string 返回条件SQL语句，即WHERE部分的语句
	// Parameter:   const PersonnelQuery::Wrapper& query 查询数据对象
	// Parameter:   SqlParams& params 存放查询数据的参数对象
	// Description: 查询条件构建器，根据PersonnelQuery对象动态构建查询条件相关参数
	//************************************
	inline std::string queryConditionBuilder(const PersonnelQuery::Wrapper& query, SqlParams& params);
public:
	// 新增数据
	bool insert(const PersonnelFileDO& one);
	// 通过id查询数据
	PtrPersonnelFileDO selectById(const string& id);
	// 通过ID删除数据
	bool deleteById(const string& id);

	// 新增人员实现
	bool insert(const std::shared_ptr<PersonnelFileDO>& po);
	
	bool updateById(const std::shared_ptr<PersonnelFileDO>& po);
	
	bool existsByNumber(const oatpp::String& number);

	//id是否存在
	bool existsById(const oatpp::String& id);

	//frame是否存在
	bool isFrameExist(const oatpp::String& frame);

	// 统计数据条数
	uint64_t count(const PersonnelQuery::Wrapper& query);
	// 分页查询数据
	std::list<PersonnelFileDO> selectWithPage(const PersonnelQuery::Wrapper& query);
	// 通过姓名查询数据
	std::list<PersonnelFileDO> selectByName(const string& name);
	// 通过ID查询数据
	//PtrPersonnelFileDO selectById(std::string id);

};




#endif // !_PERSONNEL_DAO_
