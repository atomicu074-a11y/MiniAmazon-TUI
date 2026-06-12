#include "GEMA.h"
#include <iostream>
#include <algorithm>

using namespace std;


Guerrier::Guerrier(string nom) 
    : Personnage(nom, 150, 30, 25, 15, 8) { 
    resistance_feu_ = 0.8; 
}

void Guerrier::attaquer(Personnage& cible, string& log) {
    int degats = atk_ - cible.def();
    if (degats < 5) degats = 5;
    cible.recevoir_degats(degats);
    log = "⚔️ [" + nom_ + "] يضرب بالسيف ويسبّب " + to_string(degats) + " ضرر بدني لـ [" + cible.nom() + "]!";
}

void Guerrier::lancer_magie(Personnage& cible, string& log) {
    log = "🛡️ [" + nom_ + "] ليس لديه قدرات سحرية، لكنه يفعّل وضعيّة الحماية لتقليل الضرر!";
}

void Guerrier::executer_coups_special(Personnage& cible, string& log) {
    if (mp_actuels_ >= 10) {
        utiliser_mp(10);
        int degats = (atk_ * 2) - cible.def(); 
        if (degats < 15) degats = 15;
        cible.recevoir_degats(degats);
        log = "💥 [ضربة قاصمة] غرس [" + nom_ + "] سيفه العملاق في العدو مسبباً " + to_string(degats) + " ضرر هائل!";
    } else {
        log = "⚠ نقاط السحر (MP) غير كافية لتنفيذ الضربة القاصمة!";
    }
}

Mage::Mage(string nom) 
    : Personnage(nom, 90, 100, 35, 5, 12) {
    resistance_feu_ = 0.4; 
}

void Mage::attaquer(Personnage& cible, string& log) {
    int degats = atk_ / 2;
    cible.recevoir_degats(degats);
    log = "🪄 [" + nom_ + "] يلوّح بعصاه ويسبّب " + to_string(degats) + " ضرر خفيف لـ [" + cible.nom() + "]!";
}

void Mage::lancer_magie(Personnage& cible, string& log) {
    if (mp_actuels_ >= 20) {
        utiliser_mp(20);
        int degats_base = 45; 
        int degats_finals = degats_base * cible.get_resistance_feu(); 
        cible.recevoir_degats(degats_finals);
        log = "🔥 [جحيم النار] أطلق [" + nom_ + "] كرة لهب متفجرة تسبّب " + to_string(degats_finals) + " ضرر سحري!";
    } else {
        log = "⚠ نقاط السحر (MP) نفذت! لا يمكنك إطلاق سحر النار.";
    }
}

void Mage::executer_coups_special(Personnage& cible, string& log) {
    mp_actuels_ += 30;
    if (mp_actuels_ > mp_max_) mp_actuels_ = mp_max_;
    log = "🔮 [التأمل العميق] قام الساحر [" + nom_ + "] بتركيز طاقته واستعاد +30 من نقاط السحر (MP)!";
}

Archer::Archer(string nom) 
    : Personnage(nom, 110, 50, 28, 10, 16) { 
    resistance_feu_ = 1.0;
}

void Archer::attaquer(Personnage& cible, string& log) {
    int degats = atk_ - (cible.def() / 2); 
    cible.recevoir_degats(degats);
    log = "🏹 [" + nom_ + "] يطلق سهماً سريعاً ويسبّب " + to_string(degats) + " ضرر مخترق لـ [" + cible.nom() + "]!";
}

void Archer::lancer_magie(Personnage& cible, string& log) {
    if (mp_actuels_ >= 15) {
        utiliser_mp(15);
        int degats = 30 * cible.get_resistance_feu(); 
        cible.recevoir_degats(degats);
        log = "🏹🔥 [السهم المتفجر] أطلق [" + nom_ + "] سهماً مشتعلاً سبّب " + to_string(degats) + " ضرر عنصري!";
    } else {
        log = "⚠ نقاط السحر لا تكفي لشحن السهم بالهب!";
    }
}

void Archer::executer_coups_special(Personnage& cible, string& log) {
    if (mp_actuels_ >= 25) {
        utiliser_mp(25);
        int degats_totaux = (atk_ - cible.def()) * 3;
        if (degats_totaux < 15) degats_totaux = 15;
        cible.recevoir_degats(degats_totaux);
        log = "🌪️ [وابل السهام] أطلق [" + nom_ + "] عاصفة من السهام الحادة تسبّب " + to_string(degats_totaux) + " ضرر مميت!";
    } else {
        log = "⚠ نقاط السحر غير كافية لإطلاق وابل السهام!";
    }
}

Monstre::Monstre(string nom, int pv, int atk, int def, int vit, double res_feu)
    : Personnage(nom, pv, 0, atk, def, vit) {
    resistance_feu_ = res_feu;
}

void Monstre::attaquer(Personnage& cible, string& log) {
    int degats = atk_ - cible.def();
    if (degats < 5) degats = 5;
    cible.recevoir_degats(degats);
    log = "👾 الوحش [" + nom_ + "] يهاجم بعنف ويسبّب " + to_string(degats) + " ضرر لـ [" + cible.nom() + "]!";
}

void Monstre::lancer_magie(Personnage& cible, string& log) {
    int degats = atk_ + 10;
    cible.recevoir_degats(degats);
    log = "💨 الوحش يطلق زئيراً مرعباً يتسبب في " + to_string(degats) + " ضرر مباشر!";
}

Magasin::Magasin() {
    monstres_.push_back(Monstre("الغول الأخضر الثقيل", 90, 22, 12, 6, 1.5));
    monstres_.push_back(Monstre("تنين الحمم الأسطوري", 140, 28, 18, 10, 0.2));
    indice_monstre_actif_ = 0;
}

void Magasin::executer_tour_ennemi(Personnage& heros, string& log) {
    if (monstres_[indice_monstre_actif_].est_vivant()) {
        monstres_[indice_monstre_actif_].attaquer(heros, log);
    } else {
        log = "💀 [" + monstres_[indice_monstre_actif_].nom() + "] سقط مهزوماً! أحسنت صنعاً.";
    }
}

Client::Client(string nom, string classe_choisie)
    : Personnage(nom, 120, 40, 25, 10, 11), classe_(classe_choisie) {}

void Client::attaquer(Personnage& cible, string& log) {
    int degats = atk_ - cible.def();
    if (degats < 6) degats = 6;
    cible.recevoir_degats(degats);
    log = "⚔️ البطل [" + nom_ + "] ينفذ ضربة بدنية مسبباً " + to_string(degats) + " ضرر للوحش.";
}

void Client::lancer_magie(Personnage& cible, string& log) {
    int degats = 35 * cible.get_resistance_feu();
    cible.recevoir_degats(degats);
    log = "🔥 البطل يطلق موجة سحرية حارقة تسبّب " + to_string(degats) + " ضرر عنصري.";
}

void Client::executer_coups_special(Personnage& cible, string& log) {
    int degats = atk_ * 1.5;
    cible.recevoir_degats(degats);
    log = "⚡ البطل يستخدم مهارته الخاصة الغاضبة مسبباً " + to_string(degats) + " ضرر!";
}
