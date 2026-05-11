#include "Magasin.h"
#include <fstream>
#include <iomanip>

Produit::Produit(int id, std::string nom, std::string cat, double p, int s) 
    : id_(id), nom_(nom), categorie_(cat), prix_(p), stock_(s) {}

Magasin::Magasin() {
    produits_.push_back(Produit(1, "ordinateur portable", "informatique", 899.99, 5));
    produits_.push_back(Produit(2, "souris sans fil", "accessoire", 29.99, 20));
    produits_.push_back(Produit(3, "clavier mecanique", "accessoire", 149.99, 8));
    produits_.push_back(Produit(4, "casque audio", "audio", 199.99, 12));
    produits_.push_back(Produit(5, "ecran 27 pouces", "informatique", 299.99, 3));
    produits_.push_back(Produit(6, "hub usb-c", "connectique", 49.99, 15));
       produits_.push_back(Produit(7, "sweat à capuche noir", "vetements", 45.00, 20));
        produits_.push_back(Produit(8, "sneakers blanches", "chaussures", 89.90, 8));
        produits_.push_back(Produit(9, "parfum royal oud", "parfumerie", 120.00, 5));
        produits_.push_back(Produit(10, "jean slim bleu", "vetements", 39.00, 15));
        produits_.push_back(Produit(11, "bottines en cuir", "chaussures", 110.00, 3));
        produits_.push_back(Produit(12, "sac à dos urbain", "accessoire", 75.00, 10));
        produits_.push_back(Produit(13, "imprimante 3D", "informatique", 199.99, 7));
        produits_.push_back(Produit(14, "tablette graphique", "informatique", 249.99, 4));
}


Produit* Magasin::trouver(int id) {
    for (auto& p : produits_) {
        if (p.id() == id) return &p;
    }
    return nullptr;
}

const Produit* Magasin::trouver(int id) const {
    for (const auto& p : produits_) {
        if (p.id() == id) return &p;
    }
    return nullptr;
}

void Magasin::sauvegarder_journal(const std::string& log) {
    std::ofstream fichier("journal.txt", std::ios::app);
    if (fichier.is_open()) {
        fichier << log << std::endl;
        fichier.close();
    }
}

// Implémentation de la logique de panier
void Panier::ajouter(int id, int q) {
    for (auto& ligne : lignes_) {
        if (ligne.produit_id == id) {
            ligne.quantite += q;
            return;
        }
    }
    lignes_.push_back({id, q});
}

bool Magasin::ajouter_au_panier(Panier& panier, int id, int quantite, std::string& message) {
    Produit* produit = trouver(id);
    if (!produit) {
        message = "⚠ produit introuvable";
        return false;
    }
    if (produit->stock() < quantite) {
        message = "⚠ stock insuffisant";
        return false;
    }

    produit->diminuer_stock(quantite);
    panier.ajouter(id, quantite);
    message = "🛒 produit ajouté au panier";
    return true;
}

DetailPrix Magasin::calculer_prix(const Panier& panier) const {
    DetailPrix detail;
    for (const auto& ligne : panier.lignes()) {
        const Produit* produit = trouver(ligne.produit_id);
        if (produit) {
            detail.sous_total += produit->prix() * ligne.quantite;
        }
    }
    detail.remise = detail.sous_total > 500.0 ? detail.sous_total * 0.10 : 0.0;
    detail.total_ht = detail.sous_total - detail.remise;
    detail.tva = detail.total_ht * 0.20;
    detail.total_ttc = detail.total_ht + detail.tva;
    return detail;
}
