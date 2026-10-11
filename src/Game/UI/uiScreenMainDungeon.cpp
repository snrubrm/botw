#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiTagProcessor.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiUI.h"

namespace uking::ui {

// The original D1 keeps the vtable stores (upstream GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
ScreenMainDungeon::~ScreenMainDungeon() { ; }

// 0x71010a5068
eui::TagProcessor* ScreenMainDungeon::doCreateTagProcessor_(sead::Heap* heap) {
    return ScreenBase::doCreateTagProcessor_(heap);
}

// 0x71010a486c
const char* ScreenMainDungeon::getLayoutName_() const {
    return "MainDungeon_00";
}

// 0x71010a4f8c
void ScreenMainDungeon::m93(sead::Heap* heap) {
    _2fc = 3;
    _300 = 3;
    _9d0 = sub_7100BEAFB0("Pa_Message_00");
    _9d8 = sub_7100BEAFB0("Pa_Title_00");
    _9e0 = sub_7100BEAFB0("Pa_LocationNameS_00");
    _9e8 = ScreenBase::doCreateTagProcessor_(heap);
    _9e8->setRubyEnabled(true);
    _9d0->SetTagProcessor(_9e8);
    _9f0 = sub_7100986160(_9d0, "N_Capture_00");
    _9f8 = sub_7100986160(_9d0, "N_Capture_01");
    _a00 = sub_7100986160(_9d8, "N_Capture_00");
    _a08 = sub_7100986160(_9e0, "N_Capture_00");
}

// 0x71010a53f0
void ScreenMainDungeon::m101() {
    _9d0->startAnimCloseImpl_(false, true);
    _9d8->startAnimCloseImpl_(false, true);
    _9e0->startAnimCloseImpl_(false, true);
}

// 0x71010a4f24
void ScreenMainDungeon::sub_71010A4F24() {
    _2fc = 2;
    open(1);
}

// 0x71010a4f3c
void ScreenMainDungeon::sub_71010A4F3C() {
    if (_304 == 3) {
        _300 = 2;
        open(1);
    }
}

// 0x71010a4f64
void ScreenMainDungeon::sub_71010A4F64() {
    if (_300 == 3) {
        _304 = 2;
        open(1);
    }
}

}  // namespace uking::ui
