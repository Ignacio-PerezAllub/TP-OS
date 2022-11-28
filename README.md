# TP-OS
Labo OS

Le but du labo OS est d’explorer les fondements d’un système d’exploitation multitâche simple pour ARM en
le réalisant soi-même (do it yourself :-)
La cible matérielle est une carte LPC55S69-EVK. L’ensemble du code s’exécutera sur le Corex-M33 Core 0 du
microcontrôleur LPC55S69 de NXP.
Le logiciel fait apparaître une organisation en deux parties :
• Le code applicatif qui s’exécute en mode Thread unprivileged.
∗ Plusieurs tâches (processus) peuvent s’exécuter en pseudo-parallèle.
∗ L’accès de la couche applicative aux services du système d’exploitation (création de tâche, de
sémaphore, …) se fait via les appels systèmes (SVC = SuperVisor Call).
∗ Les interruptions sont autorisées.
• Le système d’exploitation composé :
∗ du noyau qui s’exécute en mode Handler (privileged)
– Il offre derrière les appels systèmes une gestion des tâches et des sémaphores, ainsi que le
moyen de démarrer la commutation des tâches. Les SVC sont non interruptibles par les IRQ
des périphériques.
– Il gère la commutation de tâches sur interruption du timer système en mode tourniquet
(round-robin) ou sur des évènements liés à l’utilisation des sémaphores ou de la fonctionnalité de
temporisation. Il décide de la tâche applicative qui peut utiliser le processeur à un instant donné.
∗ d’une couche driver qui s’exécute en mode Thread unprivileged qui permet de la communication
entre la partie applicative et le matériel à travers une interface standard. On s’appuie sur les outils
de synchronisation fournis par le noyau (sémaphores) pour offrir un fonctionnement adéquat, que le
périphérique fonctionne sur interruption ou pas.
TP OS ARM 1/ 12
Lors de l’appel de la fonction main, le processeur se trouve en mode Thread privilégiés avec msp comme
pointeur de pile. Les IRQ des périphériques sont inhibées. Seules les SVC sont autorisées. Une initialisation
minimale du système a été effectuée.
Le projet est géré (génération du makefile, du script de l’éditeur de lien, des fichiers à compiler) par l’IDE
MCUXpresso de NXP (un clône d’Eclipse). Le répertoire du projet est organisé de la manière suivante (je
n’insiste que sur les fichiers importants pour le projet) :
/répertoire racine du projet/
 +- board/ : config du microcontrôleur effectuée avant l’entrée
 | dans le «main»
 +- CMSIS/ : couche d’abstraction du processeur [source : ARM]
 +- device/
 | +- LPC55S69_cm33_core0.h : définition des IRQn, structures des périphériques
 | +- target.[ch] : drivers au niveau OS
 | +- vfs.[ch] : interface générique de drivers OS
 +- drivers/ : drivers de bas niveau du microcontrôleur
 +- kernel/
 | +- kernel.[ch] : code du noyau
 | +- list.[ch] : implémentation de listes circulaires
 +- startup/
 | +- startup_lpc55s69_cm33_core0.c : code de startup, table des vecteurs
 | +- svc.s : SVC_Handler et PendSV_Handler
 |
 | C O D E S Y S T E M E
 | --------------------------------------------------------------------------------------
 | C O D E U T I L I S A T E U R
 |
 +- source/
 +- oslib.[ch] : bibliothèque d’appels systèmes
 +- main.c : code applicatif
Le système sera construit de manière progressive : le fichier source/main.c est subdivisé en plusieurs parties
encapsulés dans les macros #ifdef …#endif. Chaque partie contient un exemple de code applicatif utilisé pour
tester la mise en œuvre d’une fonctionnalité de l’OS en cours de développement. On choisit le programme de
test en définissant avec un#define, en haut du fichier main.c, le label correspondant à la partie qu’on souhaite
inclure dans la compilation.
Les différents labels sont :
MAIN_TEST : test de la mécanique d’un appel système
MAIN_EX1 : test de la mise en route de la première tâche et de la commutation de tâche
MAIN_EX2 : idem, mais toutes les tâches exécutent le même code
MAIN_EX3 : test d’un sémaphore
MAIN_EX4 : exemple d’utilisation d’un sémaphore comme mutex
MAIN_EX5 : test de la fonctionnalité de temporisation
MAIN_EX6 : idem, mais 2 tâches temporisées
MAIN_EX7 : test de la terminaison d’une tâche
MAIN_EX8 : test de l’interface virtuelle de fichiers
MAIN_EX9 : la led RGB comme périphérique
MAIN_EX10 : le bouton USR comme périphérique avec la gestion de l’appui sur interruption