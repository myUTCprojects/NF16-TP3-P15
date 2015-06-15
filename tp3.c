#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"


T_Produit *creerProduit(char *marque, float prix, char qualite, int quantite)
{
    T_Produit *produit;
    produit = (T_Produit*)malloc(sizeof(T_Produit));
    strcpy(produit->marque,marque);
    produit->prix = prix;
    produit->qualite = qualite;
    produit->quantite_en_stock = quantite;
    produit->suivant = NULL;
    return produit;
}

T_Rayon *creerRayon(char *nom)
//on utilise une sentinelle en début de liste de produits pour éviter de gérer le cas où le premier élément est à modifier
{
    T_Rayon* rayon;
    T_Produit* sentinelle;
    sentinelle = creerProduit("",0,' ',0);
    rayon = (T_Rayon*)malloc(sizeof(T_Rayon));
    strcpy(rayon->nom_rayon, nom);
    rayon->nombre_produits = 0;
    rayon->premier = sentinelle;
    rayon->suivant = NULL;
    return rayon;
}

T_Magasin *creerMagasin(char *nom)
//on utilise une sentinelle en début de liste de rayons pour éviter de gérer le cas où le premier élément est à modifier
{
    T_Magasin* magasin;
    T_Rayon* sentinelle;
    sentinelle = creerRayon("");
    magasin = (T_Magasin*)malloc(sizeof(T_Magasin));
    strcpy(magasin->nom,nom);
    magasin->premier = sentinelle;
    return magasin;
}

T_Rayon *rechercheRayon(T_Magasin *magasin, char* nom_rayon)
{
    T_Rayon* ptrRayon;
    ptrRayon = magasin->premier;
    while ((ptrRayon != NULL)&&(strcmp(nom_rayon, ptrRayon->nom_rayon)!=0))     //parcours des rayons
        ptrRayon = ptrRayon->suivant;
    if (ptrRayon == NULL)           //rayon non trouvé
        return NULL;
    else
        return ptrRayon;
}

int ajouterProduit(T_Rayon *rayon, T_Produit *produit)
//Ajout d'un produit dans un rayon
//renvoie 1 si l'ajout s'est bien passé, 0 sinon
//l'ajout se fait en respectant le tri par ordre alphabétique sur le nom du produit
//on ne doit pas autoriser l'utilisateur à ajouter deux fois le même produit
{
    T_Produit* ptr = NULL;
    ptr = rayon->premier;
    while((ptr->suivant != NULL)&&(strcmp(produit->marque, ptr->suivant->marque) == 1))  //tant qu'on n'est pas à la fin ET
        {                                                                           //que le produit a un nom > au suivant
            ptr = ptr->suivant;
        }
    if ((ptr->suivant != NULL)&&(strcmp(produit->marque, ptr->suivant->marque) == 0))       //on trouve un produit identique
        return 0;
    else
        {
            produit->suivant = ptr->suivant;
            ptr->suivant = produit;
            rayon->nombre_produits++;
            return 1;
        }
}

int ajouterRayon(T_Magasin *magasin, T_Rayon *rayon)
//Ajout d'un rayon dans un magasin
//renvoie 1 si l'ajout s'est bien passé, 0 sinon
//l'ajout se fait en respectant le tri par ordre alphabétique sur le nom du rayon
//on ne doit pas autoriser l'utilisateur à ajouter deux fois le même rayon
{
    T_Rayon* ptr = NULL;
    ptr = magasin->premier;
    while((ptr->suivant != NULL)&&(strcmp(rayon->nom_rayon,ptr->suivant->nom_rayon) == 1))  //tant qu'on n'est pas à la fin ET
        {                                                                                   //que le rayon a un nom > au suivant
            ptr = ptr->suivant;
        }
    if ((ptr->suivant != NULL)&&(strcmp(rayon->nom_rayon, ptr->suivant->nom_rayon) == 0))        //si le rayon existe déjà
        return 0;
    else
        {
            rayon->suivant = ptr->suivant;
            ptr->suivant = rayon;
            return 1;
        }
}

void afficherMagasin(T_Magasin *magasin)
//Affichage de tous les rayons d'un magasin
{
    T_Rayon* ptr = NULL;
    if(magasin->premier->suivant == NULL)           //s'il n'y a que la sentinelle
        printf("MAGASIN VIDE\n");
    else
        {
            ptr = magasin->premier->suivant;        //on commence juste après la sentinelle
            printf("Nom\tNombre de produits\n");
            while(ptr != NULL)
                {
                    printf("%s\t%d\n",ptr->nom_rayon,ptr->nombre_produits);
                    ptr = ptr->suivant;
                }
        }
}

void afficherRayon(T_Rayon *rayon)
//Affichage de tous les produits d'un rayon
{
    T_Produit* ptr = NULL;
    if(rayon->premier->suivant == NULL)
        printf("RAYON \"%s\" VIDE\n\n",rayon->nom_rayon);
    else
        {
            ptr = rayon->premier->suivant;
            printf("Marque\tPrix\tQualite\tQuantite en stock\n\n");
            while(ptr != NULL)
                {
                    printf("%s\t%.2f\t%c\t%d\n",ptr->marque,ptr->prix,ptr->qualite,ptr->quantite_en_stock);
                    ptr = ptr->suivant;
                }
        }
}

