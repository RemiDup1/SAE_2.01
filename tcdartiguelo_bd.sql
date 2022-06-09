-- phpMyAdmin SQL Dump
-- version 4.9.2
-- https://www.phpmyadmin.net/
--
-- Hôte : mysql-5.7
-- Généré le :  jeu. 09 juin 2022 à 12:25
-- Version du serveur :  5.7.28
-- Version de PHP :  7.2.25

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données :  `tcdartiguelo_bd`
--

-- --------------------------------------------------------

--
-- Structure de la table `ConnexionChifoumi`
--

CREATE TABLE `ConnexionChifoumi` (
  `id` int(8) NOT NULL,
  `utilisateur` varchar(24) NOT NULL,
  `motdepasse` varchar(24) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `ConnexionChifoumi`
--

INSERT INTO `ConnexionChifoumi` (`id`, `utilisateur`, `motdepasse`) VALUES
(1, 'root', 'root'),
(2, 'thomas', 'thomas');

-- --------------------------------------------------------

--
-- Structure de la table `ScoresChifoumi`
--

CREATE TABLE `ScoresChifoumi` (
  `DateHeure` datetime NOT NULL,
  `NomJoueur` varchar(24) NOT NULL,
  `ScoreJ` int(2) NOT NULL,
  `ScoreM` int(2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `ScoresChifoumi`
--

INSERT INTO `ScoresChifoumi` (`DateHeure`, `NomJoueur`, `ScoreJ`, `ScoreM`) VALUES
('2022-06-09 09:55:40', 'Vous', 5, 3),
('2022-06-09 09:56:10', 'Remi', 5, 9),
('2022-06-09 09:56:36', 'Remi', 8, 4),
('2022-06-09 10:19:25', 'toto', 8, 5),
('2022-06-09 10:20:01', 'toto', 6, 6);

--
-- Index pour les tables déchargées
--

--
-- Index pour la table `ConnexionChifoumi`
--
ALTER TABLE `ConnexionChifoumi`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `ScoresChifoumi`
--
ALTER TABLE `ScoresChifoumi`
  ADD PRIMARY KEY (`DateHeure`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
