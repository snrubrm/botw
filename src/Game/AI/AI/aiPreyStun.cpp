#include "Game/AI/AI/aiPreyStun.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actEnemy.h"

namespace uking::ai {

PreyStun::PreyStun(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyStun::~PreyStun() = default;

bool PreyStun::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PreyStun::enter_(ksys::act::ai::InlineParamPack* params) {
    _40.reset(*mStunTime_s);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (!enemy->_e84.isOnBit(3))
            setFailed();
    }
    changeChild("気絶中");
}

void PreyStun::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        setFinished();
        return;
    }

    if (!isCurrentChild("気絶中") || _40.value <= sead::Mathf::epsilon())
        return;

    _40.update();
    if (_40.value <= sead::Mathf::epsilon())
        changeChild("復帰");
}

void PreyStun::leave_() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.resetBit(3);
}

void PreyStun::loadParams_() {
    getStaticParam(&mStunTime_s, "StunTime");
}

}  // namespace uking::ai
