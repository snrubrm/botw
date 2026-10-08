#include "Game/UI/uiOnUiActorMgr.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerArmors.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

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

// 0x7100906e70
void OnUiActorMgr::sub_7100906E70() {
    if (mArmors) {
        delete mArmors;
        mArmors = nullptr;
    }
    if (mActor) {
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        mActor = nullptr;
    }
    if (_50.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_50, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        _50.reset();
    }
    _1f4.makeAllZero();
}

}  // namespace uking::ui
