#include "Interface.h"
#include <iostream>

using namespace std;

int main() {
    try {
        Ui game_ui;
        game_ui.lancer();
        
    } catch (const exception& e) {
        cerr << "❌ حدث خطأ غير متوقع أثناء تشغيل اللعبة: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "❌ حدث خطأ مجهول أدى إلى توقف اللعبة." << endl;
        return 1;
    }

    return 0;
}








