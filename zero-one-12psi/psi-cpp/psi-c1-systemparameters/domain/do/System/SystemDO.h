
































/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2023/10/13 21:38:24

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

#include "../DoInclude.h"

#ifndef _SYSTEMDO_H_
#define _SYSTEMDO_H_



class SystemDO : public BaseDO {
private:
    MYSQL_SYNTHESIZE(string, id, Id);      // 去掉引号
    MYSQL_SYNTHESIZE(string, name, Name);
    MYSQL_SYNTHESIZE(string, info, Info);
    MYSQL_SYNTHESIZE(string, remark, Remark);
public:
    SystemDO() : BaseDO("sys") {
        MYSQL_ADD_FIELD_PK("id", "s", id);      // 用小写
        MYSQL_ADD_FIELD("info", "s", info);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("data", "s", remark);
    }
};

typedef std::shared_ptr<SystemDO> PtrSystemDO;

#endif // !_SYSTEMDO_H_