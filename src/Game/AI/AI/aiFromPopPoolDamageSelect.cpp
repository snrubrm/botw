#include "Game/AI/AI/aiFromPopPoolDamageSelect.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

FromPopPoolDamageSelect::FromPopPoolDamageSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FromPopPoolDamageSelect::~FromPopPoolDamageSelect() = default;

bool FromPopPoolDamageSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool FromPopPoolDamageSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool FromPopPoolDamageSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FromPopPoolDamageSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* mgr = sead::DynamicCast<dmg::DamageManager>(mActor->getDamageMgr());
    if (mgr && mgr->getDamageType() == 9)
        changeChild("ストップタイマー", params);
    else
        changeChild("非ストップタイマー", params);
}

void FromPopPoolDamageSelect::calc_() {}

void FromPopPoolDamageSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FromPopPoolDamageSelect::loadParams_() {}

}  // namespace uking::ai
