-- Change DataBase
USE `zo_psi`;

SET NAMES utf8mb4;

INSERT INTO `dict_type` (`id`, `name`, `code`, `remark`) VALUES 
('61f3bbc90b904b51890448968afc106f', '文件类型', 'file_type', NULL),
('f42afd7d846248528fe72d62c01e9d1e', '文件存储方式', 'save_way', NULL);

INSERT INTO `dict` (`id`, `tid`, `name`, `value`, `remark`) VALUES 
('07cd9e35e50746c4817523c8d4cc046a', 'f42afd7d846248528fe72d62c01e9d1e', 'fastdfs', '10001', 'FastDfs分布式存储'),
('2e2f4fd8dbe64bdc96b879c8f5d927e5', 'f42afd7d846248528fe72d62c01e9d1e', 'disk', '10002', '业务服务器磁盘存储'),
('4b8891f629c24b099bb11f3b444ae82c', 'f42afd7d846248528fe72d62c01e9d1e', 'oss', '10003', '阿里云对象存储'),
('b9112f5abc544150a32f19767f8c0816', 'f42afd7d846248528fe72d62c01e9d1e', 'ftp', '10004', '普通文件服务器'),
('029f4d8bbb014530bbc18df89ae1bc36', '61f3bbc90b904b51890448968afc106f', '用户头像', '10001', NULL),
('e4d9a2ff1fbb4d8e86060e7e4374bba4', '61f3bbc90b904b51890448968afc106f', '商品描述', '10002', NULL),
('e3b89e8b9bea4ea2bf501b8e932ab29c', '61f3bbc90b904b51890448968afc106f', '合同附件', '10003', NULL),
('94d5020775e94f9cadd5c4826ea20a56', '61f3bbc90b904b51890448968afc106f', '发票附件', '10004', NULL),
('4084bbb7e99d4ae5b9d2072f0437f71a', '61f3bbc90b904b51890448968afc106f', '采购订单', '10005', NULL),
('14a9554b3dff4414bc160910c01b8e26', '61f3bbc90b904b51890448968afc106f', '采购单', '10006', NULL),
('7f6f37b1ee474ba9a742150387be2218', '61f3bbc90b904b51890448968afc106f', '采购退货单', '10007', NULL),
('6a04e30465f94a91a7948256f7f2dd68', '61f3bbc90b904b51890448968afc106f', '销售订单', '10008', NULL),
('e25984ef3ef84d849cbe7af577312b8f', '61f3bbc90b904b51890448968afc106f', '销售单', '10009', NULL),
('9eb54f20a9544bbf96dcf12ff990bed7', '61f3bbc90b904b51890448968afc106f', '销售退货单', '10010', NULL),
('901f5e07f0364ddf8a7fa00f5774719e', '61f3bbc90b904b51890448968afc106f', '其他入库单', '10011', NULL),
('793cf11342094defbb586449aa706078', '61f3bbc90b904b51890448968afc106f', '其他出库单', '10012', NULL),
('a77c064624764d04988e8b4022d6b7ca', '61f3bbc90b904b51890448968afc106f', '调拨单', '10013', NULL),
('c9418496cc23426bb34009009c879f4e', '61f3bbc90b904b51890448968afc106f', '收款单', '10014', NULL),
('a12637e811d04370a3660002fa79ada8', '61f3bbc90b904b51890448968afc106f', '付款单', '10015', NULL),
('28f8a872fe6a45b49bc118efcab64a53', '61f3bbc90b904b51890448968afc106f', '核销单', '10016', NULL),
('a513763626f74da399f47bc4c4814d33', '61f3bbc90b904b51890448968afc106f', '转账单', '10017', NULL),
('ac598710482748b8aa5da51c4eb5e55c', '61f3bbc90b904b51890448968afc106f', '其他收入单', '10018', NULL),
('c3a6d08e5cb54d9caa71f1c1f1d8a99b', '61f3bbc90b904b51890448968afc106f', '其他支出单', '10019', NULL);