#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tp3.h"

/*-------------------------NF16 - TP3 - Baptiste Amato, Sylvain Carre------------------------------*/

int main()
{
    char repMenu;               //choix de l'action dans le menu
    char repChar;
    char repString[20];
    float repFloat, repFloat2;
    int repInt;
    int verifMagasin = 0;       //booléen : mise à 1 si le magasin est créé
    int nombreRayons = 0;
    T_Magasin *magasin = NULL;
    T_Rayon *rayon = NULL, *temp = NULL;
    T_Produit *produit = NULL;
    printf("\n----------TP3 de NF16----------\n");
    do
    {
        printf("\nQue voulez-vous faire ?\n\n");
        printf("Creer un magasin (A) ?\nAjouter un rayon au magasin (B) ?\n");
        printf("Ajouter un produit dans un rayon (C) ?\nAfficher les rayons du magasin (D) ?\n");
        printf("Afficher les produits d'un rayon (E) ?\nRetirer un produit (F) ?\n");
        printf("Supprimer un rayon (G) ?\nRechercher un produit par prix (H) ?\nQuitter (I) ?\n\n");
        scanf("%c",&repMenu);
        fflush(stdin);                      //vidage du buffer
        if (islower(repMenu))
            repMenu=toupper(repMenu);       //conversion en majuscule
        switch (repMenu)
        {
            case 'A':{
                        system("cls");      //effaçage de l'écran
                        if (verifMagasin ==1)
                            printf("Vous avez deja cree votre magasin !\n\n");
                        else
                            {
                                printf("Comment appeler le magasin ?\n\n");
                                scanf("%s",repString);
                                fflush(stdin);
                                magasin = creerMagasin(repString);
                                printf("\nMagasin cree !\n\n");
                                verifMagasin = 1;
                            }
                        break;
                     }
            case 'B':{
                        system("cls");
                        if (verifMagasin == 0)
                            printf("Veuillez commencer par creer un magasin.\n\n");
                        else
                            {
                                printf("Comment appeler le rayon ?\n\n");
                                scanf("%s",repString);
                                fflush(stdin);
                                rayon = creerRayon(repString);
                                if (ajouterRayon(magasin, rayon) == 0)
                                    printf("\nCe rayon existe deja\n");
                                else
                                    {
                                        printf("\nRayon ajoute !\n\n");
                                        nombreRayons ++;
                                    }
                                rayon = NULL;   //si on ne fait pas cette instruction et que le rayon est supprimé, l'instruction
                                                // à la fin "free(rayon)" plantera car "rayon" ne pointera plus vers rien
                            }
                        break;
                     }
            case 'C':{
                        system("cls");
                        if (verifMagasin == 0)
                            printf("Veuillez commencer par creer un magasin.\n\n");
                        if (nombreRayons == 0)
                            printf("Veuillez commencer par creer un rayon.\n\n");
                        else
                            {
                                printf("Quelle est la marque du produit ?\n");
                                scanf("%s",repString);
                                fflush(stdin);
                                printf("\nCombien coute-t-il ?\n");
                                scanf("%f",&repFloat);
                                fflush(stdin);
                                do
                                    {
                                        printf("\nDe quelle qualite est-il (A,B ou C)?\n");
                                        scanf("%c",&repChar);
                                        fflush(stdin);
                                        if (islower(repChar))
                                            repChar=toupper(repChar);       //conversion en majuscule
                                    }
                                while ((repChar != 'A')&&(repChar != 'B')&&(repChar != 'C'));
                                printf("\nCombien en ajouter au stock ?\n\n");
                                scanf("%d",&repInt);
                                fflush(stdin);
                                produit = creerProduit(repString, repFloat, repChar, repInt);
                                printf("\nA quel rayon ajouter le produit ?\n\n");
                                scanf("%s",repString);
                                fflush(stdin);
                                rayon = rechercheRayon(magasin, repString);
                                if (rayon == NULL)
                                    printf("\nRayon non trouve.\n");
                                else
                                    {
                                        if (ajouterProduit(rayon, produit) == 0)
                                            printf("\nProduit deja existant en magasin.\n");
                                        else
                                            printf("\Produit ajoute !\n\n");
                                    }
                                produit = NULL;
                                rayon = NULL;
                            }
                        break;
                     }
            case 'D':{
                        system("cls");
                        if (verifMagasin == 0)
                            printf("Veuillez commencer par creer un magasin.\n\n");
                        else
                            {
                                afficherMagasin(magasin);
                            }
                        break;
                     }
            case 'E':{
                        system("cls");
                        if (verifMagasin == 0)
                            printf("Veuillez commencer par creer un magasin.\n\n");
                        if (nombreRayons == 0)
                            printf("Veuillez commencer par creer un rayon.\n\n");
                        else
                            {
                                printf("Quel rayon afficher ?\n");
                                scanf("%s",repString);
                                fflush(stdin);
                                rayon = rechercheRayon(magasin, repString);
                                if (rayon == NULL)
                                    printf("\nRayon non trouve.\n");
                                else
                                    afficherRayon(rayon);
                                rayon = NULL;
                            }
                        break;
                     }
            case 'F':{
                        system("cls");
                        if (verifMagasin == 0)
                            printf("Veuillez commencer par creer un magasin.\n\n");
                        else
                            {
                                printf("Dans quel rayon se trouve le produit a retirer ?\n");
                                scanf("%s",repString);
                                fflush(stdin);
                                if ((rayon = rechercheRayon(magasin, repString)) == NULL)
                                    printf("\nRayon non trouve\n");
                                else
                                    {
                                        printf("\nQuel produit retirer ?\n");
                                        scanf("%s",repString);
                                        fflush(stdin);
                                        if (retirerProduit(rayon, repString) == 0)
                                            printf("\nProduit non trouve.\n\n");
                                        else
                                            printf("\nProduit supprime avec succes !\n\n");
                                    }
                                rayon = NULL;
                            }
                        break;
                     }
            case 'G':{
                        system("cls");
                        if (verifMagasin == 0)
                            printf("Veuillez commencer par creer un magasin.\n\n");
                        else
                            {
                                printf("Quel rayon supprimer ?\n");
                                scanf("%s",repString);
                                fflush(stdin);
                                if (supprimerRayon(magasin, repString) == 0)
                                    printf("\nRayon non trouve.\n");
                                else
                                    {
                                        printf("\nLe rayon a ete supprime avec succes.\n");
                                        nombreRayons--;
                                    }
                            }
                        break;
                     }
            case 'H':{
                        system("cls");
                        if (verifMagasin == 0)
                            printf("Veuillez commencer par creer un magasin.\n\n");
                        else
                            {
                                printf("Quel est le prix minimum ?\n");
                                scanf("%f",&repFloat);
                                fflush(stdin);
                                printf("\nQuel est le prix maximum ?\n");
                                scanf("%f",&repFloat2);
                                fflush(stdin);
                                rechercheProduits(magasin, repFloat, repFloat2);
                            }
                        break;
                     }
            case 'I':{  //suppression du magasin et libération de l'espace mémoire
                        if (verifMagasin != 0)                                  //si le magasin a été créé
                        {
                            while (nombreRayons != 0)                           //tant qu'il reste des rayons
                                {
                                    supprimerRayon(magasin, magasin->premier->suivant->nom_rayon); //suppression du premier rayon
                                    nombreRayons--;
                                }
                            temp = magasin->premier;   //"sauvegarde" de la sentinelle
                            magasin->premier = NULL;   //remplacement de la sentinelle par NULL
                            free(temp);                //libération de la sentinelle
                            free(magasin);
                        }
                        break;
                     }

            default: printf("Vous vous etes surement trompe de touche...\n\n");
        }       //fin switch
        system("PAUSE");
        system("cls");
    }           //fin do
    while (repMenu != 'I');
    return 0;
}
