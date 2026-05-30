#ifndef INTERFACE_H
#define INTERFACE_H

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>
#include "GEMA.h" 

class Ui {
public:
    Ui();
    void lancer();

private:
    ftxui::Element render_combat_screen();
    ftxui::Element render_inventaire_screen();
    ftxui::Element render_stats_screen();

    GEMA game_engine_;   
    Client heros_;          
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
