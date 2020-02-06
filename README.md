# 42 minishell

*Authors :*
* Martin Claudel https://github.com/yorncl
* Théo Videira https://github.com/TheoVideira

## Architecture du projet
***

Lorsque ___./minishell___ est lancé, il doit afficher un prompt en l'attente d'une commande 

Format commande:
```
nom_commande arg1 arg2 ... argn < fichier_entrée > fichier sortie
```
Une commande peut recevoir soit des argument et/ou une entrée (avec la redirection "<" ou un autre prompt shell (ex: cat )) 
et ou/une une redirection (">") de la sortie vers un autre fichier. Par défaut la sortie se fait sur le prompt du shell