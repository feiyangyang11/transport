/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/10/13 21:38:24

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
#include "PersonnelController.h"
#include "service/Personnel/PersonnelService.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
// FastDFS需要导入的头
#include "ServerInfo.h"
#include "NacosClient.h"
#include "FastDfsClient.h"

#include "domain/dto/Personnel/PersonnelDTO.h"
#include <regex>
#include <sstream>


#define SET_VO_FAIL(vo, err_code, err_msg) { \
  (vo)->code = (err_code); \
  (vo)->message = (err_msg); \
  (vo)->data = ""; \
}


#define INIT_VO_SUCCESS(vo) { \
  (vo)->code = 10000; \
  (vo)->message = "success"; \
  (vo)->data = ""; \
}


#define DEFAULT_ORG_ID "DEFAULT_ORG"
#define DEFAULT_SEX "女"

PersonnelListPageJsonVO::Wrapper PersonnelController::executeQueryAll(const PersonnelQuery::Wrapper& query)
{
	// 定义一个Service
	PersonnelService service;
	// 查询数据
	auto result = service.listAll(query);
	// 响应结果
	auto jvo = PersonnelListPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}


PersonnelDetailJsonVO::Wrapper PersonnelController::executeQueryOne(const String& id)
{
	PersonnelService per;
	auto jvo = PersonnelDetailJsonVO::createShared();
	auto data = per.getById(id);
	if (data)
		jvo->success(data);
	else
		jvo->fail({});
	return jvo;
	//return {};
}




PersonnelJsonVO::Wrapper PersonnelController::executeAddPersonnel(const PersonnelAddDTO::Wrapper& dto)
{
	// Service instance
	PersonnelService ps;
	// Create response object
	auto pvo = PersonnelJsonVO::createShared();
	INIT_VO_SUCCESS(pvo);

	//==================== 1. Required fields ====================//

	// Check name
	if (dto->name == nullptr || dto->name->empty()) {
		SET_VO_FAIL(pvo, 9999, "Name cannot be empty");
		return pvo;
	}

	// Check organization
	if (dto->frame == nullptr || dto->frame->empty()) {
		SET_VO_FAIL(pvo, 9999, "Organization cannot be empty");
		return pvo;
	}

	// Check if organization exists (via Service)
	if (!ps.isFrameExist(dto->frame)) {
		SET_VO_FAIL(pvo, 9999, "Organization does not exist");
		return pvo;
	}


	// Check number
	if (dto->number == nullptr || dto->number->empty()) {
		SET_VO_FAIL(pvo, 9999, "Personnel number cannot be empty");
		return pvo;
	}

	// Check number uniqueness
	if (ps.checkNumberExists(dto->number)) {
		SET_VO_FAIL(pvo, 9999, "Personnel number already exists");
		return pvo;
	}

	// Check organization
	if (dto->frame == nullptr || dto->frame->empty()) {
		SET_VO_FAIL(pvo, 9999, "Organization cannot be empty");
		return pvo;
	}

	// Check gender
	if (dto->sex == nullptr || dto->sex->empty()) {
		SET_VO_FAIL(pvo, 9999, "Gender cannot be empty");
		return pvo;
	}
	else {
		if (*dto->sex != u8"男" && *dto->sex != u8"女") {
			SET_VO_FAIL(pvo, 9999, u8"Gender must be '男' or '女'");
			return pvo;
		}
	}

	//==================== 2. Optional fields ====================//

	// Telephone check (optional, must be positive integer if provided)
	if (dto->tel && !dto->tel->empty()) {
		try {
			int telNum = std::stoi(dto->tel->c_str());
			if (telNum <= 0) {
				SET_VO_FAIL(pvo, 9999, "Invalid telephone number format");
				return pvo;
			}
		}
		catch (...) {
			SET_VO_FAIL(pvo, 9999, "Telephone number should contain only digits");
			return pvo;
		}
	}

	// Address (optional, max length 64)
	if (dto->add && !dto->add->empty()) {
		if (dto->add->size() > 64) {
			SET_VO_FAIL(pvo, 9999, "Address too long (max 64 characters)");
			return pvo;
		}
	}

	// ID card (optional, must be 18 digits: first 17 are numbers, last is number or X)
	if (dto->card && !dto->card->empty()) {
		std::string idCard(dto->card->c_str());
		std::regex idPattern("^[0-9]{17}[0-9Xx]{1}$");
		if (!std::regex_match(idCard, idPattern)) {
			SET_VO_FAIL(pvo, 9999, "Invalid ID card format (must be 18 digits or ending with X)");
			return pvo;
		}
	}

	// Remark (optional, max length 256)
	if (dto->data && !dto->data->empty()) {
		if (dto->data->size() > 256) {
			SET_VO_FAIL(pvo, 9999, "Remark too long (max 256 characters)");
			return pvo;
		}
	}

	//==================== 3. Call Service to insert ====================//

	oatpp::String id = ps.addPersonnel(dto);

	INIT_VO_SUCCESS(pvo);
	pvo->data = id;

	return pvo;
}



