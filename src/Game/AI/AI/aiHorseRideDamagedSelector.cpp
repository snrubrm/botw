#include "Game/AI/AI/aiHorseRideDamagedSelector.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

HorseRideDamagedSelector::HorseRideDamagedSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseRideDamagedSelector::~HorseRideDamagedSelector() = default;

bool HorseRideDamagedSelector::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool HorseRideDamagedSelector::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool HorseRideDamagedSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRideDamagedSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* mgr = sead::DynamicCast<dmg::DamageManager>(mActor->getDamageMgr());
    if (mgr && mgr->checkDamageFlags(17))
        changeChild("騎乗", params);
    else
        changeChild("それ以外", params);
}

void HorseRideDamagedSelector::calc_() {}

void HorseRideDamagedSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRideDamagedSelector::loadParams_() {}

}  // namespace uking::ai
