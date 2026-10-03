#include "Game/AI/Behavior/behaviorOnStateXLinkCreate.h"

namespace uking::behavior {

OnStateXLinkCreate::OnStateXLinkCreate(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
OnStateXLinkCreate::~OnStateXLinkCreate() {
    ;
}

bool OnStateXLinkCreate::m6(sead::Heap* heap) {
    return true;
}

void OnStateXLinkCreate::m7() {}

void OnStateXLinkCreate::m8() {
    if (!m14())
        return;
    if (mKey_s.isEmpty())
        return;
    xlinkSearchAndEmit(mActor, mKey_s.cstr(), 2, &_58);
}

void OnStateXLinkCreate::m9() {
    sub_7100631CAC();
}

void OnStateXLinkCreate::sub_7100631CAC() {
    if (*mIsEndKill_s) {
        _58.mELink.kill();
        _58.mSLink.fade();
    } else if (*mIsEndFade_s) {
        _58.fadeXLink();
    }

    if (!mEndKey_s.isEmpty())
        xlinkSearchAndEmit(mActor, mEndKey_s.cstr(), 2, nullptr);
}

void OnStateXLinkCreate::loadParams() {
    getStaticParam(&mIsEndKill_s, "IsEndKill");
    getStaticParam(&mIsEndFade_s, "IsEndFade");
    getStaticParam(&mKey_s, "Key");
    getStaticParam(&mEndKey_s, "EndKey");
}

}  // namespace uking::behavior
