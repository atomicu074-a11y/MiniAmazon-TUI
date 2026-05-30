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

struct ElementInventaire {
    std::string nom_objet;
    int quantite;
};

class Inventaire {
public:
    void vider() { items_.clear(); }
    bool vide() const { return items_.empty(); }
    std::vector<ElementInventaire>& items() { return items_; }
private:
    std::vector<ElementInventaire> items_;
};

class Magasin { 
public:
    Magasin();
    std::vector<Monstre>& monstres() { return monstres_; }
    void executer_tour_ennemi(Personnage& heros, std::string& log);
private:
    std::vector<Monstre> monstres_;
    int indice_monstre_actif_;
};

class Client : public Personnage {
public:
    Client(std::string nom, std::string classe_choisie);
    void attaquer(Personnage& cible, std::string& log) override;
    void lancer_magie(Personnage& cible, std::string& log) override;
    Inventaire& inventaire() { return inventaire_; }
private:
    Inventaire inventaire_;
    std::string classe_;
};

#endif 
