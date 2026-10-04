#include "Game/AI/Action/actionBackStepAttack.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include <cmath>
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

BackStepAttack::BackStepAttack(const InitArg& arg) : BackStepBase(arg) {}

BackStepAttack::~BackStepAttack() = default;

void BackStepAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    BackStepBase::enter_(params);
    _138 = -1;
    setDamageCallbackTiming(mActor, 4, &_d8);
}

void BackStepAttack::leave_() {
    BackStepBase::leave_();
    sub_71005DA114(mActor, &_d8);
    sub_71005D79AC(mActor, *mWeaponIdx_s, act::Unk_71002edaec(1));
}

void BackStepAttack::loadParams_() {
    BackStepBase::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mMoveDist_s, "MoveDist");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
}

// NON_MATCHING: the original merges the `_138 = state` stores of the first two branches (state in w20) and keeps
// the query below the request struct on the stack; ours stores per branch
void BackStepAttack::calc_() {
    if (sub_71005DAFB0(mActor)) {
        setFailed();
        return;
    }
    BackStepBase::calc_();
    const f32 range = sub_71007322E8(mActor, *mWeaponIdx_s);
    sub_71005DAB2C(mActor, range + *mJustAvoidSideDist_s, range + *mJustAvoidBackDist_s,
                   *mJustAvoidAngle_s, 0);
    int state;
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD66C(mActor, &query, 0, 0)) {
        _10c = query._10;
        sub_71000B362C();
        state = 0;
        _138 = state;
    } else if (sub_71005DD74C(mActor, nullptr, 0, 0)) {
        sub_71005D79AC(mActor, *mWeaponIdx_s, uking::act::Unk_71002edaec(1));
        state = 1;
        _138 = state;
    } else {
        state = _138;
    }
    switch (state) {
    case 1:
        _c8 *= *mStopSpeedRatio_s;
        _c8.updateStats();
        break;
    case 0:
        break;
    default:
        return;
    }
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E7F0(_c8.value * 30.0f);
        sub_710072C1B4(controller, _100);
    }
}

void BackStepAttack::sub_71000B362C() {
    sub_71005D7ADC(mActor, *mWeaponIdx_s, 2, nullptr, nullptr, 1, 1, 0, 1, 1.0f, 1.0f);
    mActor->getMtx().getBase(_100, 2);
    f32 v = _10c;
    const f32 diff = 0.0f - v;
    if (diff <= 1.1920929e-07f && diff >= -1.1920929e-07f) {
        _10c = 1.0f;
        v = 1.0f;
    }
    const f32 speed = *mMoveDist_s / v;
    _c8.value = speed;
    _c8.prev_value = speed;
    _c8.updateStats();
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E7F0(_c8.value * 30.0f);
        sub_710072C1B4(controller, _100);
    }
}

void BackStepAttack::m40() {
    if (_138 != -1) {
        if (auto* controller = mActor->getCharacterController())
            sub_7100738660(controller, 0.1f);
        return;
    }
    sub_71000B4170();
}

void BackStepAttack::m34() {
    playAS("BackStepStart", false, 0, 0, -1.0f);
}

void BackStepAttack::m35() {
    playAS("BackStep", false, 0, 0, -1.0f);
}

void BackStepAttack::m36() {
    playAS("BackStepPreLand", false, 0, 0, -1.0f);
}

void BackStepAttack::m37() {
    playAS("AttackStep", false, 0, 0, -1.0f);
}

}  // namespace uking::action
