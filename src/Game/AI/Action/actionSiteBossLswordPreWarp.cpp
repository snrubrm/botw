#include "Game/AI/Action/actionSiteBossLswordPreWarp.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

SiteBossLswordPreWarp::SiteBossLswordPreWarp(const InitArg& arg) : LastBossPreNormalWarp(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SiteBossLswordPreWarp::~SiteBossLswordPreWarp() {
    ;
}

bool SiteBossLswordPreWarp::init_(sead::Heap* heap) {
    return LastBossPreNormalWarp::init_(heap);
}

void SiteBossLswordPreWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossPreNormalWarp::enter_(params);
}

void SiteBossLswordPreWarp::leave_() {
    LastBossPreNormalWarp::leave_();
}

void SiteBossLswordPreWarp::loadParams_() {
    LastBossPreNormalWarp::loadParams_();
    getStaticParam(&mSleepPartsName_s, "SleepPartsName");
}

void SiteBossLswordPreWarp::calc_() {
    LastBossPreNormalWarp::calc_();
    if (sub_71005DD780(mActor, 59, nullptr, 0, 0)) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            if (!mSleepPartsName_s.isEmpty()) {
                if (enemy->getActorPartsActor(mSleepPartsName_s).hasProc()) {
                    ksys::act::ActorConstDataAccess accessor;
                    ksys::act::acquireActor(&enemy->getActorPartsActor(mSleepPartsName_s),
                                            &accessor);
                    if (accessor.isStateCalc())
                        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
                }
            }
        }
    }
}

void SiteBossLswordPreWarp::m34(f32 a1, ksys::act::Actor* actor, bool a3) {
    LastBossPreNormalWarp::m34(a1, actor, a3);
}

}  // namespace uking::action
