#include "Game/UI/euiScreen.h"

namespace eui {

// 0x7100be97fc
void Screen::adjstBoxCursor(sead::BoundBox2<f32>*, const BoxCursorNode*) const {}

// 0x7100beaab4
void Screen::draw(const DrawInfoEx::RenderBufferInfo* info) {
    doDraw_(info);
}

// 0x7100beaad8
const char* Screen::getMessageName_() const {
    return m15();
}

// 0x7100beaaf0
bool Screen::isPlayPartsInOut_() const {
    return false;
}

// 0x7100beaaf8
bool Screen::isDisallowHitLowerScreenOnButtonHit_() const {
    return true;
}

// 0x7100bead18
void Screen::doLoadResource_(sead::Heap*) {}

// 0x7100beae0c
bool Screen::isForceGlbMtxDirty_() const {
    return false;
}

// 0x7100beaebc
void* Screen::getElinkSystem_() const {
    return nullptr;
}

// 0x7100beaecc
s32 Screen::getSlink2LocalPropertyNum_() const {
    return 0;
}

// 0x7100beaed4
void Screen::setSlink2PropertyDefinition_(xlink2::UserInstanceSLink*) {}

// 0x7100beabb8
void Screen::doAfterBuildLayout_(sead::Heap*) {}

// 0x7100beadf8
void Screen::doInitialize_(sead::Heap*) {}

// 0x7100be9df0
void Screen::doUpdate_() {}

// 0x7100beadfc
void Screen::doOpenStart_() {}

// 0x7100beae00
void Screen::doOpenEnd_() {}

// 0x7100beae04
void Screen::doCloseStart_() {}

// 0x7100beae08
void Screen::doCloseEnd_() {}

// 0x7100beae9c
void Screen::doButtonOnStart_(AnimButton*) {}

// 0x7100beaea0
void Screen::doButtonOnEnd_(AnimButton*) {}

// 0x7100beaea4
void Screen::doButtonOffStart_(AnimButton*) {}

// 0x7100beaea8
void Screen::doButtonOffEnd_(AnimButton*) {}

// 0x7100beaeac
void Screen::doButtonDownStart_(AnimButton*) {}

// 0x7100beaeb0
void Screen::doButtonDownEnd_(AnimButton*) {}

// 0x7100beaeb4
void Screen::doButtonCancelStart_(AnimButton*) {}

// 0x7100beaeb8
void Screen::doButtonCancelEnd_(AnimButton*) {}

}  // namespace eui
