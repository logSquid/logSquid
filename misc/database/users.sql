CREATE TABLE `users` (
  `id` int(255) NOT NULL AUTO_INCREMENT,
  `username` varchar(50) NOT NULL,
  `password` varchar(256) NOT NULL,
  `nickname` varchar(50) DEFAULT NULL,
  `theme` varchar(10) NOT NULL,
  `hashCode` text,
  PRIMARY KEY (`id`),
  KEY `id` (`id`)
) ENGINE=InnoDB DEFAULT COLLATE=latin1_general_cs;

