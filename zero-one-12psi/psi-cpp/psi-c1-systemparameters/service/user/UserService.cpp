
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/19 16:19:31

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
#include "UserService.h"
#include "id/UuidFacade.h"
#include "dao/user/UserDAO.h"
#include "NacosClient.h"
#include "Macros.h"
#include"../../../lib-common/include/bcrypt/bcrypt.h"
using namespace oatpp;


std::string UserService::getDfsServerAddrssUrl()
{
	/** 定义一个Nacos客户端对象，用于获取配置 */
	NacosClient _ns(ServerInfo::getInstance().getNacosAddr(), ServerInfo::getInstance().getNacosNs());
#ifdef LINUX
	/** 读取配置数据节点 */
	auto _thirdServerConfig = _ns.getConfig("third-services.yaml");
#else
	/** 读取配置数据节点 */
	auto _thirdServerConfig = _ns.getConfig("./conf/third-services.yaml");
#endif
	return "http://" + YamlHelper().getString(&_thirdServerConfig, "fastdfs.nginx-servers") + "/";
}

UserPageDTO::Wrapper UserService::listAll(const UserQuery::Wrapper& query)
{
	// 定义一个分页对象
	auto page = UserPageDTO::createShared();
	page->pageIndex = query->pageIndex;
	page->pageSize = query->pageSize;

	// 获取数据总条数
	UserDAO ud;
	auto count = ud.count(query);
	if (count <= 0)
		return page;
	page->total = count;
	page->calcPages();

	// 获取文件服务器地址
	std::string urlPrefix = getDfsServerAddrssUrl();
	// 获取分页数据
	auto list = ud.selectAll(query);
	for (auto one : list)
	{
		auto user = UserDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO_1(user, one, name, Name,tel, Tel, frame, Frame, role, Role, user,User, data, Data, id, Id);
		page->addData(user);
	}
	return page;
}

std::string UserService::saveUser(const UserAddDTO::Wrapper& dto)
{
	// 生成唯一标识
	UuidFacade uf;
	auto id = uf.genUuid();

	// 数据转换
	UserDO udo;
	udo.setId(id);
	ZO_STAR_DOMAIN_DTO_TO_DO(udo, dto, Name, name, Py, py, Tel, tel, Frame, frame, Role, role, User,user, Img, img, Data, data, More, more);

	// 保存数据
	UserDAO ud;
	if (ud.insert(udo)) return id;
	return "";
}

UserDetailDTO::Wrapper UserService::getUserDetail(const oatpp::String& id)
{
	// 获取用户主数据
	UserDAO ud;
	auto data = ud.selectById(id.getValue(""));
	if (!data)
		return nullptr;
	auto dto = UserDetailDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, data,name, Name,tel, Tel, frame, Frame, id, Id, role, Role, user,User,img, Img, data, Data);
	if (data->getFile())
	{
		dto->imgUrl = getDfsServerAddrssUrl() + data->getFile()->getSavePath();
	}
	// 返回数据
	return dto;
}

bool UserService::checkUserExists(const String& user) {
	UserDAO ud;
	return ud.countByColumn("user", std::string(user->c_str())) != nullptr;
	//return true;
}
bool UserService::checkTelExists(const String& tel) {
	UserDAO ud;
	return ud.countByColumn("tel", std::string(tel->c_str())) != nullptr;
	//return true;
}
bool UserService::checkFrameExists(const String& frame) {
	UserDAO ud;
	return ud.countByColumn("frame", std::string(frame->c_str()))!= nullptr;
	//return true;
}
bool UserService::checkRoleExists(const String& role) {
	UserDAO ud;
	return ud.countByColumn("role", std::string(role->c_str()))!= nullptr;
	//return true;
}

bool UserService::checkIdExists(const String& id) {
	UserDAO ud;
	return ud.countByColumn("id", std::string(id->c_str()))!= nullptr;
	//return true;
}

// 宏定义：参数为字段名（如 img），自动处理 dto->字段 到 udo->set字段 的赋值
#define SET_FIELD_IF_NOT_EMPTY(field, Field) \
    do { \
        if ((dto)->field == nullptr || (dto)->field->empty()) { \
            (udo)->set##Field(""); \
        } else { \
            (udo)->set##Field((dto)->field->c_str()); \
        } \
    } while(0)
//自动检查密码是否为空，非空则加密
#define SET_PWD_IF_NOT_EMPTY(pwd) \
    do { \
        if ((dto)->pwd == nullptr || (dto)->pwd->empty()) { \
            (udo)->setPwd(""); \
        } else { \
            std::string hash = bcrypt::generateHash((dto)->pwd->c_str()); \
            (udo)->setPwd(hash); \
        } \
    } while(0)

String UserService::addUser(const UserAddDTO::Wrapper& dto) {
	PtrUserDO udo=std::make_shared<UserDO>();
	//必填字段
	udo->setName(dto->name->c_str());
	udo->setPy(dto->py->c_str());
	udo->setTel(dto->tel->c_str());
	udo->setFrame(dto->frame->c_str());
	udo->setRole(dto->role->c_str());
	udo->setUser(dto->user->c_str());

//--------这俩字段不归我们管理，所以随便填值了-------//
	udo->setToken("");
	udo->setExpire(0);
//--------这俩字段不归我们管理，所以随便填值了-------//

	//非必填字段，检查是否为空，空则填默认值
	//非空密码需要加密
	SET_PWD_IF_NOT_EMPTY(pwd);
	SET_FIELD_IF_NOT_EMPTY(img, Img);
	SET_FIELD_IF_NOT_EMPTY(data, Data);
	SET_FIELD_IF_NOT_EMPTY(more, More);
	//头像
	/*if (dto->img == nullptr || dto->img->empty()) {
		udo->setImg("");
	}
	else {
		udo->setImg(dto->img);
	}*/
	//备注
	//if (dto->data == nullptr || dto->data->empty()) {
	//	udo->setData("");
	//}
	//else {
	//	udo->setData(dto->data);
	//}
	////更多信息
	//if (dto->more == nullptr || dto->more->empty()) {
	//	udo->setMore("");
	//}
	//else {
	//	udo->setMore(dto->more);
	//}
	//自动生成ID
	UuidFacade uf;
	auto id = uf.genUuid();
	udo->setId(id);
	//操作数据库
	UserDAO ud;
	if(ud.insertOne(udo)) {
		//cout << "successfully insert" << endl;
		return oatpp::String(id);
	}
	return "";
}
bool UserService::modUser(const UserModDTO::Wrapper& dto) {
	PtrUserDO udo = std::make_shared<UserDO>();
	//将dto中的数据复制到udo中
	udo->setId(dto->id->c_str());
	udo->setName(dto->name->c_str());
	udo->setPy(dto->py->c_str());
	udo->setTel(dto->tel->c_str());
	udo->setFrame(dto->frame->c_str());
	udo->setRole(dto->role->c_str());
	udo->setUser(dto->user->c_str());
	//若密码不为空，则加密密码
	if (!dto->pwd->empty()) {
		std::string hash = bcrypt::generateHash(dto->pwd->c_str());
		udo->setPwd(hash);
	}
	else {
		udo->setPwd(dto->pwd->c_str());
	}
	udo->setImg(dto->img->c_str());
	udo->setData(dto->data->c_str());
	udo->setMore(dto->more->c_str());
	UserDAO ud;
	return ud.updateOne(udo);
}

bool UserService::delUser(const String& id) {
	UserDAO ud;
	return ud.deleteOneById(string(id->c_str()));
}
