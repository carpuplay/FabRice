![FabRice Banner](https://github.com/carpuplay/FabRice/blob/main/Assets/banner.png)
(La Phase 1 de développement a été financé par la CVEC)

# FabRice ![Distribution](https://img.shields.io/badge/Distribution-v0.3_alpha-red) ![Workflow](https://img.shields.io/badge/See%20our%20Workflow-black?logo=notion&link=https%3A%2F%2Fwww.notion.so%2Fteam%2F02e4a775-5faf-4f9c-b3c9-5d9b888db163%2Fjoin) ![PCB](https://img.shields.io/badge/PCB-darkblue?logo=Kicad)

<p style="color:darkblue">FabRice est un projet open-source développé par une équipe d'étudiants de l'Université UT3 Paul Sabatier. Il s'agit d'un robot modulaire autonome actuellement en phase 1 de développement sur un total de 3 phases. FabRice est créé à partir de zéro, avec la majorité de ses composants et pièces conçus sur mesure. Notre objectif principal est d'apprendre à rechercher, créer, penser et appliquer des connaissances dans un projet réel.</p>

## <span style="color:darkred">Objectifs de la Phase 1</span>

La Phase 1 de développement de FabRice se concentre sur les objectifs suivants :

- **Contrôle Manuel :** Développer un robot qui peut être contrôlé manuellement.
- **Modularité :** Concevoir le robot pour qu'il puisse intégrer des modules d'amélioration à l'avenir.
- **Ordinateurs de Bord :** Intégrer des ordinateurs de bord capables de gérer des capteurs futurs.
- **Motorisation :** Créer un système de motorisation efficace et adapté aux spécifications du projet.
- **Châssis :** Développer un châssis conforme aux spécifications nécessaires pour le robot.
- **Logiciel :** Développer le logiciel nécessaire pour le contrôle et la gestion du robot.

## <span style="color:darkgreen">Composants et Conception</span>

### <span style="color:darkorange">Matériel</span>

- **[Châssis](https://github.com/carpuplay/FabRice/wiki/Chassis) :** Conçu en CAO et fabriqué avec des imprimantes 3D et des découpeuses laser.
- **[Motorisation](https://github.com/carpuplay/FabRice/wiki/Moteurs) :** Moteurs DC avec réducteurs personnalisés pour obtenir le couple nécessaire.
- **[Électronique](https://github.com/carpuplay/FabRice/wiki/Electronique) :** Inclut tous les circuits et composants électroniques utilisés dans le robot.
- **[Électricité](https://github.com/carpuplay/FabRice/wiki/Electricite) :** Gestion de l'alimentation et des connexions électriques.
- **[PCB](https://github.com/carpuplay/FabRice/wiki/PCB) :** Conçues avec KiCad, elles incluent des contrôleurs de moteur, des régulateurs de tension et des connexions pour capteurs et actionneurs.

### <span style="color:darkorange">Logiciel</span>

- **Plateforme :** Le logiciel principal est écrit en C/C++ pour la compatibilité avec les microcontrôleurs et l'environnement Arduino.
- **Contrôle :** Implémentation d'algorithmes de contrôle basique pour la navigation et le contrôle manuel.
- **Communication :** Utilisation des protocoles I2C et SPI pour la communication entre capteurs et actionneurs.
- **Interface :** Une interface utilisateur sera développée dans les phases futures pour faciliter l'interaction avec le robot.

## <span style="color:darkred">Installation</span>

### <span style="color:darkgreen">Prérequis</span>

- **Arduino IDE :** Assurez-vous d'avoir la dernière version de l'IDE Arduino installée.
- **Bibliothèques nécessaires :** Installez les bibliothèques nécessaires depuis le gestionnaire de bibliothèques de l'IDE Arduino.

```bash
# Cette partie est encore en développement.
Arduino IDE > Sketch > Include Library > Manage Libraries > Rechercher et installer :
- Adafruit Motor Shield
- Wire
- SPI
```

### <span style="color:darkgreen">Instructions</span>

1. Clonez le dépôt :

```bash
git clone https://github.com/carpuplay/FabRice.git
```

2. Ouvrez le projet dans l'IDE Arduino et sélectionnez la carte et le port corrects :

```bash
Arduino IDE > Tools > Board > Sélectionnez votre carte
Arduino IDE > Tools > Port > Sélectionnez le port correspondant
```

3. Téléversez le code dans le microcontrôleur :

```bash
Arduino IDE > Sketch > Upload
```

## <span style="color:darkred">Utilisation (Expected) </span>

1. **Allumez le robot :** Connectez la batterie et allumez l'interrupteur principal.
2. **Contrôle manuel :** Utilisez le contrôleur à distance pour manipuler le robot. Assurez-vous que le robot se trouve dans une zone sécurisée pour l'opération.
3. **Intégration de modules :** Connectez et configurez les modules supplémentaires au fur et à mesure de leur développement.

## <span style="color:darkgreen">Contribuer</span>

Nous sommes ouverts aux contributions ! Si vous souhaitez contribuer à FabRice, veuillez suivre ces étapes :

1. **Fork ce dépôt**
2. **Créez une nouvelle branche** (`git checkout -b feature/nouvelle-fonctionnalité`)
3. **Commitez vos changements** (`git commit -m 'Ajouter une nouvelle fonctionnalité'`)
4. **Push à la branche** (`git push origin feature/nouvelle-fonctionnalité`)
5. **Ouvrez une pull request**

## <span style="color:darkred">Documentation et Ressources</span>

- **Workflow :** [Notre Workflow sur Notion](https://www.notion.so/team/02e4a775-5faf-4f9c-b3c9-5d9b888db163/join)
- **Schémas de PCB :** Les schémas de PCB sont conçus avec KiCad et sont disponibles dans ce dépôt.
- **Guide de l'utilisateur et FAQ :** Bientôt disponible.

## <span style="color:darkgreen">Licence</span>

Ce projet est sous licence MIT. Consultez le fichier [LICENSE](LICENSE) pour plus de détails.

## <span style="color:darkred">Contact</span>

Si vous avez des questions ou des suggestions, n'hésitez pas à ouvrir un issue ou à nous contacter directement.
