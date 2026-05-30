#ifndef INTERFACE_H
#define INTERFACE_H

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

#include "GAME.h" 

class Ui {
public:
    Ui();

    void lancer();

private:
    ftxui::Element render_produits();      
    ftxui::Element render_panier();         
    ftxui::Element render_journal_combat();

    void action_valider_commande();        
    void verifier_et_ajouter(const ProduitElectronique& nouveau_produit);

    std::string message_;   
    ftxui::Color rose_;
    ftxui::Color mauve_;
    ftxui::Color bleu_doux_;
    ftxui::Color vert_clair_;
    ftxui::Color fond_;
    ftxui::Color surface_;
    ftxui::Color alerte_;
    ftxui::Color accent_;
};

#endif // INTERFACE_H
