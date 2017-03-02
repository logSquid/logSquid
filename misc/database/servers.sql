CREATE TABLE `servers` (
  `id` int(12) NOT NULL AUTO_INCREMENT,
  `ipaddr` varchar(16) NOT NULL,
  `name` varchar(50) DEFAULT NULL,
  `start_session` timestamp NULL,
  `last_activity` timestamp NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT COLLATE=latin1_general_cs;
