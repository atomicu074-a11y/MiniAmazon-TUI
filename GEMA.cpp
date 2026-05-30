#include "GEMA.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

Guerrier::Guerrier(string nom) 
    : Personnage(nom, 150, 25, 15, 8) {
    resistance_feu_ = 1.0;
    resistance_glace_ = 1.0;
}

void Guerrier::attaquer(Personnage& cible, string& log) {
    int degats = atk_ - cible.def();
    if (degats < 5) degats = 5; 
    cible.recevoir_degats(degats);
    log = "⚔️ [" + nom_ + "] يضرب بالسيف ويسبّب " + to_string(degats) + " ضرر بدني لـ [" + cible.nom() + "]!";
}

void Guerrier::lancer_magie(Personnage& cible, string& log) {
    int degats = atk_ - (cible.def() / 2);
    cible.recevoir_degats(degats);
    log = "✨ [" + nom_ + "] يطلق ضربة مقدسة تتجاهل الدفاع وتسبّب " + to_string(degats) + " ضرر!";
}

Mage::Mage(string nom) 
    : Personnage(nom, 90, 35, 5, 12) {
    resistance_feu_ = 0.5;
    resistance_glace_ = 0.5; 

void Mage::attaquer(Personnage& cible, string& log) {
    int degats = atk_ - cible.def();
    if (degats < 5) degats = 5;
    cible.recevoir_degats(degats);
    log = "🪄 [" + nom_ + "] يضرب بعصاه السحرية ويسبّب " + to_string(degats) + " ضرر لـ [" + cible.nom() + "]!";
}

void Mage::lancer_magie(Personnage& cible, string& log) {
    int degats_base = 40; 
    int degats_finals = degats_base * cible.get_resistance_feu(); 
    
    cible.recevoir_degats(degats_finals);
    log = "🔥 [" + nom_ + "] يطلق كرة لهب حارقة تسبّb " + to_string(degats_finals) + " ضرر سحري لـ [" + cible.nom() + "]!";
}



Monstre::Monstre(string nom, int pv, int atk, int def, int vit, double res_feu)
    : Personnage(nom, pv, atk, def, vit) {
    resistance_feu_ = res_feu;
    resistance_glace_ = 1.0;
}

void Monstre::attaquer(Personnage& cible, string& log) {
    int degats = atk_ - cible.def();
    if (degats < 5) degats = 5;
    cible.recevoir_degats(degats);
    log = "👾 الوحش [" + nom_ + "] يهاجم ويسبّب " + to_string(degats) + " ضرر لـ [" + cible.nom() + "]!";
}

void Monstre::lancer_magie(Personnage& cible, string& log) {
    int degats = atk_;
    cible.recevoir_degats(degats);
    log = "💨 الوحش [" + nom_ + "] يطلق زئيراً مرعباً يسبّب " + to_string(degats) + " ضرر!";
}

Magasin::Magasin() {
    produits_.push_back(Monstre("الغول الأخضر", 80, 18, 8, 6, 1.5));
    produits_.push_back(Monstre("تنين الحمم", 120, 22, 12, 10, 0.2));
    produits_.push_back(Monstre("الهيكل العظمي", 60, 15, 5, 11, 1.0));
    
    indice_ennemi_actif_ = 0;
}

const Personnage* Magasin::trouver(int id) const {
    if (id > 0 && id <= produits_.size()) {
        return &produits_[id - 1];
    }
    return nullptr;
}

void Magasin::executer_tour_ennemi(Personnage& heros, string& log) {
    if (produits_[indice_ennemi_actif_].est_vivant()) {
        produits_[indice_ennemi_actif_].attaquer(heros, log);
    } else {
        log = "💀 [" + produits_[indice_ennemi_actif_].nom() + "] مهزوم الآن! لقد انتصرت في المعركة.";
    }
}

void Magasin::sauvegarder_journal(const string& texte) {
}



void Panier::vider() {
    lignes_.clear();
}

bool Panier::vide() const {
    return lignes_.empty();
}

void Magasin::ajouter_au_inventaire(Panier& inv, int id_objet, int qte, string& msg) {
    if (qte <= 0) {
        msg = "⚠ الكمية غير صالحة!";
        return;
    }
    
    for (auto& ligne : inv.lignes()) {
        if (ligne.produit_id == id_objet) {
            ligne.quantite += qte;
            msg = "🎒 تم إضافة الأداة بنجاح!";
            return;
        }
    }
    
    Ligne nouvelle_ligne = {id_objet, qte};
    inv.lignes().push_back(nouvelle_ligne);
    msg = "🎒 تم إضافة أداة جديدة إلى الحقيبة!";
}
