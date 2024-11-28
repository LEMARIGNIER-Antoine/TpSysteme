Utilisation du logiciel CLion, très pratique

Q1)
La fonction write s'utilise comme suit :
write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));
avec, au préalable, une définition de WELCOME_MSG :

#define WELCOME_MSG "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"

La fonction read permet de lire la commande de l'utilisateur.
C'est une alternative efficace aux fonctions printf et scanf.

Q2)
Utilisation de fork pour dupliquer un processus. Le parent continue d'exécuter le shell, tandis que le processus enfant exécute fortune.
Attention :
     Toujours vérifier que le processus enfant se termine correctement.
     Ne pas oublier de fermer les processus enfants pour éviter les duplications non contrôlées.

Q3)
Au départ, l'utilisation de break semblait judicieuse, mais elle est insuffisante en cas de plusieurs boucles imbriquées.
La fonction exit(status) (disponible via la bibliothèque stdlib.h) est une solution plus adaptée, car elle permet d'interrompre complètement l'exécution du programme.
