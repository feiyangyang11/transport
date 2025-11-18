#include "stdafx.h"
#include "PersonnelService.h"
#include "dao/Personnel/PersonnelDAO.h"
#include "id/UuidFacade.h"
#include <regex>

PeopleDeleteReportDTO::Wrapper PersonnelService::removePeopleByIds(const oatpp::List<oatpp::String>& ids)
{
	PersonnelDAO dao;
	auto result = PeopleDeleteReportDTO::createShared();
	result->total = ids->size();
	result->succnt = 0;
	result->failed = 0;
	result->details = oatpp::List<PeopleDeleteDetailDTO::Wrapper>::createShared();

	for (auto id : *ids.get()) {
		auto detail = PeopleDeleteDetailDTO::createShared();
		detail->personId = id;
		try {
			bool ok = dao.deleteById(id);
			if (ok) {
				detail->success = true;
				detail->message = u8"删除成功";
				result->succnt = result->succnt + 1;
			}
			else {
				detail->success = false;
				detail->message = u8"id不存在，删除失败";
				result->failed = result->failed + 1;
			}
		}
		catch (const std::exception& e) {
			detail->success = false;
			string s = u8"存在关联数据，无法删除：";
			s += e.what();
			detail->message = s;
			result->failed = result->failed + 1;
		}
		result->details->push_back(detail);
	}
	return result;
}

PeopleImportReportDTO::Wrapper PersonnelService::importPeopleFromExcel(const oatpp::List<PersonnelImportDTO::Wrapper>& dtolist)
{
	int successCnt = 0;
	int failCnt = 0;
	std::vector<PeopleImportErrorDTO::Wrapper> errorList;
	UuidFacade uf(1);
	PersonnelDAO dao;

	int rowIndex = 1;
	for (auto dto : *dtolist) {
		rowIndex++;
		PersonnelFileDO da;

		//生成唯一标识
		std::string id = uf.genUuid();
		da.setId(id);
		// 检查参数是否为空
		//姓名为空
		if (dto->name->empty()) {
			failCnt++;
			auto err = PeopleImportErrorDTO::createShared();
			err->row = rowIndex;
			err->field = "name";
			err->value = dto->name;
			err->message = "name is empty";
			errorList.push_back(err);
			continue; 
		}
		else if ( dto->number->empty()) {//编号为空
			failCnt++;
			auto err = PeopleImportErrorDTO::createShared();
			err->row = rowIndex;
			err->field = "number";
			err->value = dto->number;
			err->message = "number is empty";
			errorList.push_back(err);
			continue; 
		}
		else if (dto->sex == -1) {//性别为空或者格式错误
			failCnt++;
			auto err = PeopleImportErrorDTO::createShared();
			err->row = rowIndex;
			err->field = "sex";
			err->value = std::to_string(dto->sex);
			err->message = "sex is empty or format error";
			errorList.push_back(err);
			continue; 
		}
		else if ( dto->tel->empty()) {//联系电话为空
			failCnt++;
			auto err = PeopleImportErrorDTO::createShared();
			err->row = rowIndex;
			err->field = "tel";
			err->value = dto->tel;
			err->message = "tel is empty";
			errorList.push_back(err);
			continue; 
		}
		else if (dto->frame->empty()) {//所属组织为空
			failCnt++;
			auto err = PeopleImportErrorDTO::createShared();
			err->row = rowIndex;
			err->field = "frame";
			err->value = dto->frame;
			err->message = "frameis empty";
			errorList.push_back(err);
			continue; 
		}
		//编号重复
		if (checkNumberExists(dto->number)) {
			failCnt++;
			auto err = PeopleImportErrorDTO::createShared();
			err->row = rowIndex;
			err->field = "number";
			err->value = dto->number;
			err->message = "number already exists in the database";
			errorList.push_back(err);
			continue; 
		}
		//所属组织frame不存在
		if (!dao.isFrameExist(dto->frame)) {
			failCnt++;
			auto err = PeopleImportErrorDTO::createShared();
			err->row = rowIndex;
			err->field = "frame";
			err->value = dto->frame;
			err->message = "frame does not exist";
			errorList.push_back(err);
			continue;
		}
		 // 检查手机号格式
		std::regex phonePattern(R"(^1[3-9]\d{9}$)");
		if (!std::regex_match(*dto->tel, phonePattern)) {
			failCnt++;
			auto err = PeopleImportErrorDTO::createShared();
			err->row = rowIndex;
			err->field = "tel";
			err->value = dto->tel;
			err->message = "Invalid phone number format";
			errorList.push_back(err);
			continue; 
		}
		// 检查身份证号格式
		std::regex idCardPattern(R"(^\d{17}[\dXx]$)");
		if (!std::regex_match(*dto->card, idCardPattern)) {
			failCnt++;
			auto err = PeopleImportErrorDTO::createShared();
			err->row = rowIndex;
			err->field = "card";
			err->value = dto->card;
			err->message = "Invalid ID card number format";
			errorList.push_back(err);
			continue;
		}
	
		ZO_STAR_DOMAIN_DTO_TO_DO(da, dto, Name, name, Py, py, Number, number, Frame, frame, Sex, sex, Tel, tel, Add, add, Card, card, Data, data, More, more);
		try {
			bool success=dao.insert(da);
			if (success) successCnt++;
			else {
				failCnt++;
				auto err = PeopleImportErrorDTO::createShared();
				err->row = rowIndex;
				err->field = "";
				err->value = "";
				err->message = "insert failed";
				errorList.push_back(err);
			}
		}
		catch (std::exception& e) {
			failCnt++;
			auto err = PeopleImportErrorDTO::createShared();
			err->row = rowIndex;
			err->field = "";
			err->value = "";
			err->message = e.what();
			errorList.push_back(err);
		}
	}
	auto report= PeopleImportReportDTO::createShared();
	report->total = successCnt + failCnt;
	report->success = successCnt;
	report->failed = failCnt;
	report->errors = oatpp::List<PeopleImportErrorDTO::Wrapper>::createShared();
	for (auto& e : errorList) {
		report->errors->push_back(e);
	}
	return report;
}


