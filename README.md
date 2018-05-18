# Simulation du système solaire séquentiel et parallèle

## Description

Ce projet vise à produire des simulations séquentielles et parallèles
sur l'évolution d'un système solaire. Une analyse complète des 
résultats obtenus est incluse dans le fichier `analyse.pdf`. 

## Auteur

Alexis Chrétien

## Dépendances

[Bibliothèque TBB d'Intel](https://www.threadingbuildingblocks.org)
[GnuPlot](http://www.gnuplot.info/)

## Utilisation

Compilation :
```
$ make
```
Tests (vérification que la simulation séquentielle retourne les mêmes résultats
que la simulation parallèle) :
```
$ make tests
```
Mesures (comparaisons des temps d'exécutions pour différentes nombres de threads
utilisés et production de graphes):
```
$ make mesures
```
Orbites (produire le tracés des orbites de notre système solaires en utilisants
des données réelles)
```
$ make orbites
```
