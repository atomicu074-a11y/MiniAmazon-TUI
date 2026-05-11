#ifndef MAGASIN_H
#define MAGASIN_H

#include <string>
#include <vector>
#include <ctime>

struct DetailPrix {
    double sous_total = 0.0;
    double remise = 0.0;
    double total_ht = 0.0;
    double tva = 0.0;
    double total_ttc = 0.0;
};

class Produit {
public:
    Produit(int id, std::string nom, std::string categorie, double prix, int stock);
    int id() const { return id_; }
    const std::string& nom() const { return nom_; }
    const std::string& categorie() const { return categorie_; }
    double prix() const { return prix_; }
    int stock() const { return stock_; }
    void diminuer_stock(int q) { stock_ -= q; }
    void augmenter_stock(int q) { stock_ += q; }
private:
    int id_; std::string nom_, categorie_; double prix_; int stock_;
};

class Panier {
public:
    struct Ligne { int produit_id; int quantite; };
    void ajouter(int id, int q);
    void vider() { lignes_.clear(); }
    bool vide() const { return lignes_.empty(); }
    const std::vector<Ligne>& lignes() const { return lignes_; }
private:
    std::vector<Ligne> lignes_;
};

class Client {
public:
    explicit Client(std::string nom) : nom_(nom) {}
    std::string nom() const { return nom_; }
    void set_nom(std::string n) { nom_ = n; }
    Panier& panier() { return panier_; }
    // ... Historique de commandes ...
private:
    std::string nom_;
    Panier panier_;
};

class Magasin {
public:
    Magasin();
    std::vector<Produit>& produits() { return produits_; }
    Produit* trouver(int id);
    const Produit* trouver(int id) const;
    bool ajouter_au_panier(Panier& p, int id, int q, std::string& msg);
    DetailPrix calculer_prix(const Panier& p) const;
    void sauvegarder_journal(const std::string& log);
private:
    std::vector<Produit> produits_;
};

#endif