oatpp::List<PersonnelExportDTO::Wrapper> PersonnelService::exportPeopleToExcel(const oatpp::List<oatpp::String>& ids)
{
	auto list = oatpp::List<PersonnelExportDTO::Wrapper>::createShared();
	PersonnelDAO dao;
	for (auto one : *ids) {
		if (dao.existsById(one)) {//只导出存在的id的信息
			auto dto = PersonnelExportDTO::createShared();
			auto res = dao.selectById(one);
			ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, res,  name, Name,  number, Number, frame, Frame, sex, Sex, tel, Tel, add, Add, card, Card, data, Data );
			list->push_back(dto);
		}
	}
	return list;
}


// 新增人员
oatpp::String PersonnelService::addPersonnel(const PersonnelAddDTO::Wrapper& dto) {
    PersonnelDAO dao;
    UuidFacade uf;

    auto po = std::make_shared<PersonnelFileDO>();
    po->setId(uf.genUuid());
    po->setName(dto->name ? dto->name->c_str() : "");
    po->setPy(""); // 可选，拼音生成逻辑
    po->setNumber(dto->number ? dto->number->c_str() : "");
    po->setFrame(dto->frame ? dto->frame->c_str() : "");
    po->setSex((dto->sex && *dto->sex == u8"男") ? 1 : 0);
    po->setTel(dto->tel ? dto->tel->c_str() : "");
    po->setAdd(dto->add ? dto->add->c_str() : "");
    po->setCard(dto->card ? dto->card->c_str() : "");
    po->setData(dto->data ? dto->data->c_str() : "");
    po->setMore("");

    try {
        if (dao.insert(po)) {
            return po->getId().c_str();
        }
    }
    catch (const std::exception& e) {
        OATPP_LOGE("PersonnelService", "Add personnel failed: %s", e.what());
    }
    return nullptr;
}

// 批量修改人员
bool PersonnelService::modifyPersonnel(const oatpp::List<PersonnelEditDTO::Wrapper>& dtolist)
{
    PersonnelDAO dao;
    bool allSuccess = true;

    for (auto dto : *dtolist) {
        if (!dto->id || dto->id->empty()) {
            OATPP_LOGE("PersonnelService", "Missing ID in modifyPersonnel");
            allSuccess = false;
            continue;
        }

        auto po = std::make_shared<PersonnelFileDO>();
        po->setId(dto->id->c_str());
        po->setName(dto->name ? dto->name->c_str() : "");
        po->setPy("");
        po->setNumber(dto->number ? dto->number->c_str() : "");
        po->setFrame(dto->frame ? dto->frame->c_str() : "");
        po->setSex((dto->sex && *dto->sex == u8"男") ? 1 : 0);
        po->setTel(dto->tel ? dto->tel->c_str() : "");
        po->setAdd(dto->add ? dto->add->c_str() : "");
        po->setCard(dto->card ? dto->card->c_str() : "");
        po->setData(dto->data ? dto->data->c_str() : "");
        po->setMore("");

        try {
            if (!dao.updateById(po)) {
                allSuccess = false;
                OATPP_LOGE("PersonnelService", "Update failed for id=%s", dto->id->c_str());
            }
        }
        catch (const std::exception& e) {
            OATPP_LOGE("PersonnelService", "Exception updating id=%s: %s", dto->id->c_str(), e.what());
            allSuccess = false;
        }
    }

    return allSuccess;
}


// 检查人员编号是否存在
bool PersonnelService::checkNumberExists(const oatpp::String& number)
{
    if (!number || number->empty())
        return false;

    PersonnelDAO dao;
    return dao.existsByNumber(number);
}

// 检查人员组织是否存在
bool PersonnelService::isFrameExist(const oatpp::String& frame) {
	PersonnelDAO dao;
	return dao.isFrameExist(frame);
}



PersonnelListPageDTO::Wrapper PersonnelService::listAll(const PersonnelQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = PersonnelListPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	PersonnelDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<PersonnelFileDO> result = dao.selectWithPage(query);
	// 将DO转换成DTO
	for (PersonnelFileDO& sub : result)
	{
		auto dto = PersonnelListDTO::createShared();
		// ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id, name, Name, py, Py, number, Number, frame, Frame, sex, Sex, tel, Tel, add, Add, card, Card, data, Data);
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id, name, Name, number, Number, frame, Frame, sex, Sex, tel, Tel, add, Add, card, Card, data, Data);
		pages->addData(dto);
	}
	return pages;
}
PersonnelDetailDTO::Wrapper PersonnelService::getById(const oatpp::String& id)
{
	//修改添加下两行代码
	if (!id || id->empty()) return nullptr;
	// 将 oatpp::String 转为 std::string（如果 DAO 需要）
	std::string stdId = std::string(id->c_str(), id->size());


	// 查询数据
	PersonnelDAO dao;
	auto res = dao.selectById(id);

	// 没有查询到数据
	if (!res)
		return nullptr;

	// 查询到数据转换成DTO
	auto dto = PersonnelDetailDTO::createShared();
	// ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, res, id, Id, name, Name, py, Py, number, Number, frame, Frame, sex, Sex, tel, Tel, add, Add, card, Card, data, Data);
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, res, id, Id, name, Name, number, Number, frame, Frame, sex, Sex, tel, Tel, add, Add, card, Card, data, Data);
	return dto;
}



