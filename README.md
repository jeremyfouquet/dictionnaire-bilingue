jeremy fouquet

Listes 6 Dico

1 . analyse des données
    1.1 Fabrication de l’échantillon
    1.2 Parenthésage
    1.3 Détailler la forme à traduire
    1.4 Détailler la traduction
    1.5 Lecture des données

2 . maquette d’un programme de traduction en PYTHON


**1 . analyse des données**

Tout d’abord j’ai décidé de prendre le dictionnaire japonais-français car je n’ai pas trouvé d’autre dictionnaire par moi même, et les autres liens semblaient compromis.

1.1 Fabrication de l’échantillon

明白 [めいはく] /(adj-na)(n)(uk) clair/évident/1000220
あっさり /(adv)(n) facilement/simplement/rapidement/carrément/1000360
あっち /(n)(col) là-bas/1000380
あの人 [あのひと] /lui/elle/cette personne/1000440
あれ /(int)(n) çà/celui-là//(X)(col) organes génitaux//règles/menstruation/1000580
いらっしゃいませ /bienvenue ! (magasins, restaurants, etc) (litt. entrez!)/1000930
うろうろ /(adv)(n)(vs) rôder/flâner/traîner/marcher sans but/1001060
ええ /(conj)(int)(n) oui/1001140
お宅 [おたく] /(n)(pol) votre maison/vous/1002400

J’ai décidé de partir de cet échantillonnage (ci dessus) qui me semble le plus exhaustif possible.
Ici j’observe que les premiers mots entre parenthèses juste après les mots en Japonais représentent la catégorie du mot. A savoir adjectif, nom, verbe … En observant le dictionnaire je me rends compte qu’il y en a beaucoup trop pour les lister exhaustivement.
Je vais donc décider par la suite de ne pas extraire toutes les catégories entre parenthèse pour simplifier l’extraction.

1.2 Parenthésage :

1ere constatation, par ligne dans un premier temps : 
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

2eme constatation, Japonais - Français - identifiant : 
Je reperes dans un premier cas que le Japonais est la première partie de la ligne.
Je reperes dans un deuxième cas que le Français est toujours précédé d’un ‘/’.
Et enfin en dernière partie de la ligne vient l’identifiant de celle ci à 7 chiffre qui commence toujours par “/1”.




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
Je peux dès à présent déclarer et initialiser la constante séparateur:

const char separateur = '/' ;

1.3 Détailler la forme à traduire :

Concernant la partie Japonaise, la forme à traduire peut comprendre un ou 2 mots et s’il y à un deuxième mot celui-ci est toujours entre crochet. Ainsi pour 明白 [めいはく] cela peut s’écrire en forme 1 : 明白 ou bien forme 2 : めいはく
Etant donné que la deuxième forme n’est pas systématique elle pourra être soit renseignée soit à NULL.
Si je doit analyser une ligne Japonaise uniquement cela donnerait : 

( ((明白) ([めいはく])) 
((あっさり)) 
((あっち)) 
((あの人) ([あのひと])) … )

Ce qui peut être traduit par une structure final : 
 
((“Japonais”) (“[Japonais]”)) 

Je peux dès à présent déclarer et initialiser la constante crochet qui me permettra de distinguer la deuxième forme Japonaise du mot:

const char crochet = '[';

 
1.4 Détailler la traduction :

Il peut y avoir plusieurs traductions, séparées par le même séparateur que celui qui sépare le Japonais et le Français à savoir ‘/’.
De plus, il y a une catégorie au début de la traduction qui se trouve entre parenthèses, mais pas systématique. 
Cependant étant donné le nombre incroyable de catégories différentes et le fait qu’il puisse y avoir plusieurs catégories à la fois par traduction je considère que cela rend la chose trop complexe et je préfère supprimer tout ce qui est entre parenthèses si cela vient directement après la première partie de la ligne, donc juste après le premier ‘/’.
On remarque aussi que lorsque ‘/’ apparaît 2 fois la traduction peut avoir un double sens. Cependant puisque qu’une liste chaînée de traductions sera nécessaire de toute façon cela ne change rien et je préfère donc ignorer ce détail inutile. 
À l'exception du fait que lorsqu’il y a une double traduction il peut de nouveau avoir des catégories et cela pose problème. Ainsi je devrais créer une fonction global qui passe sur chaque occurrence de traduction pour nettoyer les catégorie que je ne souhaite pas afficher

Voici ce que cela donnera  sur une échantillon de traduction uniquement :

