/*
@author: AC
@date:2025/10/17
@file:PeriodDAO.cpp
*/

#include "PeriodDAO.h"
#include "SimpleDateTimeFormat.h"
#include "domain/dto/period/PeriodDTO.h"
#include "domain/do/period/PeriodDO.h"


// 向数据库插入结账信息
bool PeriodDAO::insertPeriod(const PeriodDO& periodDO) {
    string id = periodDO.getId();
    string date = periodDO.getDate();
    string time = periodDO.getTime();
    string user = periodDO.getUser();
    // 校验核心字段非空
    if (id.empty() || date.empty() || time.empty() || user.empty()) {
        return false;
    }
    char sqlBuffer[1024] = { 0 };
    string sqlTemplate = "INSERT INTO `period` (`id`,`date`,`time`,`user`) VALUES('%s','%s','%s','%s')";
    snprintf(
        sqlBuffer,
        sizeof(sqlBuffer),
        sqlTemplate.c_str(),
        id.c_str(),
        date.c_str(),
        time.c_str(),
        user.c_str()
    );
    // 2. 获取数据库会话并执行 SQL
    SqlSession* session = getSqlSession();
    int affectedRows = session->executeUpdate(sqlBuffer); // 执行插入，返回受影响行数
    return affectedRows > 0; // 受影响行数 >0 表示插入成功
}



// 查询该日期是否已有结账记录
bool PeriodDAO::existsByDate(const std::string& date) {
    if (date.empty()) {
        std::cerr << "PeriodDAO::existsByDate: 结账日期为空，无需查询" << std::endl;
        return false;
    }

    const std::string sql = "SELECT COUNT(*) FROM `period` WHERE `date` = ?";

    try {
        // 3. 获取数据库会话
        SqlSession* session = getSqlSession();
        if (session == nullptr) {
            throw std::runtime_error("获取数据库会话失败");
        }

        // 4. 构造参数列表（用 SqlSession 提供的 SQLPARAMS_PUSH 宏，确保参数类型匹配）
        SqlParams params;
        // 宏说明：SQLPARAMS_PUSH(参数集, 参数类型, 数据类型, 参数值)
        // "s" 表示字符串类型（对应 SqlSession 中 SQL_PARAM_SETTING2 的 "s" 分支）
        SQLPARAMS_PUSH(params, "s", std::string, date);

        // 5. 调用 executeQueryNumerical 查询记录数（专门查 COUNT(*) 这类数值）
        // 该方法返回查询到的数值（此处为记录数），无结果时返回 0
        uint64_t recordCount = session->executeQueryNumerical(sql, params);

        // 6. 结果判断：记录数 > 0 表示“已存在”，否则“不存在”
        return recordCount > 0;

    }
    catch (const std::exception& e) {
        // 7. 异常处理：捕获数据库异常（如连接超时、SQL 错误），返回“不存在”并打印日志
        std::cerr << "PeriodDAO::existsByDate 异常: " << e.what() << ", 日期: " << date << std::endl;
        return false;
    }
}

bool PeriodDAO::insertLog(const PeriodDO& periodDO, const string& info) {
    string id = periodDO.getId();
    string time = periodDO.getTime();
    string user = periodDO.getUser();
    // 校验核心字段非空
    if (id.empty() || time.empty() || info.empty() || user.empty()) {
        std::cerr << "insertLog: 参数为空" << std::endl;
        return false;
    }

    // 1. 用参数化 SQL（? 占位符）
    const std::string sql = "INSERT INTO `log` (`id`,`time`,`user`,`info`) VALUES (?, ?, ?, ?)";

    try {
        // 2. 构造参数列表
        SqlParams params;
        SQLPARAMS_PUSH(params, "s", std::string, id);     // id
        SQLPARAMS_PUSH(params, "s", std::string, time);   // time（datetime格式字符串）
        SQLPARAMS_PUSH(params, "s", std::string, user);   // user
        SQLPARAMS_PUSH(params, "s", std::string, info);   // info

        // 3. 执行参数化插入
        SqlSession* session = getSqlSession();
        if (session == nullptr) {
            throw std::runtime_error("insertLog: 获取会话失败");
        }
        int affectedRows = session->executeUpdate(sql, params);
        if (affectedRows <= 0) {
            std::cerr << "insertLog: 插入失败，受影响行数为0" << std::endl;
            return false;
        }
        return true;

    }
    catch (const std::exception& e) {
        // 打印异常信息（关键：可直接看到数据库返回的错误原因）
        std::cerr << "insertLog 数据库异常: " << e.what()
            << ", id=" << id << ", time=" << time << std::endl;
        return false;
    }
}


