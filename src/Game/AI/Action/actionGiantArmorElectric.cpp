#include "Game/AI/Action/actionGiantArmorElectric.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

GiantArmorElectric::GiantArmorElectric(const InitArg& arg) : GiantArmorAction(arg) {}

GiantArmorElectric::~GiantArmorElectric() = default;

bool GiantArmorElectric::init_(sead::Heap* heap) {
    return GiantArmorAction::init_(heap);
}

void GiantArmorElectric::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantArmorAction::enter_(params);
    _78 = *mTimeMin_s;
}

void GiantArmorElectric::leave_() {
    GiantArmorAction::leave_();
}

void GiantArmorElectric::loadParams_() {
    GiantArmorAction::loadParams_();
    getStaticParam(&mTimeMin_s, "TimeMin");
}

void GiantArmorElectric::calc_() {
    if (_78 > 0.0f)
        ksys::Timer::update(&_78, -1.0f);
    GiantArmorAction::calc_();
}

bool GiantArmorElectric::m32() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        return enemy->m151(4);
    return false;
}

}  // namespace uking::action
