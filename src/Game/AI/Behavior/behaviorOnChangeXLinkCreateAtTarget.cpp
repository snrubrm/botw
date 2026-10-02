#include "Game/AI/Behavior/behaviorOnChangeXLinkCreateAtTarget.h"

namespace uking::behavior {

OnChangeXLinkCreateAtTarget::OnChangeXLinkCreateAtTarget(const InitArg& arg)
    : OnChangeXLinkCreate(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
OnChangeXLinkCreateAtTarget::~OnChangeXLinkCreateAtTarget() {
    ;
}

bool OnChangeXLinkCreateAtTarget::m6(sead::Heap* heap) {
    if (!OnChangeXLinkCreate::m6(heap))
        return false;
    sub_7100630570();
    return true;
}

void OnChangeXLinkCreateAtTarget::m7() {
    OnChangeXLinkCreate::m7();
}

void OnChangeXLinkCreateAtTarget::m8() {
    OnChangeXLinkCreate::m8();
}

void OnChangeXLinkCreateAtTarget::m9() {
    OnChangeXLinkCreate::m9();
}

void OnChangeXLinkCreateAtTarget::loadParams() {
    OnChangeXLinkCreate::loadParams();
    getStaticParam(&mTargetUniqueName_s, "TargetUniqueName");
}

}  // namespace uking::behavior
