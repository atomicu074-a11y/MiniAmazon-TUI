#include "Interface.h"
#include <ftxui/component/screen_interactive.hpp>
#include <iomanip>
#include <sstream>

using namespace ftxui;
using namespace std;

Ui::Ui() {
    rose_ = Color::RGB(245, 194, 231);
    mauve_ = Color::RGB(203, 166, 247);
    bleu_doux_ = Color::RGB(137, 180, 250);
    vert_clair_ = Color::RGB(166, 227, 161);
    fond_ = Color::RGB(30, 30, 46);
    surface_ = Color::RGB(49, 50, 68);
    alerte_ = Color::RGB(243, 139, 168);
    accent_ = Color::RGB(250, 179, 135);
    
    message_ = "تبدأ المغامرة الآن! اختر مهاراتك بعناية.";
}

Element Ui::render_journal_combat() {
    Elements lignes;
    lignes.push_back(text(" 📜 سجل المعركة الأخير:") | bold | color(mauve_));
    lignes.push_back(separator());
    lignes.push_back(text(" [البطل] استخدم ضربة السيف السريعة! ") | color(vert_clair_));
    lignes.push_back(text(" [العدو] تلقى 45 نقطة ضرر. ") | color(alerte_));
    return window(text(" أحداث المعركة "), vbox(move(lignes))) | bgcolor(surface_);
}

void Ui::lancer() {
    auto screen = ScreenInteractive::TerminalOutput();

    int selected_tab = 0;
    vector<string> tabs_entries = {"⚔️ المعركة", "🎒 الحقيبة", "📊 الخصائص"};
    auto menu_principal = Menu(&tabs_entries, &selected_tab);

    auto btn_attaque = Button("⚔️ هجوم عادي", [&] {
        message_ = "لقد قمت بتنفيذ هجوم عادي سريع!";
        screen.RequestAnimationFrame();
    });

    auto btn_magie = Button("🔥 إطلاق سحر", [&] {
        message_ = "تم إطلاق كرة اللهب! (حساب المقاومة تلقائياً عبر Polymorphism)";
        screen.RequestAnimationFrame();
    });

    auto btn_soin = Button("🧪 شرب جرعة علاج", [&] {
        message_ = "تم استخدام جرعة صحة (+50 PV)";
        screen.RequestAnimationFrame();
    });

    auto conteneur_combat = Container::Vertical({btn_attaque, btn_magie, btn_soin});

    auto vue_combat = Renderer(conteneur_combat, [&] {
        return vbox({
            window(text(" الإجراءات المتاحة "), vbox({
                btn_attaque->Render() | border,
                btn_magie->Render() | border,
                btn_soin->Render() | border
            })),
            separator(),
            render_journal_combat()  
        }) | bgcolor(surface_);
    });

    auto vue_inventaire = Renderer([&] {
        return window(text(" 🎒 حقيبة الأدوات المستهلكة "), vbox({
            text("• جرعة صحة حمراء (عدد: 3)") | color(vert_clair_),
            text("• ترياق مانا أزرق  (عدد: 1)") | color(bleu_doux_),
            text("• لفافة سحر النار   (عدد: 2)") | color(accent_)
        })) | bgcolor(surface_);
    });

    auto vue_stats = Renderer([&] {
        return window(text(" 📊 خصائص البطل الحالية "), vbox({
            text(" الاسم  : MARYEM") | bold | color(accent_),
            text(" المستوى: Niv. 1") | color(bleu_doux_),
            text(" نقاط الحياة (PV): [██████████] 100/100") | color(vert_clair_),
            text(" نقاط السحر (MP) : [█████     ] 50/100") | color(mauve_)
        })) | bgcolor(surface_);
    });

    auto main_container = Container::Tab({vue_combat, vue_inventaire, vue_stats}, &selected_tab);

    auto main_renderer = Renderer(Container::Horizontal({menu_principal, main_container}), [&] {
        return vbox({
            text(" 🎮 لعبة القتال بالتبادل (RPG Console) ") | bold | center | color(rose_),
            hbox({
                window(text(" القائمة "), menu_principal->Render()) | size(WIDTH, EQUAL, 20),
                window(text(tabs_entries[selected_tab]) | color(mauve_), main_container->Render() | flex)
            }) | flex,
            window(text(" حالة اللعبة "),
                   text(message_.empty() ? "في انتظار قرارك..." : message_)
                   | color(message_.find("⚠") != string::npos ? alerte_ : vert_clair_)
            ) | size(HEIGHT, EQUAL, 4),
            text("realise par MDL") | center | dim
        }) | bgcolor(fond_) | border;
    });

    screen.Loop(main_renderer);
}




