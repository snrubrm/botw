#include "Game/AI/AI/aiLastBossShootGaleArrowRoot.h"
#include <prim/seadSafeString.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

LastBossShootGaleArrowRoot::LastBossShootGaleArrowRoot(const InitArg& arg)
    : LastBossShootNormalArrowRoot(arg) {}

LastBossShootGaleArrowRoot::~LastBossShootGaleArrowRoot() = default;

bool LastBossShootGaleArrowRoot::init_(sead::Heap* heap) {
    return LastBossShootNormalArrowRoot::init_(heap);
}

void LastBossShootGaleArrowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossShootNormalArrowRoot::enter_(params);
}

void LastBossShootGaleArrowRoot::calc_() {
    LastBossShootNormalArrowRoot::calc_();
}

void LastBossShootGaleArrowRoot::leave_() {
    LastBossShootNormalArrowRoot::leave_();
    if (_a0 != 0)
        return;

    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        sead::FormatFixedSafeString<32> name("%s%d", mPartsName_s.cstr(), _a0);
        if (enemy->getActorPartsActor(name).hasProcInCalcState()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
            accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        }
    }
    if (mActor->getConnectedCalcChild())
        mActor->resetConnectedCalcChild(false);
}

void LastBossShootGaleArrowRoot::loadParams_() {
    LastBossShootNormalArrowRoot::loadParams_();
}

}  // namespace uking::ai
