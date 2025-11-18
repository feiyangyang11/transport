#include "SystemService.h"

oatpp::Vector<SystemDTO::Wrapper> SystemService::listAll() {
	SystemDAO systemDO;
	list<PtrSystemDO> result = systemDO.selectAllSys();
	auto vectorData = oatpp::Vector<SystemDTO::Wrapper>::createShared();
	for (auto& item : result) {
		auto dto = SystemDTO::createShared();
		dto->id = item->getId();
		dto->info = item->getInfo();
		dto->name = item->getName();
		dto->remark = item->getRemark();
		vectorData->emplace_back(dto);
	}
	return vectorData;
}

oatpp::Int32 SystemService::updateById(const oatpp::Vector<SystemDTO::Wrapper>& data) {
	SystemDAO systemDO;
	list<PtrSystemDO> datas;
	for (auto &one : (*data)) {
		auto dos = std::make_shared<SystemDO>();
		dos->setId(one->id);
		dos->setInfo(one->info);
		dos->setName(one->name);
		dos->setRemark(one->remark);
		datas.push_back(dos);
	}
	oatpp::Int32 result = systemDO.updateById(datas);
	return oatpp::Int32(result);
}
