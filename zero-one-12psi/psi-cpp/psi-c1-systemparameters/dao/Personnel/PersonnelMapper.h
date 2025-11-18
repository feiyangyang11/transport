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
#ifndef _PERSONNEL_MAPPER_
#define _PERSONNEL_MAPPER_

#include "Mapper.h"
#include "domain/do/Personnel/PersonnelDO.h"

/**
 * 示例表字段匹配映射
 */
class PersonnelFileMapper : public Mapper<PersonnelFileDO>
{
public:
	PersonnelFileDO mapper(ResultSet* resultSet) const override
	{
		PersonnelFileDO data;
		data.setId(resultSet->getString(1));
		data.setName(resultSet->getString(2));
		data.setPy(resultSet->getString(3));
		data.setNumber(resultSet->getString(4));
		data.setFrame(resultSet->getString(5));
		data.setSex(resultSet->getInt(6));
		data.setTel(resultSet->getString(7));
		data.setAdd(resultSet->getString(8));
		data.setCard(resultSet->getString(9));
		data.setData(resultSet->getString(10));
		data.setMore(resultSet->getString(11));
		return data;
	}
};

/**
 * 示例表字段匹配映射-创建智能指针对象
 */
class PtrPersonnelFileMapper : public Mapper<PtrPersonnelFileDO>
{
public:
	PtrPersonnelFileDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<PersonnelFileDO>();
		data->setId(resultSet->getString(1));
		data->setName(resultSet->getString(2));
		data->setPy(resultSet->getString(3));
		data->setNumber(resultSet->getString(4));
		data->setFrame(resultSet->getString(5));
		data->setSex(resultSet->getInt(6));
		data->setTel(resultSet->getString(7));
		data->setAdd(resultSet->getString(8));
		data->setCard(resultSet->getString(9));
		data->setData(resultSet->getString(10));
		data->setMore(resultSet->getString(11));
		return data;
	}
};

/**
 * 人员管理匹配映射
 */
class PersonnelMapper : public Mapper<PersonnelFileDO>
{
public:
	PersonnelFileDO mapper(ResultSet* resultSet) const override
	{
		PersonnelFileDO data;
		data.setId(resultSet->getString("id"));
		data.setName(resultSet->getString("name"));
		data.setPy(resultSet->getString("py"));
		data.setNumber(resultSet->getString("number"));
		data.setFrame(resultSet->getString("frame"));
		//data.setSex(resultSet->getInt("sex"));
		data.setSex(static_cast<int8_t>(resultSet->getInt("sex")));
		data.setTel(resultSet->getString("tel"));
		data.setAdd(resultSet->getString("add"));
		data.setCard(resultSet->getString("card"));
		data.setData(resultSet->getString("data"));
		//data.setMore(resultSet->getString("more"));
		return data;
	}
};

/**
 * 人员管理匹配映射-创建智能指针对象
 */
class PtrPersonnelMapper : public Mapper<PtrPersonnelFileDO>
{
public:
	PtrPersonnelFileDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<PersonnelFileDO>();
		//data.setId(resultSet->getString("id"));
		data->setId(resultSet->getString("id"));
		data->setName(resultSet->getString("name"));
		data->setPy(resultSet->getString("py"));
		data->setNumber(resultSet->getString("number"));
		data->setFrame(resultSet->getString("frame"));
		//data->setSex(resultSet->getInt("sex"));
		data->setSex(static_cast<int8_t>(resultSet->getInt("sex")));
		data->setTel(resultSet->getString("tel"));
		data->setAdd(resultSet->getString("add"));
		data->setCard(resultSet->getString("card"));
		data->setData(resultSet->getString("data"));
		data->setMore(resultSet->getString("more"));
		return data;
	}
};

#endif // !_PERSONNEL_MAPPER_