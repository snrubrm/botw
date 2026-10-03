#include "Game/AI/aiUnk_71025b2aa8.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/System/Timer.h"

// The dialog unit's methods (0x7100721de4-0x7100721fb4, in the TU after Message3DText).
//
// They are called on `unit->Data` pointers that can be null when the object behind the AI tree
// variable is not a Unk_71025b2aa8 (the callers pass `mov x0, xzr`).

// NON_MATCHING: the original loads request->_14 before the store to `_8` (scheduling).
void Unk_71025b2aa8Data::sub_7100721DE4(const Request* request) {
    if (_14)
        return;
    if (!request->_0 || !request->_8)
        return;
    auto* ui = uking::ui::UI::instance();
    if (!ui)
        return;

    u32 mode = request->_10;
    f32 time = -1.0f;
    _10 = mode;
    if (mode >= 2) {
        if (mode == 3) {
            mode = 4;
        } else if (mode == 2) {
            time = request->_18;
            mode = 1;
        } else {
            return;
        }
    }
    _0 = time;
    _8 = request->_20;
    ui->messageDialogViewStyleStuff(*request->_0, *request->_8, request->_20, 0.0f, mode,
                                    request->_14 == 1 || request->_14 == 2, false);
}

void Unk_71025b2aa8Data::sub_7100721E80() {
    if (_0 > 0) {
        ksys::Timer::update(&_0, -1.0f);
        if (_0 <= 0)
            sub_7100721EFC();
    }
}

void Unk_71025b2aa8Data::sub_7100721EFC() {
    if (_10 != -1) {
        if (auto* ui = uking::ui::UI::instance()) {
            if (ui->sub_71010A5888())
                ui->sub_71010A6B98(_8);
        }
        _10 = -1;
    }
}

void Unk_71025b2aa8Data::sub_7100721F54() {
    sub_7100721EFC();
    _14 = true;
}

bool Unk_71025b2aa8Data::sub_7100721FB4() const {
    auto* ui = uking::ui::UI::instance();
    return ui && ui->sub_71010A5888();
}