int retirerProduit(T_Rayon *rayon, char* nom_produit)
//Retrait d'un produit dans un rayon
//renvoie 1 si le retrait s'est bien passé, 0 sinon
//on veillera à libérer la mémoire précédemment allouée
{
    T_Produit* ptr = NULL;
    T_Produit* temp = NULL;
    ptr = rayon->premier;
    while((ptr->suivant != NULL)&&(strcmp(nom_produit,ptr->suivant->marque) != 0))      //parcours des produits
        ptr = ptr->suivant;
    if(ptr->suivant == NULL)     //si on n'a pas trouvé le produit
        return 0;
    else
        {
            temp = ptr->suivant;
            ptr->suivant=ptr->suivant->suivant;
            free(temp);
            rayon->nombre_produits--;
            return 1;
        }
}

int supprimerRayon(T_Magasin *magasin, char *nom_rayon)
//Suppression d'un rayon et de tous les produits qu'il contient
//renvoie 1 si la suppression s'est bien passée, 0 sinon
//on veillera à libérer la mémoire précédemment allouée
{
    T_Rayon* ptrRayon = NULL;
    T_Rayon* tempRayon = NULL;
    T_Produit* tempProduit = NULL;
    ptrRayon = magasin->premier;
    while ((ptrRayon->suivant != NULL)&&(strcmp(nom_rayon, ptrRayon->suivant->nom_rayon) != 0))     //parcours des rayons
        ptrRayon = ptrRayon->suivant;
    if (ptrRayon->suivant == NULL)                               //rayon non trouvé
        return 0;
    else                                                         //rayon trouvé (pointé par ptrRayon->suivant)
        {
            while (ptrRayon->suivant->nombre_produits != 0)      //tant que le rayon n'est pas vide
                retirerProduit(ptrRayon->suivant, ptrRayon->suivant->premier->suivant->marque);  //on retire le premier produit
            tempProduit = ptrRayon->suivant->premier;   //"sauvegarde" de la sentinelle
            ptrRayon->suivant->premier = NULL;          //remplacement de la sentinelle par NULL
            free(tempProduit);                          //libération de la sentinelle
            tempRayon = ptrRayon->suivant;                      //"sauvegarde" du rayon
            ptrRayon->suivant=ptrRayon->suivant->suivant;       //suppression du rayon
            free(tempRayon);                                    //libération du rayon
            return 1;
        }
}

char *rechercheRayonDuProduit(T_Magasin *magasin, T_Produit *produit)
{
    //renvoie le nom du rayon dans lequel se trouve le produit
    //ici on est sûr que le produit recherché existe car il a été copié
    T_Rayon *ptrRayon = magasin->premier->suivant;
    T_Produit *ptrProduit = NULL;
    int trouve = 0;     //mise à 1 quand on a trouvé le produit
    while (trouve == 0)
        {
            ptrProduit = ptrRayon->premier->suivant;
            while (ptrProduit != NULL)
                {
                    if (strcmp(ptrProduit->marque, produit->marque) == 0)
                        {
                            trouve = 1;
                            return ptrRayon->nom_rayon;
                        }
                    else
                        ptrProduit = ptrProduit->suivant;
                }
            ptrRayon = ptrRayon->suivant;
        }

}

void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max)
//Recherche des produits se situant dans une fourchette de prix entrée par l'utilisateur
//L'affichage se fait sous forme de liste triée sur la marque du produit

{
    T_Rayon *ptrRayon = NULL, *rayon;
    T_Produit *ptrProduit = NULL, *produit;
    if (magasin->premier->suivant == NULL)                      //magasin vide
        printf("magasin vide\n");
    //remplissage de la liste des produits concernés
    else
        {
            rayon = creerRayon("listeTrie");
            ptrRayon=magasin->premier->suivant;
            while (ptrRayon != NULL)                            //parcours des rayons
                {
                    ptrProduit=ptrRayon->premier->suivant;
                    while (ptrProduit != NULL)                  //parcours des produits
                        {
                            if ((prix_min <= ptrProduit->prix)&&(ptrProduit->prix <= prix_max))
                            {
                                produit = creerProduit(ptrProduit->marque, ptrProduit ->prix, ptrProduit->qualite, ptrProduit->quantite_en_stock);
                                ajouterProduit(rayon, produit);
                                produit = NULL;
                                rayon->nombre_produits++;
                            }
                            ptrProduit=ptrProduit->suivant;
                        }
                    ptrRayon=ptrRayon->suivant;
                }
        }
    //affichage du rayon et libération de la mémoire au fur et à mesure de l'affichage
    ptrProduit = NULL;
    if(rayon->nombre_produits == 0)
        printf("Aucun produit trouve.\n\n");
    else
        {
            ptrProduit = rayon->premier->suivant;
            printf("Marque\tPrix\tQualite\tQuantite en stock\tRayon\n\n");
            while(ptrProduit != NULL)
                {
                    printf("%s\t%.2f\t%c\t%d\t\t\t%s\n",ptrProduit->marque,ptrProduit->prix,ptrProduit->qualite,ptrProduit->quantite_en_stock,rechercheRayonDuProduit(magasin,ptrProduit));
                    retirerProduit(rayon, ptrProduit->marque);  //on retire le produit affiché du rayon
                    ptrProduit = rayon->premier->suivant;
                }
        }
    ptrProduit = rayon->premier;    //"sauvegarde" de la sentinelle
    rayon->premier = NULL;          //remplacement de la sentinelle par NULL
    free(ptrProduit);               //libération de la sentinelle
    free(rayon);                    //libération du rayon
}
