#include "Game/AI/AI/aiDamageTypeSelect.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

DamageTypeSelect::DamageTypeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DamageTypeSelect::~DamageTypeSelect() = default;

bool DamageTypeSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool DamageTypeSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool DamageTypeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DamageTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* damage_mgr = mActor->getDamageMgr();
    if (damage_mgr && damage_mgr->getField50() == *mDamageType_s)
        changeChild("該当", params);
    else
        changeChild("非該当", params);
}

void DamageTypeSelect::calc_() {}

void DamageTypeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DamageTypeSelect::loadParams_() {
    getStaticParam(&mDamageType_s, "DamageType");
}

}  // namespace uking::ai
