CREATE TABLE `logSquid` (
  `id` bigint(255) NOT NULL AUTO_INCREMENT,
  `datetime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `ipuser` varchar(15) DEFAULT NULL,
  `macaddress` varchar(17) DEFAULT NULL,
  `username` varchar(50) DEFAULT NULL,
  `destination` varchar(100) DEFAULT NULL,
  `url` varchar(2048) DEFAULT NULL,
  `ipdest` varchar(50) DEFAULT NULL,
  `mime` varchar(50) DEFAULT NULL,
  `size` int(255) DEFAULT NULL,
  `status` varchar(50) DEFAULT NULL,
  `agent` int(16) NOT NULL,
  `server` int(16) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `datetime` (`datetime`),
  KEY `agent` (`agent`),
  KEY `server` (`server`)
) ENGINE=InnoDB DEFAULT COLLATE=latin1_general_ci;