PersonnelJsonVO::Wrapper PersonnelController::executeModPersonnel(const PersonnelEditDTO::Wrapper& dto)
{
	auto pvo = PersonnelJsonVO::createShared();
	PersonnelService service;
	pvo->code = 10000;
	pvo->message = "Operation successful";
	pvo->data = "";

	// 组织存在性检查
	if (dto->frame && !dto->frame->empty()) {
		if (!service.isFrameExist(dto->frame)) {
			pvo->code = 9999;
			pvo->message = "Organization does not exist";
			return pvo;
		}
	}


	// 1. Check ID
	if (dto->id == nullptr || dto->id->empty()) {
		pvo->code = 9999;
		pvo->message = "Personnel ID cannot be empty";
		return pvo;
	}

	// 2. Check name (optional)
	if (dto->name && dto->name->size() > 32) {
		pvo->code = 9999;
		pvo->message = "Name too long (max 32 characters)";
		return pvo;
	}

	// 3. Check number uniqueness
	if (dto->number && service.checkNumberExists(dto->number)) {
		pvo->code = 9999;
		pvo->message = "Personnel number already exists";
		return pvo;
	}

	// 4. Check gender, ID card, phone, etc. (same as Add)
	if (dto->card && !dto->card->empty()) {
		std::string c(dto->card->c_str());
		if (!(std::regex_match(c, std::regex("^[0-9]{17}[0-9Xx]$")))) {
			pvo->code = 9999;
			pvo->message = "Invalid ID card format";
			return pvo;
		}
	}

	if (dto->tel && !dto->tel->empty()) {
		try {
			int telNum = std::stoi(dto->tel->c_str());
			if (telNum <= 0) {
				pvo->code = 9999;
				pvo->message = "Invalid telephone number";
				return pvo;
			}
		}
		catch (...) {
			pvo->code = 9999;
			pvo->message = "Telephone number must be numeric";
			return pvo;
		}
	}

	// 5. Call Service layer
	auto dtoList = oatpp::List<PersonnelEditDTO::Wrapper>::createShared();
	dtoList->push_back(dto);
	bool ok = service.modifyPersonnel(dtoList);
	if (!ok) {
		pvo->code = 9999;
		pvo->message = "Failed to modify personnel record";
		return pvo;
	}

	return pvo;
}


PersonnelJsonVO::Wrapper PersonnelController::executeModPersonnel(const oatpp::List<PersonnelEditDTO::Wrapper>& dtoList)
{
	return {};
}

PersonnelDeleteJsonVO::Wrapper PersonnelController::execRemovePeople(const String& ids)
// ListJsonVO<String>::Wrapper PersonnelController::execRemovePeople(const List<String>& ids)
{
	// 定义返回数据对象
	auto jvo = PersonnelDeleteJsonVO::createShared();
	// 参数校验
	if (ids->empty())
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 直接用 std::string 操作
	std::string idsStr = *ids.get();
	for (size_t pos; (pos = idsStr.find("%2C")) != std::string::npos; )
		idsStr.replace(pos, 3, ",");
	for (size_t pos; (pos = idsStr.find("%EF%BC%8C")) != std::string::npos; )
		idsStr.replace(pos, 3, ",");

	// 解析逗号分隔的 id
	std::stringstream ss(idsStr);
	std::string item;
	auto idList = oatpp::List<oatpp::String>::createShared();
	while (std::getline(ss, item, ',')) {
		if (!item.empty()) {
			idList->push_back(item.c_str());
		}
	}

	// 定义一个Service
	PersonnelService service;
	// 执行数据删除
	auto result = service.removePeopleByIds(idList);
	jvo->data = result;
	jvo->message = u8"批量删除完成";
	jvo->code = 10000;
	return jvo;
}

