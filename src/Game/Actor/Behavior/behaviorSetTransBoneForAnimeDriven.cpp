#include "Game/Actor/Behavior/behaviorSetTransBoneForAnimeDriven.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

SetTransBoneForAnimeDriven::SetTransBoneForAnimeDriven(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
SetTransBoneForAnimeDriven::~SetTransBoneForAnimeDriven() {
    ;
}

bool SetTransBoneForAnimeDriven::init_(sead::Heap* heap) {
    return true;
}

void SetTransBoneForAnimeDriven::calc() {}

void SetTransBoneForAnimeDriven::loadParams() {
    getStaticParam(&mTransBoneName_s, "TransBoneName");
}

void SetTransBoneForAnimeDriven::enter() {
    if (!mActor->getModel())
        return;
    if (auto* as_list = mActor->getASList())
        as_list->sub_710115BAF8(mTransBoneName_s);
}

void SetTransBoneForAnimeDriven::leave() {
    if (auto* list = mActor->getASList())
        list->sub_710115CD0C();
}

}  // namespace uking::behavior
