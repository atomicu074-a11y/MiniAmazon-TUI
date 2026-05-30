#include "Interface.h"
#include <ftxui/component/screen_interactive.hpp>
#include <iomanip>
#include <sstream>

using namespace ftxui;
using namespace std;

Ui::Ui() : heros_("البطل", "Guerrier") {
    rose_ = Color::RGB(245, 194, 231);
    mauve_ = Color::RGB(203, 166, 247);
    bleu_doux_ = Color::RGB(137, 180, 250);
    vert_clair_ = Color::RGB(166, 227, 161);
    fond_ = Color::RGB(30, 30, 46);
    surface_ = Color::RGB(49, 50, 68);
    alerte_ = Color::RGB(243, 139, 168);
    accent_ = Color::RGB(250, 179, 135);
    
    message_ = "⚔️ مرحباً بك في ميدان القتال! اختر إجراءك بحكمة للانتصار.";
}

Element Ui::render_combat_screen() {
    string nom_monstre = game_engine_.monstres().empty() ? "لا يوجد عدو" : game_engine_.monstres()[0].nom();
    int pv_monstre = game_engine_.monstres().empty() ? 0 : game_engine_.monstres()[0].pv_actuels();
    int pv_max_monstre = game_engine_.monstres().empty() ? 0 : game_engine_.monstres()[0].pv_max();

    return vbox({
        window(text(" 👾 حالة العدو الحالي ") | bold | color(alerte_),
            vbox({
                text(" الاسم : " + nom_monstre) | color(alerte_),
                text(" نقاط الحياة (PV) : " + to_string(pv_monstre) + " / " + to_string(pv_max_monstre)) | color(rose_)
            })
        ),
        separator(),
        window(text(" 📜 سجل المعركة الأخير "),
            vbox({
                text(" • في انتظار حركتك القادمة... ") | dim | italic
            })
        )
    });
}

Element Ui::render_inventaire_screen() {
    Elements items_elements;
    
    if (heros_.inventaire().vide()) {
        items_elements.push_back(text(" 🧳 الحقيبة فارغة حالياً! ") | dim | italic);
    } else {
        items_elements.push_back(text(" الأدوات المتاحة في جعبتك :") | bold | color(accent_));
        items_elements.push_back(separator());
        for (const auto& item : heros_.inventaire().items()) {
            items_elements.push_back(hbox({
                text(" • " + item.nom_objet),
                filler(),
                text("الكمية: " + to_string(item.quantite)) | color(vert_clair_)
            }));
        }
    }

    return window(text(" 🎒 حقيبة المستهلكات "), vbox(move(items_elements))) | bgcolor(surface_);
}

Element Ui::render_stats_screen() {
    return window(text(" 📊 بطاقة تعريف البطل "),
        vbox({
            text(" الاسم   : " + heros_.nom()) | bold | color(accent_),
            separator(),
            text(" نقاط الحياة (PV) : " + to_string(heros_.pv_actuels()) + " / " + to_string(heros_.pv_max())) | color(vert_clair_),
            text(" قوة الهجوم (ATK) : " + to_string(heros_.atk())) | color(bleu_doux_),
            text(" قوة الدفاع (DEF) : " + to_string(heros_.def())) | color(mauve_),
            text(" سرعة الحركة(VIT) : " + to_string(heros_.vit())) | color(rose_),
            separator(),
            text(" الحالة  : جاهز لخوض المعركة القادمة ") | dim | italic
        })
    ) | bgcolor(surface_);
}

void Ui::lancer() {
    auto screen = ScreenInteractive::TerminalOutput();

    int selected_tab = 0;
    vector<string> tabs_entries = {"⚔️ المعركة", "🎒 الحقيبة", "📊 الخصائص"};
    auto menu_principal = Menu(&tabs_entries, &selected_tab);

    auto btn_attaque = Button("⚔️ تنفيذ هجوم عادي", [&] {
        if (!game_engine_.monstres().empty() && game_engine_.monstres()[0].est_vivant()) {
            string log_tour = "";
            heros_.attaquer(game_engine_.monstres()[0], log_tour);
            message_ = log_tour;
            
            if (game_engine_.monstres()[0].est_vivant()) {
                string log_ennemi = "";
                game_engine_.executer_tour_ennemi(heros_, log_ennemi);
                message_ += " | " + log_ennemi;
            }
        } else {
            message_ = "💀 الوحش مهزوم بالفعل! لا داعي للهجوم.";
        }
        screen.RequestAnimationFrame();
    });

    auto btn_magie = Button("🔥 إطلاق سحر عنصري", [&] {
        if (!game_engine_.monstres().empty() && game_engine_.monstres()[0].est_vivant()) {
            string log_tour = "";
            heros_.lancer_magie(game_engine_.monstres()[0], log_tour);
            message_ = log_tour;
            
            if (game_engine_.monstres()[0].est_vivant()) {
                string log_ennemi = "";
                game_engine_.executer_tour_ennemi(heros_, log_ennemi);
                message_ += " | " + log_ennemi;
            }
        } else {
            message_ = "💀 لقد سقط العدو! انتصرت في هذه الجولة.";
        }
        screen.RequestAnimationFrame();
    });

    auto btn_soin = Button("🧪 جرعة إعادة حياة", [&] {
        heros_.soigner(30);
        message_ = "🧪 جرعة سريعة! تم استعادة +30 نقطة حياة (PV).";
        screen.RequestAnimationFrame();
    });

    auto conteneur_actions = Container::Vertical({btn_attaque, btn_magie, btn_soin});

    auto main_container = Container::Tab({
        Renderer(conteneur_actions, [&] {
            return vbox({
                window(text(" خيارات القتال المتاحة ") | color(accent_), vbox({
                    btn_attaque->Render(),
                    btn_magie->Render(),
                    btn_soin->Render()
                })),
                separator(),
                render_combat_screen()
            });
        }),
        Renderer([&] { return render_inventaire_screen(); }),
        Renderer([&] { return render_stats_screen(); })
    }, &selected_tab);

    auto main_renderer = Renderer(Container::Horizontal({menu_principal, main_container}), [&] {
        return vbox({
            text(" 🎮 لعبة القتال التكتيكية بالتبادل (RPG Console) ") | bold | center | color(rose_),
            separator(),
            hbox({
                window(text(" القائمة ") | color(bleu_doux_), menu_principal->Render()) | size(WIDTH, EQUAL, 20),
                window(text(tabs_entries[selected_tab]) | color(mauve_), main_container->Render() | flex)
            }) | flex,
            separator(),
            window(text(" التنبيهات والرسائل ") | color(vert_clair_),
                text(message_.empty() ? "في انتظار قرارك التكتيكي..." : message_)
                | color(message_.find("⚠") != string::npos ? alerte_ : vert_clair_)
            ) | size(HEIGHT, EQUAL, 5),
            text("realise par MDL") | center | dim
        }) | bgcolor(fond_) | border;
    });

    screen.Loop(main_renderer);
}



