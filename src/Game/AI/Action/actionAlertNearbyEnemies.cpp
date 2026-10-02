#include "Game/AI/Action/actionAlertNearbyEnemies.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiAwarenessFilters.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

AlertNearbyEnemies::AlertNearbyEnemies(const InitArg& arg) : PlayASForAnimalUnit(arg) {}

AlertNearbyEnemies::~AlertNearbyEnemies() = default;

bool AlertNearbyEnemies::init_(sead::Heap* heap) {
    return PlayASForAnimalUnit::init_(heap);
}

void AlertNearbyEnemies::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASForAnimalUnit::enter_(params);
    _d8 = ksys::Timer(*mAlertTime_s, *mAlertTime_s);
}

void AlertNearbyEnemies::leave_() {
    sub_71005D8D4C(mActor, 0.0f, true, false);
    PlayASForAnimalUnit::leave_();
}

void AlertNearbyEnemies::loadParams_() {
    PlayASForAnimalUnit::loadParams_();
    getStaticParam(&mAlertRange_s, "AlertRange");
    getStaticParam(&mAlertTime_s, "AlertTime");
    getStaticParam(&mNoiseLevel_s, "NoiseLevel");
    getStaticParam(&mUseNoise_s, "UseNoise");
}

void AlertNearbyEnemies::calc_() {
    PlayASForAnimalUnit::calc_();

    if (!(_d8.value <= sead::Mathf::epsilon())) {
        _d8.update();
        return;
    }

    ksys::act::BaseProcLink link;
    link.acquire(mActor, false);
    auto* actor = mActor;
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_80._18.mLock);
        auto& data = _80._18.mData;
        data._0.acquire(actor, false);
        data._10.acquire(actor, false);
        data._20 = 1;
        data._24 = 2;
        data._28 = pos;
        data._34 = 0;
    }

    if (auto* awareness = mActor->getAwareness()) {
        Unk_7102451448 filter;
        while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
            if (entry->_a8 < *mAlertRange_s) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&entry->mLink, &accessor);
                _80.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
            }
        }
        if (*mUseNoise_s)
            sub_71005D8D4C(mActor, *mNoiseLevel_s, true, false);
    }
}

}  // namespace uking::action
