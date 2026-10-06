#include "Game/AI/Action/actionGiantArmorBurned.h"
#include "Game/Actor/actEnemy.h"

namespace uking::action {

GiantArmorBurned::GiantArmorBurned(const InitArg& arg) : GiantArmorAction(arg) {}

GiantArmorBurned::~GiantArmorBurned() = default;

bool GiantArmorBurned::init_(sead::Heap* heap) {
    return GiantArmorAction::init_(heap);
}

void GiantArmorBurned::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantArmorAction::enter_(params);
}

void GiantArmorBurned::leave_() {
    GiantArmorAction::leave_();
}

void GiantArmorBurned::loadParams_() {
    GiantArmorAction::loadParams_();
}

void GiantArmorBurned::calc_() {
    GiantArmorAction::calc_();
}

bool GiantArmorBurned::m32() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        return enemy->m151(2);
    return false;
}

}  // namespace uking::action
