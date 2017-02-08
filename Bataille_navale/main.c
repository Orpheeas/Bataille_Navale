#include <stdio.h>
#include <stdlib.h>

#define NBJOUEUR 2 //Nombre de joueur
#define TAILLEFLOTTE 5  //Nombre de bateau par flotte
#define TAILLEPLATEAU 10 //Nombres de cases par lignes/colonnes


typedef struct Cell{

    int column;
    int row;

}Cell;

typedef struct Boat{

    Cell tabbateau[TAILLEFLOTTE];    //Definit le nombre de pieces/bateau que le joueur possède
}Boat;

typedef struct Fleet{

    Boat tabflotte[NBJOUEUR];
    int nbbateau;    //Sert à savoir le bombre de bateau restant dans la flotte

}Fleet;

enum BOOL{

    True,False,
};


void creacell(int *colonne, int *ligne, int i, Fleet Joueur);    //Fonction pour poser ses bateaux sur le terrain
enum BOOL coincidecell(Cell *cellule_target, Cell *cellule_aim); //Fonction pour comparer deux cellules
enum BOOL bateauhit (Cell *cellule_aim,Cell *cellule_target);    //Fonction pour comparer si un bateau appartient à une cellule
enum BOOL Fleethit (Cell *cellule_aim, Fleet *IA);               //Fct pour comparer si un bateau appartient à une flotte

int main()
{

    Fleet Joueur;
    Fleet IA;
    Cell cellule_aim;  //La cellule que les joueurs viseront
    int colonne=1;
    int ligne=1;
    int i=0;

     srand(time(NULL)); // initialisation de rand
    //le joueur place ses bateaux
    for (i=0;i<TAILLEFLOTTE;i++){
        printf("Sur quelle colonne voulez vous placez votre bateau ?\n");
        scanf("%d",&colonne);
        fflush(stdin);
        printf("Sur quelle ligne voulez vous placez votre bateau ?\n");
        scanf("%d",&ligne);
        creacell(&colonne,&ligne,i,Joueur);
        printf("\n");
    }

    system("cls");
    //ON place les bateaux de l'IA aléatoirement
    for (i=0;i<TAILLEFLOTTE;i++){
        colonne=rand() % 10+1;
        ligne=rand() % 10+1;
        creacell(&colonne,&ligne,i,IA);
    }

    Joueur.nbbateau=TAILLEFLOTTE;
    IA.nbbateau=TAILLEFLOTTE;

    while ((Joueur.nbbateau>0) || (IA.nbbateau>0)){   //Jusqu'a que l'un des joueur soient en manque de bateau on joue

       //   <-- Tour du Joueur -->

        printf("Quel colonne voulez vous visez ?\n");          //On demande au joueur ou il souhaite viser
        scanf("%d",&cellule_aim.column);
        printf("Quel ligne voulez vous visez ?\n");
        scanf("%d",&cellule_aim.row);
        if (Fleethit(&cellule_aim,&IA)==True){       //Selon si il touche ou non on lui l=donne un feedback
            printf("Touché !\n");
            IA.nbbateau=IA.nbbateau-1;
        }else{
            printf("Loupé !\n");
        }

        printf("\n");
        printf("\n");
        printf("\n");

        // <-- Tour de l'IA -->

        printf("Tour de l'adversaire\n");
        cellule_aim.column=rand() % 10+1;          //L'Ia vise aléatoirement
        cellule_aim.row=rand() % 10+1;
        printf("Il Vise en %d %d\n",cellule_aim.column,cellule_aim.row);
        if (Fleethit(&cellule_aim,&Joueur)==True){
            printf("Il touche !\n");           //le joueur sait ou l'Ia vise et sait si il est touché ou non
            Joueur.nbbateau=Joueur.nbbateau-1;
        }else{
            printf("Il loupe !\n");
        }

        printf("\n");
        printf("\n");
        printf("\n");
    }

    //Ecran de victoire / Game over

    if (Joueur.nbbateau=0){
        system("cls");
        printf("L'ennemi a gagné !");
    }else if(IA.nbbateau=0){
        system("cls");
        printf("Bravo vous avez gagné !");
    }


    return 0;
}


void creacell(int *colonne, int *ligne, int i, Fleet Joueur){

    Joueur.tabflotte[0].tabbateau[i].column=*colonne;
    Joueur.tabflotte[0].tabbateau[i].row=*ligne;
}

enum BOOL coincidecell(Cell *cellule_target, Cell *cellule_aim){

    if((cellule_target->column==cellule_aim->column) && (cellule_target->row==cellule_aim->row)){
        return True;      //Si les cellules coincident on renvoie true
    }else{
        return False;    //Sinon on renvoie faux
    }
}

enum BOOL bateauhit (Cell *cellule_aim,Cell *cellule_target){

       if(coincidecell(&cellule_target,&cellule_aim)==True){
            return True;
        }else{
            return False;
        }
}


enum BOOL Fleethit (Cell *cellule_aim, Fleet *IA){

    Cell cellule_target;
    int i=TAILLEFLOTTE;  //On vérifie pour le nombre de bateau que possède chaque joueur
    for(i=0;i<TAILLEFLOTTE;i++){
        cellule_target.column=IA->tabflotte[0].tabbateau[i].column;     //ON attribue les coordonnées de la cellule visé à notre variable
        cellule_target.row=IA->tabflotte[0].tabbateau[i].row;
        if(bateauhit(&cellule_target,&cellule_aim)==True){
            IA->tabflotte[0].tabbateau[i].column=-1;           //Le bateau est détruit on le place hors du terrain
            IA->tabflotte[0].tabbateau[i].row=-1;               //Le bateau est détruit on le place hors du terrain
            return True;
        }else{
            return False;
        }
    }
}
