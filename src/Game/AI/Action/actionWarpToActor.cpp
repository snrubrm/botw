#include "Game/AI/Action/actionWarpToActor.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

WarpToActor::WarpToActor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpToActor::~WarpToActor() = default;

bool WarpToActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpToActor::loadParams_() {
    getDynamicParam(&mDestinationX_d, "DestinationX");
    getDynamicParam(&mDestinationY_d, "DestinationY");
    getDynamicParam(&mDestinationZ_d, "DestinationZ");
    getDynamicParam(&mDirectionY_d, "DirectionY");
    getDynamicParam(&mRotToVec3f_d, "RotToVec3f");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mGameDataVec3fRotDir_d, "GameDataVec3fRotDir");
}

bool WarpToActor::oneShot_() {
    if (!mActor)
        return false;

    _98.set(mActor->getScale());
    m32();
    mActor->setMtx(_68, false, true);
    if (auto* npc = sead::DynamicCast<uking::act::NPC>(mActor)) {
        npc->_10a4 = _68.m[1][3];
        npc->_fe8 |= 2;
    }
    return true;
}

}  // namespace uking::action
