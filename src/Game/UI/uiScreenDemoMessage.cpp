#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiTagProcessor.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiUI.h"

namespace uking::ui {

// 0x710109e644
ScreenDemoMessage::ScreenDemoMessage() : Screen() {}

ScreenDemoMessage::~ScreenDemoMessage() = default;

// 0x710109e94c
void ScreenDemoMessage::sub_710109E94C() {
    if (_548 != -1)
        close(-1);
}

// 0x710109e96c
void ScreenDemoMessage::sub_710109E96C() {
    _548 = -1;
}

// 0x710109e978
void ScreenDemoMessage::sub_710109E978() {
    _558 = true;
}

// 0x710109e9d4 (CSV unnamed; slot 27)
eui::TagProcessor* ScreenDemoMessage::doCreateTagProcessor_(sead::Heap* heap) {
    auto* processor = ScreenBase::doCreateTagProcessor_(heap);
    processor->setRubyEnabled(true);
    return processor;
}

// 0x710109e984 (slot 93)
void ScreenDemoMessage::m93(sead::Heap*) {
    _550 = mLayout->tryCreateAnimatorAutoWithWarning("Pos", true);
    if (_550)
        _550->Stop(0.0f);
}

// 0x710109e9f0 (slot 94)
void ScreenDemoMessage::m94() {
    if (_558) {
        _548 = 0;
        if (_300.getString()) {
            bool has_next_page = false;
            mLayout->setMessageStringForEachIdWithPage("T_Message_00", _300, &has_next_page, 0, true,
                                                       nullptr);
            x_2();
            _548 = has_next_page ? _548 + 1 : -1;
        }
        _558 = false;
    }
}

// 0x710109ea70 (slot 98)
void ScreenDemoMessage::m98() {
    if (_300.getString()) {
        bool has_next_page = false;
        mLayout->setMessageStringForEachIdWithPage("T_Message_00", _300, &has_next_page, _548, true,
                                                   nullptr);
        x_2();
        _548 = has_next_page ? _548 + 1 : -1;
    }
    if (_550)
        _550->Stop(_559 ? 1.0f : 0.0f);
}

// 0x710109eb08 (slot 101)
void ScreenDemoMessage::m101() {
    if (_548 != -1)
        open(1);
}

// 0x710109ebb4
const char* ScreenDemoMessage::getLayoutName_() const {
    return "MessageDemo_00";
}

}  // namespace uking::ui
