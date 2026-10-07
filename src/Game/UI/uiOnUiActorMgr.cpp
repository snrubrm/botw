#include "Game/UI/uiOnUiActorMgr.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerArmors.h"

namespace uking::ui {

OnUiActorMgr* OnUiActorMgr::sInstance = nullptr;

void OnUiActorMgr::sub_7100906F08(ksys::act::Actor* actor) {
    if (!mActor)
        mActor = actor;
}

bool OnUiActorMgr::sub_710090AB4C() const {
    return !mArmors || mArmors->hasNoPartBeingCreated();
}

// 0x710090ab60
ksys::act::Actor* OnUiActorMgr::getActor() const {
    return mActor;
}

}  // namespace uking::ui
