#include "Game/AI/Action/actionAreaLocation.h"
#include "Game/gameSceneSubsys14.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ui {
// 0x7100a9a664 (uiMiscFacade.cpp)
bool sub_7100A9A664(const void* a0, s32* out);
}  // namespace uking::ui

namespace uking::action {

AreaLocation::AreaLocation(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AreaLocation::~AreaLocation() = default;

bool AreaLocation::init_(sead::Heap* heap) {
    Unk_71023677d8_Payload::Data data;
    data.mLink.acquire(mActor, false);
    data.mMessageId = mMessageID_m;
    data.mPriority = *mLocationPriority_m;
    s32 area_id;
    data.mAreaId = ui::sub_7100A9A664(&mMessageID_m, &area_id) ? area_id : -1;
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_40._18.mLock);
        _40._18._0 = true;
        _40._18._8.sub_7100903158(data);
    }
    return true;
}

// NON_MATCHING: identical instructions; the original computes &_40 (the call argument) after the unlock, we compute it
// before the lock
void AreaLocation::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor->checkBasicSig() != _38) {
        const bool active = !_38;
        _38 = active;
        _40.x(active);
        _40.sub_710070DBB0(*GameSceneSubsys14::instance()->mTransceiver.getId(), true);
    }
}

void AreaLocation::leave_() {
    if (!_38)
        return;

    _38 = false;
    _40.x(false);
    if (isActorDeletedOrDeleting())
        return;
    _40.sub_710070DBB0(*GameSceneSubsys14::instance()->mTransceiver.getId(), true);
}

void AreaLocation::loadParams_() {
    getMapUnitParam(&mLocationPriority_m, "LocationPriority");
    getMapUnitParam(&mMessageID_m, "MessageID");
}

// NON_MATCHING: same as enter_
void AreaLocation::calc_() {
    if (mActor->checkBasicSig() != _38) {
        const bool active = !_38;
        _38 = active;
        _40.x(active);
        _40.sub_710070DBB0(*GameSceneSubsys14::instance()->mTransceiver.getId(), true);
    }
}

}  // namespace uking::action
