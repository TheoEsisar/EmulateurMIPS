<h1 align="left">Emulateur MIPS - C</h1>

###

<p align="left">Réalisation d'un émulateur MIPS en langage C avec différents modes de fonctionnements</p>

###

<h3 align="left">Mode Automatique</h3>

###

<p align="left">Usage : ./emul-mips PROGRAMME SORTIE_ASSEMBLAGE SORTIE_EXECUTION<br><br>Dans ce mode, PROGRAMME est le nom d’un fichier contenant le programme à exécuter, écrit en assembleur MIPS.<br>L’émulateur ne demande pas à l’utilisateur de saisir du code.<br>SORTIE_ASSEMBLAGE est le nom d’un fichier où sera stocké le programme assemblé (un fichier texte contenant des chaînes hexadécimales),<br>et SORTIE_EXECUTION est le nom d’un fichier où sera stocké l’état final du programme.</p>

###

<h3 align="left">Mode Pas-à-Pas</h3>

###

<p align="left">Usage : ./emul-mips PROGRAMME -pas<br><br>Si l’option -pas est spécifiée, le programme est exécuté pas-à-pas :<br>l’émulateur fait une pause à chaque instruction et l’utilisateur valide le passage à l’instruction suivante dans le terminal.<br>L'état des registres est affiché à chaque éxécution d'une instruction.</p>

###

<h3 align="left">Mode Interactif</h3>

###

<p align="left">Le programme demande à l’utilisateur d’entrer une instruction dans le terminal, l’exécute ;<br>en demande une nouvelle, et ainsi de suite jusqu’à lecture de ”EXIT”.<br>Dans ce mode, il ne sera possible d’exécuter que des instructions en séquence.</p>

###
