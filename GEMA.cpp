#include "GEMA.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;



Guerrier::Guerrier(string nom) 
    : Personnage(nom, 150, 25, 15, 8) { 
    resistance_feu_ = 1.0;
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
    }

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
    log = "🔥 [" + nom_ + "] يطلق كرة لهب حارقة تسبّب " + to_string(degats_finals) + " ضرر سحري لـ [" + cible.nom() + "]!";
}



Monstre::Monstre(string nom, int pv, int atk, int def, int vit, double res_feu)
    : Personnage(nom, pv, atk, def, vit) {
    resistance_feu_ = res_feu;
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
    monstres_.push_back(Monstre("الغول الأخضر", 80, 18, 8, 6, 1.5));
    monstres_.push_back(Monstre("تنين الحمم", 120, 22, 12, 10, 0.2));
    monstres_.push_back(Monstre("الهيكل العظمي", 60, 15, 5, 11, 1.0));
    
    indice_monstre_actif_ = 0;
}

void Magasin::executer_tour_ennemi(Personnage& heros, string& log) {
    if (monstres_[indice_monstre_actif_].est_vivant()) {
        monstres_[indice_monstre_actif_].attaquer(heros, log);
    } else {
        log = "💀 [" + monstres_[indice_monstre_actif_].nom() + "] مهزوم الآن! لقد انتصرت في المعركة.";
    }
}


Client::Client(string nom, string classe_choisie)
    : Personnage(nom, 100, 20, 10, 10), classe_(classe_choisie) {}

void Client::attaquer(Personnage& cible, string& log) {
    int degats = atk_ - cible.def();
    if (degats < 5) degats = 5;
    cible.recevoir_degats(degats);
    log = "⚔️ البطل [" + nom_ + "] يضرب ويسبّب " + to_string(degats) + " ضرر لـ [" + cible.nom() + "]!";
}

void Client::lancer_magie(Personnage& cible, string& log) {
    int degats_base = 35;
    int degats_finals = degats_base * cible.get_resistance_feu();
    cible.recevoir_degats(degats_finals);
    log = "🔥 مهارة البطل السحرية تسبّب " + to_string(degats_finals) + " ضرر لـ [" + cible.nom() + "]!";
}
