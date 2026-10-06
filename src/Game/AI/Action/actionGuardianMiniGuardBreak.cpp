#include "Game/AI/Action/actionGuardianMiniGuardBreak.h"

namespace uking::action {

GuardianMiniGuardBreak::GuardianMiniGuardBreak(const InitArg& arg) : GuardBreak(arg) {}

GuardianMiniGuardBreak::~GuardianMiniGuardBreak() = default;

void GuardianMiniGuardBreak::loadParams_() {
    GuardBreak::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mGuardBreakASName_s, "GuardBreakASName");
    getStaticParam(&mOtherASName_s, "OtherASName");
}

int GuardianMiniGuardBreak::m33() {
    return -1;
}

void GuardianMiniGuardBreak::m34() {}

void GuardianMiniGuardBreak::m32() {
    for (int i = 0; i < 4; ++i) {
        if (i == 0 || *mASSlot_s == i)
            playAS(mGuardBreakASName_s.cstr(), false, i, 0, -1.0f);
        else
            playAS(mOtherASName_s.cstr(), true, i, 0, -1.0f);
    }
}

}  // namespace uking::action