( … ((/(adj-na)(n)(uk) clair/évident/1000220))
((/(adv)(n) facilement/simplement/rapidement/carrément/1000360))
((/(int)(n) çà/celui-là//(X)(col) organes génitaux//règles/menstruation/1000580))
((/(adj)(exp) ne doit pas faire/1000730))
((/bienvenue ! (magasins, restaurants, etc) (litt. entrez!)/1000930)) …)

Ce qui peut être traduit par une structure final très basique : 
 
((“Français”)) 
 
1.5 Lecture des données :
 
Afin d’avoir l’identifiant plus facile d'accès si l’on souhaite récupérer une traduction par celui ci, je le fait correspondre à la fois dans la partie Japonaise et dans la partie Française.
Pour récupérer l’identifiant rien de plus simple, il suffira de pointer le premier chiffre 1 qui suit un ‘/’.
 
Nous avons donc notre structure de données de base pour l’entrée de dictionnaire qui sera la suivante:

( ((“Japonais” “Second_Japonais” identifiant) 
((“Français” identifiant) (“Français” identifiant) … ))... )

**2 . maquette d’un programme de traduction en PYTHON**
 
Le nom du fichier est dico.utf et le nom de l’échantillon est echantillon.utf. Je n’ai pas développé la possibilité de renseigner le nom du fichier à charger pour les données du dictionnaire puisque cela n’était pas demandé et il n’est pas d’usage dans un dictionnaire en ligne que l’on demande à l’utilisateur de fournir par lui-même son propre fichier de données.
 
J’ai besoin de créer les entrées du dictionnaires pour ce faire je me suis aidé de la source suivante en Python car je n’avai jamais créé de Class en Python (http://python-liesse.enseeiht.fr/cours/structures_donnees.html) :
 
Ainsi pour la définition du type de la partie japonais, j’ai opté pour une Class en Python ce qui est très pratique puisqu’elle a un constructeur intégré ce qui lui évite d’avoir à fabriquer une fonction cons qui sera nécessaire en C :
 
(en Python):
class japonais :
    def __init__(self, form, secondform, id):
        self.form = form
        self.secondform = secondform
        self.id = id
 
(en C):
typedef struct {string form ; string secondform ; int id ;} japonais ;
 
Ce sera la même chose pour la class francais et dictionnaire comme suit :
 
(en Python):
class francais:
    def __init__(self, form, id):
        self.form = form
        self.id = id
​​class dictionnaire:
    def __init__(self, form, traductions):
        self.form = form
        self.traductions = traductions
 
 
(en C):
typedef struct Translate {string form ; int id ; struct Translate * cdr ;} Translate, * francais ;
typedef struct Entry {japonais form ; francais traductions ; struct Entry * cdr ;} Entry, * dictionnaire ; 
 
 
// constructeurs :
francais pushFrancais(string form, int id, francais nouvelEntree) {
    francais new = malloc(sizeof(Translate)) ;
    if (! new) usage("pushFrancais", "cons : manque de RAM") ;
    new -> form = form ;
    new -> id = id;
    new -> cdr = nouvelEntree ;
    return new ;
}
dictionnaire pushTraduction(japonais form, francais traductions, dictionnaire nouvelEntree) {
    dictionnaire new = malloc(sizeof(Entry)) ;
    if (! new) usage("pushTraduction", "cons : manque de RAM") ;
    new -> form = form ;
    new -> traductions = traductions;
    new -> cdr = nouvelEntree ;
    return new ;
}
 
La structure des données étant faites il n’y a plus qu'à construire les différentes fonctions comme suit :
 
lecturedictionnaire // lis le fichier et traduit la lecture en structure pour remplir le dictionnaire japonais_français
recupereFrancais // Traduit la ligne renvoyé par le fichier en liste de une ou plusieurs Class français
recupereJaponais // Traduit la ligne renvoyé par le fichier en une Class japonais
recupereIdentifiant // Traduit la ligne renvoyé par le fichier en identifiant
traduire // choix n° 1 japonais-français
rechercheTraduction // cherche la Class dictionnaire de la liste japonais_français correspondante dont dictionnaire.form == “mot à traduire”
accesFrancais // parcours dictionnaire.traductions et affiche toute les traductions.form
rechercheMot // choix n° 2 français-japonais
rechercheJaponais // cherche la Class dictionnaire de la liste japonais_français correspondante dont dictionnaire.traductions.form contient le “mot à traduire”
accesJaponais  // affiche dictionnaire.form.form et dictionnaire.secondform.form
rechercheId // choix n° 3 recherche par identifiant
rechercheIdentifiant // cherche la Class dictionnaire de la liste japonais_français correspondante dont dictionnaire.id == identifiant
choix  // interface rudimentaire
commencer  // interface rudimentaire
 
Dans la fonction recupereJaponais j’utilise la methode .split(“ “) qui permet de créé une liste de mot pour récupérer les 2 formes japonaise, cependant cette methode n’existe pas en C, j’ai donc trouver cette source (https://waytolearnx.com/2019/09/decouper-une-chaine-de-caractere-en-c.html#:~:text=%5B%5D%20%3D%20%22%20%22%3B-,char%20d%5B%5D%20%3D%20%22%20%22%3B,le%20caract%C3%A8re%20du%20prochain%20mot.)
qui explique comment utiliser la méthode strtok qui fait la même chose.
 
Ainsi la définition en Python:
def recupereFrancais(ligne, identifiant):
    F = list();
    cdr = supprimerCategorie(ligne[ligne.find(separateur)+1:len(ligne)]);
    for mot in cdr.split(separateur):
        if mot[:1] != '1':
            fr = francais(supprimerCategorie(mot), identifiant);
            F.append(fr);
    return F;
 
Deviendra en C:
japonais recupereJaponais(string ligne, int id) {
    japonais J = {};
    pointeur = strtok(strdup(ligne), d);
    while(pointeur != NULL && pointeur[0] != separateur) {
        string mot = strdup(pointeur);
        if(pointeur[0] == crochet1) {
            J.secondform = mot;
        }
        else J.form = mot;
        pointeur = strtok(NULL, d);
    }
    pointeur = NULL;
    J.id = id;
    return J;
}
 
Pour terminer et avant de porter la maquette de ma réalisation de Python vers C je me suis rendu compte que j'avais oublié un point que je vais ajouter dans le code C.
Il s’agit de la recherche d’un mot japonais par son second mot, en effet étant donnée que j’ai conservé les crochets, lors de la comparaisons il ne peut pas y avoir de correspondance, je vais donc devoir trouver une solution pour faire correspondre la recherche pour dictionnaire.form.secondform
