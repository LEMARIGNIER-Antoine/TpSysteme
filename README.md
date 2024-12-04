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

Q4) Affichage du code de retour dans le prompt : Utilisation du WIFEXITED(status) et WIFSIGNALED(status) pour afficher le statut exit ou le signal
Pour vérigier si tout fonctionne bien, dans la console : 
enseash % geany
[exit:1]
enseash % Command not found: No such file or directory
gedit
[sign:9]
enseash % 
On voit bien [exit:1] lors de l'exit et pour kill dans le terminal, il faut taper ps -e puis voir le PID de gedit puis faire kill -9 PID et on voit dans la console [sign:9] apparaître.

Q5) Très ressemblante à Q4, on rajoute un start timer, on fait un wait(&status) puis on arrête le timer. On teste de nouveau avec un gedit puis on le kill et on observe le temps : gedit
[sign:9|18200ms]
enseash % 
