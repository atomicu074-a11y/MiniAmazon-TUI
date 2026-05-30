#ifndef GEMA_H
#define GEMA_H

#include <string>
#include <vector>


class Personnage {
public:
    Personnage(std::string nom, int pv, int atk, int def, int vit)
        : nom_(nom), pv_max_(pv), pv_actuels_(pv), atk_(atk), def_(def), vit_(vit) {}
        
    virtual ~Personnage() = default;

    std::string nom() const { return nom_; }
    int pv_actuels() const { return pv_actuels_; }
    int pv_max() const { return pv_max_; }
    int atk() const { return atk_; }
    int def() const { return def_; }
    int vit() const { return vit_; }
    
    virtual double get_resistance_feu() const { return resistance_feu_; }
    virtual double get_resistance_glace() const { return resistance_glace_; }

    bool est_vivant() const { return pv_actuels_ > 0; }
    
    void recevoir_degats(int degats) {
        pv_actuels_ -= degats;
        if (pv_actuels_ < 0) pv_actuels_ = 0;
    }
    
    void soigner(int quantite) {
        pv_actuels_ += quantite;
        if (pv_actuels_ > pv_max_) pv_actuels_ = pv_max_;
    }

    virtual void attaquer(Personnage& cible, std::string& log) = 0;
    virtual void lancer_magie(Personnage& cible, std::string& log) = 0;

protected:
    std::string nom_;
    int pv_max_;
    int pv_actuels_;
    int atk_;
    int def_;
    int vit_;
    
    double resistance_feu_ = 1.0;
    double resistance_glace_ = 1.0;
};



class Guerrier : public Personnage {
public:
    explicit Guerrier(std::string nom);
    void attaquer(Personnage& cible, std::string& log) override;
    void lancer_magie(Personnage& cible, std::string& log) override;
};

class Mage : public Personnage {
public:
    explicit Mage(std::string nom);
    void attaquer(Personnage& cible, std::string& log) override;
    void lancer_magie(Personnage& cible, std::string& log) override;
};


class Monstre : public Personnage {
public:
    Monstre(std::string nom, int pv, int atk, int def, int vit, double res_feu);
    void attaquer(Personnage& cible, std::string& log) override;
    void lancer_magie(Personnage& cible, std::string& log) override;
};


struct Ligne {
    int produit_id; 
    int quantite;
};

class Panier {
public:
    void vider();
    bool vide() const;
    std::vector<Ligne>& lignes() { return lignes_; }
    const std::vector<Ligne>& lignes() const { return lignes_; }

private:
    std::vector<Ligne> lignes_;
};

struct DetailPrix {
    double sous_total;
    double remise;
    double tva;
    double total_ttc;
};


class Magasin {
public:
    Magasin();
    
    std::vector<Monstre>& produits() { return produits_; }
    const std::vector<Monstre>& produits() const { return produits_; }
    
    const Personnage* trouver(int id) const;
    
    void executer_tour_ennemi(Personnage& heros, std::string& log);
    void ajouter_au_inventaire(Panier& inv, int id_objet, int qte, std::string& msg);
    void sauvegarder_journal(const std::string& texte);
    
    DetailPrix calculer_prix(const Panier& p) {
        return {100.0, 0.0, 20.0, 120.0}; 
    }

private:
    std::vector<Monstre> produits_;  
    int indice_ennemi_actif_;       
};

class Client : public Guerrier {
public:
    explicit Client(std::string nom) : Guerrier(nom) {}
    Panier& panier() { return inventaire_; }
private:
Panier inventaire_;
};

#endif 