std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> PersonnelController::execExportPeople(const List<String>& ids)
{
	// 定义一个Service
	PersonnelService service;
	// 查询数据
	auto result = service.exportPeopleToExcel(ids);

	//int totalCnt = ids->size();
	//int resultCnt = result->size();
	//int failedCnt = totalCnt - resultCnt;

	// 将数据写入到Excel中
	auto buff = ExcelComponent().writeVectorToBuff("people",
		[result](ExcelComponent* ex) {
			// 写入表头
			ex->addHeader({
				ZH_WORDS_GETTER("personnel.field.name") ,
				ZH_WORDS_GETTER("personnel.field.number"),
				ZH_WORDS_GETTER("personnel.field.frame") ,
				ZH_WORDS_GETTER("personnel.field.sex") ,
				ZH_WORDS_GETTER("personnel.field.tel") ,
				ZH_WORDS_GETTER("personnel.field.add"),
				ZH_WORDS_GETTER("personnel.field.card") ,
				ZH_WORDS_GETTER("personnel.field.data") ,
				});
			// 写入数据
			int row = 2;
			int col = 1;
			for (auto item : *(result.get())) {
				col = 1;
				ex->setCellValue(row, col++, item->name ? (item->name) : "");
				ex->setCellValue(row, col++, item->number ? (item->number) : "");
				ex->setCellValue(row, col++, item->frame ? (item->frame) : "");
				if(item->sex==1) ex->setCellValue(row, col++, u8"男");
				else ex->setCellValue(row, col++, u8"女");
				ex->setCellValue(row, col++, item->tel ? (item->tel) : "");
				ex->setCellValue(row, col++, item->add ? (item->add) : "");
				ex->setCellValue(row, col++, item->card ? (item->card) : "");
				ex->setCellValue(row, col++, item->data ? (item->data) : "");
				ex->setRowProperties(row++);
			}

			int totalCount = result->size();
			ex->setCellValue(row, 1, u8"总数：" + std::to_string(totalCount));
		});

	// 组装下发数据
	const char* charData = reinterpret_cast<const char*>(buff.data());
	auto fstring = String(charData, buff.size());

	// 测试将报表上传到fastdfs
	//ZO_CREATE_DFS_CLIENT_URL(dfs, urlPrefix);
	//string filepath = dfs.uploadFile(charData, buff.size(), "xlsx");

	// 打印文件上传成功后的下载地址
	//string downloadUrl = urlPrefix + filepath;
	//OATPP_LOGD("Multipart", "download url='%s'", downloadUrl.c_str());

	// 创建响应头
	auto response = createResponse(Status::CODE_200, fstring);

	// 设置响应头信息
	response->putHeader(Header::CONTENT_TYPE, " application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
	std::string filename = "people-" + SimpleDateTimeFormat::format() + ".xlsx";
	response->putHeader("Content-Disposition", "attachment; filename=" + filename);
	

	// 影响成功结果
	return response;
}

PersonnelImportJsonVO::Wrapper PersonnelController::execImportPeople(std::shared_ptr<IncomingRequest> request)
{
	// 1 初始化
	API_MULTIPART_INIT(container, reader);

	// 2 配置读取器
	API_MULTIPART_CONFIG_MEMO_DEFAULT(reader, -1);

	// 3 读取数据
	request->transferBody(&reader);

	// 打印上传总部分数 
	OATPP_LOGD("Multipart", "parts_count=%d", container->count());

	// 4 解析数据
	// 获取文件数据 
	API_MULTIPART_PARSE_FILE_FIELD(container, "file", file);//与传入的file参数对应
	if (!file) {
		auto jvo = PersonnelImportJsonVO::createShared();
		jvo->code = 9999;
		jvo->message = "No uploaded file detected";
		jvo->data = {};
		return jvo;
	}
	
	std::vector<std::vector<std::string>> rows;
	try {
		rows = ExcelComponent::readIntoVector(file->data(), file->size(), "people");//sheet名字 people
	}
	catch (const std::exception& e) {
		auto jvo = PersonnelImportJsonVO::createShared();
		jvo->code = 9999;
		jvo->message = "Excel parsing failed: " + std::string(e.what());
		jvo->data = {};
		return jvo;
	}

	if (rows.empty() || rows.size() < 2) {
		auto jvo = PersonnelImportJsonVO::createShared();
		jvo->code = 9999;
		jvo->message = "Excel does not contain a sheet named 'people' or the 'people' sheet is empty";
		jvo->data = {};
		return jvo;
	}
	
	//转换数据	
	oatpp::List<PersonnelImportDTO::Wrapper> peoplelist = oatpp::List<PersonnelImportDTO::Wrapper>::createShared();
	for (int i = 1; i < rows.size(); i++) {
		auto dto = PersonnelImportDTO::createShared();
		dto->name = rows[i][0];
		dto->py = "";
		dto->number = rows[i][1];
		dto->frame = rows[i][2];
		if (rows[i][3] == u8"男") {
			dto->sex = (int8_t)1;
		}else if (rows[i][3] == u8"女") {
			dto->sex = (int8_t)0;
		}
		else {
			dto->sex = (int8_t)-1;
		}
		dto->tel = rows[i][4];
		dto->add = rows[i][5];
		dto->card = rows[i][6];
		dto->data = rows[i][7];
		dto->more = "";
		peoplelist->push_back(dto);
	}

	// 定义一个Service
	PersonnelService service;
	PeopleImportReportDTO::Wrapper result = service.importPeopleFromExcel(peoplelist);

	// 5 响应结果
	auto jvo = PersonnelImportJsonVO::createShared();
	jvo->code = 10000;
	jvo->message = "Successfully imported " + std::to_string(result->success) + " personnel records, failed to import " + std::to_string(result->failed) + " personnel records";
	jvo->data = result;
	return jvo;
}
