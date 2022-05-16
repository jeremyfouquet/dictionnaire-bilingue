**Ce projet est réalisé dans le cadre de la licence 2 Informatique de l'IED Paris 8**

**1**
**Analyse des données d'un dictionnaire Japonais-Francais**


**1.1 Fabrication de l’échantillon

明白 [めいはく] /(adj-na)(n)(uk) clair/évident/1000220
あっさり /(adv)(n) facilement/simplement/rapidement/carrément/1000360
あっち /(n)(col) là-bas/1000380
あの人 [あのひと] /lui/elle/cette personne/1000440
あれ /(int)(n) çà/celui-là//(X)(col) organes génitaux//règles/menstruation/1000580
いらっしゃいませ /bienvenue ! (magasins, restaurants, etc) (litt. entrez!)/1000930
うろうろ /(adv)(n)(vs) rôder/flâner/traîner/marcher sans but/1001060
ええ /(conj)(int)(n) oui/1001140
お宅 [おたく] /(n)(pol) votre maison/vous/1002400

**1.2 Parenthésage :

Simplement ligne par ligne

( ( 明白 [めいはく] /(adj-na)(n)(uk) clair/évident/1000220)
  (あっさり /(adv)(n) facilement/simplement/rapidement/carrément/1000360)
  (あっち /(n)(col) là-bas/1000380)
  (あの人 [あのひと] /lui/elle/cette personne/1000440)
  (あれ /(int)(n) çà/celui-là//(X)(col) organes génitaux//règles/menstruation/1000580)
  (いらっしゃいませ /bienvenue ! (magasins, restaurants, etc) (litt. entrez!)/1000930)
  (うろうろ /(adv)(n)(vs) rôder/flâner/traîner/marcher sans but/1001060)
  (ええ /(conj)(int)(n) oui/1001140)
  (お宅 [おたく] /(n)(pol) votre maison/vous/1002400) )

Japonais - Français - identifiant : 

( (( 明白 [めいはく]) (/(adj-na)(n)(uk) clair/évident)(/1000220))
  ((あっさり) (/(adv)(n) facilement/simplement/rapidement/carrément)(/1000360))
  ((あっち) (/(n)(col) là-bas)(/1000380))
  ((あの人 [あのひと]) (/lui/elle/cette personne)(/1000440))
  ((あれ) (/(int)(n) çà/celui-là//(X)(col) organes génitaux//règles/menstruation)(/1000580))
  ((いらっしゃいませ) (/bienvenue ! (magasins, restaurants, etc) (litt. entrez!))(/1000930))
  ((うろうろ) (/(adv)(n)(vs) rôder/flâner/traîner/marcher sans but)(/1001060))
  ((ええ) (/(conj)(int)(n) oui)(/1001140))
  ((お宅 [おたく]) (/(n)(pol) votre maison/vous)(/1002400)) )
 
En conclusion de cette étape la structure final d’une ligne serait la suivante:
( (Japonais) (/Français) (/identifiant) )

Ici le caractère ‘/’ aura un rôle important dans la séparation des éléments de la chaîne. 

const char separateur = '/' ;

**1.3 Détailler la forme à traduire :

( ((明白) ([めいはく])) 
((あっさり)) 
((あっち)) 
((あの人) ([あのひと])) … )
 
((“Japonais”) (“[Japonais]”)) 

Ici le caractère ‘[’ aura un rôle important pour distinguer la deuxième forme Japonaise du mot.

const char crochet = '[';

**2**

**Réalisation d'une maquette d’un programme de traduction en Python** 

(cf code python)

**3**
**Portage de la maquette Python en C, en utilisant une interface rudimentaire (scanf pour lire le mot à traduire, printf pour écrire la traduction)**

(cf code C)


