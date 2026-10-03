#include "Game/AI/AI/aiGuardianMini2ndBattle.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "Game/AI/AI/aiGuardianMiniRoot.h"

namespace uking::ai {

GuardianMini2ndBattle::GuardianMini2ndBattle(const InitArg& arg) : GuardianMiniBattle(arg) {}

GuardianMini2ndBattle::~GuardianMini2ndBattle() = default;

void GuardianMini2ndBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianMiniBattle::enter_(params);
}

void GuardianMini2ndBattle::leave_() {
    GuardianMiniBattle::leave_();
}

void GuardianMini2ndBattle::loadParams_() {
    GuardianMiniBattle::loadParams_();
    getStaticParam(&mAttackHitNum_s, "AttackHitNum");
    getStaticParam(&mCounterStopTime_s, "CounterStopTime");
}

void GuardianMini2ndBattle::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("反撃終了")) {
            sub_7100381ED4();
            m37();
            return;
        }
    }

    if (getCurrentChild()->isChangeable()) {
        if (isCurrentChild("反撃")) {
            if (*mAttackHitNum_s < 1)
                return;
            if (_1c8 < *mAttackHitNum_s)
                return;
            if (!(_1d0.value <= sead::Mathf::epsilon()))
                _1d0.update();
            if (!(_1d0.value <= sead::Mathf::epsilon()))
                return;
            changeChild("反撃終了");
            return;
        }
    }
    GuardianMiniBattle::calc_();
}

void GuardianMini2ndBattle::m44(ksys::act::ai::InlineParamPack* params) {
    _1c8 = 0;
    _1d0 = ksys::Timer(*mCounterStopTime_s, *mCounterStopTime_s);
    _1cc = false;
}

bool GuardianMini2ndBattle::m45() {
    if (!sub_71004282EC(mActor))
        return false;
    if (_1cc)
        return true;
    return GuardianMiniBattle::m45();
}

bool GuardianMini2ndBattle::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x8000043)
        ++_1c8;
    return GuardianMiniBattle::handleMessage_(message);
}

}  // namespace uking::ai