std::string PeriodDAO::getLatestPeriodDate() {
    // 1. 方法内定义 mapper 结构体，关键：mapper 函数声明为 const 成员
    struct LatestDateMapper {
        // 核心修正：在函数后添加 const，允许被 const 对象调用
        std::string mapper(ResultSet* res) const {
            if (res == nullptr) {
                return "";
            }
            return res->getString("latest_date");
        }
    };

    const std::string sql = "SELECT MAX(`date`) AS latest_date FROM `period`";

    try {
        SqlSession* session = getSqlSession();
        if (session == nullptr) {
            throw std::runtime_error("获取数据库会话失败");
        }

        SqlParams params;
        LatestDateMapper dateMapper;

        // 2. 此时 const 引用的 mapper 可正常调用 const 成员函数
        std::string latestDate = session->executeQueryOne<std::string>(
            sql,
            dateMapper,
            params
        );

        return latestDate;

    }
    catch (const std::exception& e) {
        std::cerr << "PeriodDAO::getLatestPeriodDate 异常: " << e.what() << std::endl;
        return "";
    }
}

// 删除指定日期的结账记录（按 insertPeriod/existsByDate 风格：参数校验→参数化SQL→会话操作→异常处理）
bool PeriodDAO::deletePeriodByDate(const std::string& date) {
    // 1. 参数校验：与 existsByDate 的日期空校验完全一致
    if (date.empty()) {
        std::cerr << "PeriodDAO::deletePeriodByDate: 结账日期为空，无需删除" << std::endl;
        return false;
    }

    // 2. 定义参数化SQL：与 insertLog 的参数化 SQL 风格一致（用 ? 占位符，避免注入）
    const std::string sql = "DELETE FROM `period` WHERE `date` = ?";

    try {
        // 3. 获取数据库会话：与 existsByDate 一致，判空抛出异常
        SqlSession* session = getSqlSession();
        if (session == nullptr) {
            throw std::runtime_error("获取数据库会话失败");
        }

        // 4. 构造参数列表：与 existsByDate/insertLog 的 SQLPARAMS_PUSH 用法完全一致
        SqlParams params;
        SQLPARAMS_PUSH(params, "s", std::string, date); // "s" 对应字符串类型，与 existsByDate 一致

        // 5. 执行删除操作：用 executeUpdate（与 insertPeriod/insertLog 的执行方法一致）
        int affectedRows = session->executeUpdate(sql, params);

        // 6. 结果判断：与 insertPeriod 一致，受影响行数>0 表示删除成功
        if (affectedRows > 0) {
            std::cout << "PeriodDAO::deletePeriodByDate: 日期【" << date << "】的结账记录删除成功" << std::endl;
            return true;
        }
        else {
            std::cerr << "PeriodDAO::deletePeriodByDate: 日期【" << date << "】无对应结账记录，删除失败" << std::endl;
            return false;
        }

    }
    catch (const std::exception& e) {
        // 7. 异常处理：与 existsByDate/insertLog 一致，打印日志+返回失败
        std::cerr << "PeriodDAO::deletePeriodByDate 异常: " << e.what() << ", 日期: " << date << std::endl;
        return false;
    }
}

// 查询总记录数
int64_t PeriodDAO::countAll() {
    SqlSession* session = getSqlSession();
    if (session == nullptr) {
        std::cerr << "countAll: 获取数据库会话失败" << std::endl;
        return 0; // 会话为空时返回0
    }
    const std::string sql = "SELECT COUNT(*) AS total FROM `period`";
    try {
        // 直接调用查询数值的方法，内部无需mapper，返回COUNT(*)的结果
        uint64_t total = session->executeQueryNumerical(sql);
        return static_cast<int64_t>(total);
    }
    catch (const std::exception& e) {
        std::cerr << "countAll 异常: " << e.what() << std::endl;
        return 0; // 异常时返回0
    }
}



