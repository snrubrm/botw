#include "Game/Actor/Behavior/behaviorOnChangeXLinkCreateAtTarget.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::behavior {

OnChangeXLinkCreateAtTarget::OnChangeXLinkCreateAtTarget(const InitArg& arg)
    : OnChangeXLinkCreate(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
OnChangeXLinkCreateAtTarget::~OnChangeXLinkCreateAtTarget() {
    ;
}

bool OnChangeXLinkCreateAtTarget::init_(sead::Heap* heap) {
    if (!OnChangeXLinkCreate::init_(heap))
        return false;
    sub_7100630570();
    return true;
}

void OnChangeXLinkCreateAtTarget::calc() {
    OnChangeXLinkCreate::calc();
}

void OnChangeXLinkCreateAtTarget::enter() {
    OnChangeXLinkCreate::enter();
}

void OnChangeXLinkCreateAtTarget::leave() {
    OnChangeXLinkCreate::leave();
}

void OnChangeXLinkCreateAtTarget::m14() {
    Unk_71012419b4 handle{};
    xlinkSearchAndEmit(mActor, mKey_s.cstr(), 2, &handle);
    handle.sub_7101241A44(sead::Matrix34f::ident);
    handle.sub_71012419B4(_50);
}

void OnChangeXLinkCreateAtTarget::loadParams() {
    OnChangeXLinkCreate::loadParams();
    getStaticParam(&mTargetUniqueName_s, "TargetUniqueName");
}

}  // namespace uking::behavior
