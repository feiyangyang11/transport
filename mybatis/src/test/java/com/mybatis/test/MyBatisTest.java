package com.mybatis.test;

import com.mybatis.entity.User;
import com.mybatis.mapper.UserMapper;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.junit.Test;

import java.io.IOException;
import java.io.InputStream;

public class MyBatisTest {

    @Test // 这个注解表示这是一个测试方法
    public void testSelectById() throws IOException {
        // 1. 读取MyBatis配置文件
        InputStream inputStream = Resources.getResourceAsStream("mybatis-config.xml");

        // 2. 创建SqlSessionFactory（相当于数据库连接池）
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);

        // 3. 获取SqlSession（相当于数据库连接）
        SqlSession sqlSession = sqlSessionFactory.openSession();

        // 4. 获取Mapper接口的实现类（MyBatis自动生成）
        UserMapper userMapper = sqlSession.getMapper(UserMapper.class);

        // 5. 调用方法查询（查询id=1的用户，也就是我们插入的“张三”）
        User user = userMapper.selectById(1);

        // 6. 打印结果
        System.out.println(user);

        // 7. 关闭连接
        sqlSession.close();
    }
}