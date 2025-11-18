-- Change DataBase
USE `zo_psi`;
SET NAMES utf8mb4;

INSERT INTO `frame` (`id`, `pid`, `name`, `sort`, `data`) VALUES
('0', NULL,	'默认组织', 0, '隐藏组织');

INSERT INTO `category` (`id`, `pid`, `name`, `sort`, `data`) VALUES
('0', NULL,	'默认类别', 0, '隐藏类别');

INSERT INTO `sys` (`id`, `name`, `info`, `data`) VALUES
('e7eb5c8d86594bb6935ffea74aa41176', 'name', '零壹进销存',	'软件名称'),
('f6dd31284c5f492f8682ee2097360796', 'company', '成都零壹科技有限公司', '公司名称'),
('1f2dd2c6ae7e452885fde3a4757b44ae', 'icp', '蜀备000000-0', '备案信息'),
('e82e7abc02384c33ae3752771a581bde', 'notice', '欢迎使用零壹进销存系统\n官网地址：www.01xq.com\n反馈邮箱：ceo@01xq.com', '公告信息'),
('fe945cb2ec084aa3902648be72447aed', 'brand', '[]', '商品品牌'),
('31b7be06795e4f7a9094b622edffcb43', 'unit',	'[]', '计量单位'),
('7ff87eb4d15c4eeaaa1ac8a9a243a080', 'crCategory', '[\"\\u5e38\\u89c4\\u7c7b\\u522b\"]', '客户类别'),
('d40db666b196439bb9415cffbdd7e585', 'crGrade', '[\"\\u5e38\\u89c4\\u7b49\\u7ea7\"]', '客户等级'),
('e185e67b312041d7a4a47f4cd86c0168', 'srCategory', '[\"\\u5e38\\u89c4\\u7c7b\\u522b\"]', '供应商类别'),
('1b1cd30b6d474f529943c10600ac3e88', 'fun', '{\"examine\":false,\"tax\":false,\"rate\":0,\"contain\":false,\"overflow\":false,\"valuation\":\"base\",\"branch\":0,\"rule\":\"def\",\"digit\":{\"nums\":0,\"money\":2},\"days\":\"30\"}', '功能参数'),
('140e79ac85c041c5a727ed112d7cee16', 'logistics', '[{\"key\":\"auto\",\"name\":\"\\u81ea\\u52a8\\u8bc6\\u522b\",\"enable\":true},{\"key\":\"debangwuliu\",\"name\":\"\\u5fb7\\u90a6\\u7269\\u6d41\",\"enable\":true},{\"key\":\"ems\",\"name\":\"\\u90ae\\u653f\\u5feb\\u9012\",\"enable\":true},{\"key\":\"kuaijiesudi\",\"name\":\"\\u5feb\\u6377\\u901f\\u9012\",\"enable\":true},{\"key\":\"quanfengkuaidi\",\"name\":\"\\u5168\\u5cf0\\u5feb\\u9012\",\"enable\":true},{\"key\":\"shentong\",\"name\":\"\\u7533\\u901a\\u901f\\u9012\",\"enable\":true},{\"key\":\"shunfeng\",\"name\":\"\\u987a\\u4e30\\u901f\\u9012\",\"enable\":true},{\"key\":\"tiantian\",\"name\":\"\\u5929\\u5929\\u5feb\\u9012\",\"enable\":true},{\"key\":\"youshuwuliu\",\"name\":\"\\u4f18\\u901f\\u7269\\u6d41\",\"enable\":true},{\"key\":\"yuantong\",\"name\":\"\\u5706\\u901a\\u901f\\u9012\",\"enable\":true},{\"key\":\"yunda\",\"name\":\"\\u97f5\\u8fbe\\u5feb\\u8fd0\",\"enable\":true},{\"key\":\"zhongtong\",\"name\":\"\\u4e2d\\u901a\\u901f\\u9012\",\"enable\":true},{\"key\":\"htky\",\"name\":\"\\u767e\\u4e16\\u5feb\\u9012\",\"enable\":true}]',	'物流配置');

INSERT INTO `user` (`id`, `name`, `py`, `tel`, `frame`, `role`, `user`, `pwd`, `img`, `token`, `expire`, `data`, `more`) VALUES
('5ca75d69600b4c8a907e25282b766d0f', '管理员', 'gly', '18800000000',	'0', '0', 'admin', '$2a$10$K7U.Xolbbz3fGsAzpIawmeQuTWt/W0TXA8DpugqRwWsE0PeRSi1Vu', NULL, NULL, NULL, '管理员', NULL);
