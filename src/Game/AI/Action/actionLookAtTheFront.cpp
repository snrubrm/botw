#include "Game/AI/Action/actionLookAtTheFront.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

LookAtTheFront::LookAtTheFront(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LookAtTheFront::~LookAtTheFront() = default;

bool LookAtTheFront::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LookAtTheFront::loadParams_() {
    getDynamicParam(&mIsValid_d, "IsValid");
}

bool LookAtTheFront::oneShot_() {
    if (auto* npc = sead::DynamicCast<uking::act::NPC>(mActor))
        npc->sub_7100022D44(*mIsValid_d, 0, sead::Vector3f::zero, nullptr, sead::Vector3f::zero);
    else
        setFailed();
    return true;
}

}  // namespace uking::action