// 分页查询记录
/*std::list<PeriodDO> PeriodDAO::queryByPage(int32_t offset, int32_t pageSize) {
    std::list<PeriodDO> resultList;
    SqlSession* session = getSqlSession();
    if (session == nullptr) {
        std::cerr << "queryByPage: 获取数据库会话失败" << std::endl;
        return resultList;
    }

    const std::string sql = "SELECT `id`, `date`, `time`, `user` FROM `period` ORDER BY `id` DESC LIMIT ?, ?";
    PreparedStatement* pstmt = nullptr;
    ResultSet* res = nullptr;

    try {
        // 获取连接并创建预处理语句
        Connection* conn = session->getConnection();
        if (conn == nullptr) {
            throw std::runtime_error("数据库连接为空");
        }
        pstmt = conn->prepareStatement(sql);
        if (pstmt == nullptr) {
            throw std::runtime_error("创建PreparedStatement失败");
        }

        // 设置分页参数
        pstmt->setInt(1, offset);
        pstmt->setInt(2, pageSize);

        // 执行查询
        res = pstmt->executeQuery();
        if (res == nullptr) {
            throw std::runtime_error("执行查询失败，结果集为空");
        }

        // 遍历结果集，移动构造PeriodDO（避免拷贝）
        while (res->next()) {
            PeriodDO period;
            period.setId(res->getString("id"));
            period.setDate(res->getString("date"));
            period.setTime(res->getString("time"));
            period.setUser(res->getString("user"));
            resultList.push_back(std::move(period));  // 移动而非拷贝
        }

    }
    catch (const std::exception& e) {
        std::cerr << "queryByPage 异常: " << e.what() << std::endl;
    }

    // 资源释放（放在try-catch之后，替代finally）
    if (res != nullptr) {
        try { res->close(); }
        catch (...) {}
        delete res;
        res = nullptr;
    }
    if (pstmt != nullptr) {
        try { pstmt->close(); }
        catch (...) {}
        delete pstmt;
        pstmt = nullptr;
    }

    return resultList;
}*/


// 分页查询记录（返回智能指针列表）
std::list<std::unique_ptr<PeriodDO>> PeriodDAO::queryByPage(int32_t offset, int32_t pageSize) {
    std::list<std::unique_ptr<PeriodDO>> resultList;  // 存储智能指针
    SqlSession* session = getSqlSession();
    if (session == nullptr) {
        std::cerr << "queryByPage: 获取数据库会话失败" << std::endl;
        return resultList;
    }

    const std::string sql = "SELECT `id`, `date`, `time`, `user` FROM `period` ORDER BY `id` DESC LIMIT ?, ?";
    PreparedStatement* pstmt = nullptr;
    ResultSet* res = nullptr;

    try {
        Connection* conn = session->getConnection();
        if (conn == nullptr) {
            throw std::runtime_error("数据库连接为空");
        }
        pstmt = conn->prepareStatement(sql);
        if (pstmt == nullptr) {
            throw std::runtime_error("创建PreparedStatement失败");
        }

        // 设置分页参数
        pstmt->setInt(1, offset);
        pstmt->setInt(2, pageSize);

        // 执行查询
        res = pstmt->executeQuery();
        if (res == nullptr) {
            throw std::runtime_error("执行查询失败，结果集为空");
        }

        // 遍历结果集，创建智能指针管理的PeriodDO对象
        while (res->next()) {
            auto period = std::make_unique<PeriodDO>();  // 创建智能指针
            period->setId(res->getString("id"));
            period->setDate(res->getString("date"));
            period->setTime(res->getString("time"));
            period->setUser(res->getString("user"));
            resultList.push_back(std::move(period));  // 移动指针，避免拷贝
        }

    }
    catch (const std::exception& e) {
        std::cerr << "queryByPage 异常: " << e.what() << std::endl;
    }

    // 释放资源
    if (res != nullptr) {
        try { res->close(); }
        catch (...) {}
        delete res;
    }
    if (pstmt != nullptr) {
        try { pstmt->close(); }
        catch (...) {}
        delete pstmt;
    }

    return resultList;
}