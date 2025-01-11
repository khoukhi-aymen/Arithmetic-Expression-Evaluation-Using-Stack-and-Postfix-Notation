#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#define max 100
typedef char chaine[max];
typedef chaine TabChaine[100];

typedef struct TabCh
{
    TabChaine val;
    int taill,b;
}TabCh;

typedef struct CHAIN
{
	chaine ELm;
}CHAIN;

typedef struct noeud* pile;
typedef struct noeud
{
    chaine val;
    pile svt;
}noeud;



pile Cree_noeud();
char* sommet_pile(pile);
CHAIN Depiler(pile*);
int pile_vide(pile);
void Affiche_pile(pile);
void Empile(pile*,chaine);
void Afficher_pile(pile);

int operande(chaine);
int operateur(chaine);
int priorite(chaine);
double operation(chaine,chaine,chaine);

pile postfixe(TabCh);
double Evaluation(pile);

pile Tab_To_pile(TabChaine, int);
int si_paro(char);
int si_opera(char);
int si_oper(char);
TabCh remplicage(chaine);
CHAIN if_blanks(chaine);

int verif_parenthese(chaine);

#endif // FONCTION_H_INCLUDED
