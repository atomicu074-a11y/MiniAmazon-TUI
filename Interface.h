#ifndef INTERFACE_H
#define INTERFACE_H

#include "Magasin.h"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

class Ui {
public:
    Ui();
    void lancer();

private:
    // Méthodes de rendu
    ftxui::Element render_produits();
    ftxui::Element render_panier();
    ftxui::Element render_historique();
    void action_valider_commande();

    // Données du magasin
  Magasin magasin_;
    Client client_;
    std::string message_;

    // Palette de couleurs complète
    ftxui::Color rose_, mauve_, bleu_doux_, vert_clair_;
    ftxui::Color fond_, surface_, alerte_, accent_, texte_gris_;
};

#endif
