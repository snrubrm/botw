#include "Game/Actor/AI/aiTargetLastDamagedPos.h"
#include "Game/Actor/actEnemy.h"

namespace uking::ai {

TargetLastDamagedPos::TargetLastDamagedPos(const InitArg& arg) : TargetActorPos(arg) {}

TargetLastDamagedPos::~TargetLastDamagedPos() = default;

bool TargetLastDamagedPos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetLastDamagedPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetLastDamagedPos::calc_() {
    TargetActorPos::calc_();
}

void TargetLastDamagedPos::leave_() {
    TargetActorPos::leave_();
}

void TargetLastDamagedPos::loadParams_() {
    TargetActorPos::loadParams_();
}

void TargetLastDamagedPos::m35(sead::Vector3f* pos) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e08._10.getTranslation(*pos);
    else
        pos->set(0, 0, 0);
}

}  // namespace uking::ai
