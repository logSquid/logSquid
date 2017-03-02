CREATE TABLE `agents` (
  `id` int(255) NOT NULL AUTO_INCREMENT,
  `ipaddr` varchar(16) NOT NULL,
  `name` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT COLLATE=latin1_general_cs;
