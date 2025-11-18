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
#ifndef _PERSONNEL_SERVICE_
#define _PERSONNEL_SERVICE_
#include "domain/GlobalInclude.h"
#include "domain/dto/Personnel/PersonnelDTO.h"
#include "domain/dto/Personnel/PersonnelImportReportDTO.h"
#include "domain/dto/Personnel/PersonnelDeleteDTO.h"
#include "domain/query/Personnel/PersonnelQuery.h"

/**
 * 人员管理服务实现
 */
class PersonnelService
{
public:
	// 通过ID批量删除数据
	PeopleDeleteReportDTO::Wrapper removePeopleByIds(const oatpp::List<oatpp::String>& ids);
	// 导入文件数据 返回第一个参数为成功的条数 第二个参数为失败的条数
	PeopleImportReportDTO::Wrapper importPeopleFromExcel(const oatpp::List<PersonnelImportDTO::Wrapper>& dtolist);
	// 导出文件数据
	oatpp::List<PersonnelExportDTO::Wrapper> exportPeopleToExcel(const oatpp::List<oatpp::String>& ids);

	// 新增人员，返回新增的ID
	oatpp::String addPersonnel(const PersonnelAddDTO::Wrapper& dto);

	// 批量修改人员，返回 true 表示全部修改成功
	bool modifyPersonnel(const oatpp::List<PersonnelEditDTO::Wrapper>& dto);
	bool modPersonnelBatch(const oatpp::List<PersonnelEditDTO::Wrapper>& dtoList);

	// 检查编号是否存在
	bool checkNumberExists(const oatpp::String& number);

	// 检查组织是否存在
	bool isFrameExist(const oatpp::String& frame);

	// 分页查询所有数据
	PersonnelListPageDTO::Wrapper listAll(const PersonnelQuery::Wrapper& query);
	// 通过ID查询单个数据
	PersonnelDetailDTO::Wrapper getById(const oatpp::String& id);


};

#endif // !_PERSONNEL_SERVICE_

