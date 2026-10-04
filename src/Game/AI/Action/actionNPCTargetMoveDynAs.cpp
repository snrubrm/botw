#include "Game/AI/Action/actionNPCTargetMoveDynAs.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

NPCTargetMoveDynAs::NPCTargetMoveDynAs(const InitArg& arg) : NPCTargetMove(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
NPCTargetMoveDynAs::~NPCTargetMoveDynAs() {
    ;
}

void NPCTargetMoveDynAs::loadParams_() {
    NPCTargetMove::loadParams_();
    getDynamicParam(&mDynASKeyName_d, "DynASKeyName");
}

// NON_MATCHING: identical code with `this` and &mDynASKeyName_d in swapped callee-saved registers (x19/x20)
void NPCTargetMoveDynAs::m34() {
    const sead::SafeString& current = mActor->getASList()->x_1(0, 0);
    if (current != mDynASKeyName_d)
        mActor->getASList()->startAnimationMaybe(-1.0f, -1.0f, mDynASKeyName_d, 0, 0, true);
}

sead::SafeString NPCTargetMoveDynAs::m35() {
    return mDynASKeyName_d;
}

}  // namespace uking::action
