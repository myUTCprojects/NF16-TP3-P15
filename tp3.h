#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED

#define MAX 20


typedef struct T_Produit{
                char marque[MAX];
                float prix;
                char qualite;
                int quantite_en_stock;
                struct T_Produit* suivant;
                        }T_Produit;

typedef struct T_Rayon{
                char nom_rayon[MAX];
                int nombre_produits;
                T_Produit* premier;
                struct T_Rayon* suivant;
                      }T_Rayon;

typedef struct{
                char nom[MAX];
                T_Rayon* premier;
              }T_Magasin;

T_Produit *creerProduit(char *marque, float prix, char qualite, int quantite);

T_Rayon *creerRayon(char *nom);

T_Magasin *creerMagasin(char *nom);

T_Rayon *rechercheRayon(T_Magasin *magasin, char* nom_rayon);               //permet de savoir où ajouter un produit

int ajouterProduit(T_Rayon *rayon, T_Produit *produit);

int ajouterRayon(T_Magasin *magasin, T_Rayon *rayon);

void afficherMagasin(T_Magasin *magasin);

void afficherRayon(T_Rayon *rayon);

int retirerProduit(T_Rayon *rayon, char* nom_produit);

int supprimerRayon(T_Magasin *magasin, char *nom_rayon);

char *rechercheRayonDuProduit(T_Magasin *magasin, T_Produit *produit);      // pour l'affichage des rayons dans rechercheProduits

void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max);


#endif // TP3_H_INCLUDED
