### Bonneville Geoffrey

#### Temps
**Temps estimé**: 10 heures
**Temps passé** : 9 heures

Je suis resté bloqué sur un problème "bête" pendant 3 heures.

#### Remarques
J'ai essayé d'implémenter une hash table assez générique.
Ainsi, une structue object est définie et contient l'id, le noeud de la liste chainée, et un pointeur data qui peut être utilisé librement par l'utilisateur pour y stocker des informations propres à l'objet qui'l manipule.

L'aide du professeur a été une nouvelle fois très utile pour comprendre tous les concepts du sujet.

valgrind est très pratique pour détecter les fuites mémoires.

La fonction de hash implémentée est `id % hashTable->size`.
