#include "Game/Actor/Behavior/behaviorOnChangeXLinkCreate.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::behavior {

OnChangeXLinkCreate::OnChangeXLinkCreate(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
OnChangeXLinkCreate::~OnChangeXLinkCreate() {
    ;
}

bool OnChangeXLinkCreate::init_(sead::Heap* heap) {
    return true;
}

void OnChangeXLinkCreate::calc() {}

void OnChangeXLinkCreate::enter() {
    m14();
}

void OnChangeXLinkCreate::leave() {}

void OnChangeXLinkCreate::loadParams() {
    getStaticParam(&mKey_s, "Key");
    getStaticParam(&mDoOnChangeAI_s, "DoOnChangeAI");
}

void OnChangeXLinkCreate::onChangeChild() {
    if (*mDoOnChangeAI_s)
        m14();
}

void OnChangeXLinkCreate::m14() {
    xlinkSearchAndEmit(mActor, mKey_s.cstr(), 2, nullptr);
}

}  // namespace uking::behavior
