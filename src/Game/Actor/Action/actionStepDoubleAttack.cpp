#include "Game/Actor/Action/actionStepDoubleAttack.h"
#include <algorithm>
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_71007320F0.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

// NON_MATCHING: store scheduling (the damage callback member's zero stores are ordered differently)
StepDoubleAttack::StepDoubleAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void StepDoubleAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("DoubleAttack", false, 0, 0, -1.0f);
    _bc = mActor->getVelocity();
    _bc.y = 0.0f;
    const f32 speed = _bc.normalize();
    _88.value = speed;
    _88.prev_value = speed;
    _94 = -1.0f;
    _c8 = 0;
    sub_710073FA90(&_98, mActor);
    setDamageCallbackTiming(mActor, 4, &_60);
}

void StepDoubleAttack::leave_() {
    sub_71005D79AC(mActor, *mParams.mWeaponIdx_s, act::Unk_71002edaec(1));
    sub_71005DA114(mActor, &_60);
}

void StepDoubleAttack::loadParams_() {
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mCloseDist_s, "CloseDist");
    getStaticParam(&mParams.mSpeed_s, "Speed");
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getStaticParam(&mParams.mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mParams.mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mParams.mJustAvoidAngle_s, "JustAvoidAngle");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

// NON_MATCHING: same differences as ForkASTrgStepMove::calc_ (TargetPos pointer kept in a register).
void StepDoubleAttack::calc_() {
    ksys::phys::CharacterController* controller;
    if (sub_71005DAFB0(mActor) || !(controller = mActor->getCharacterController())) {
        setFailed();
        return;
    }

    const f32 reach = sub_71007322E8(mActor, *mParams.mWeaponIdx_s);
    sub_71005DAB2C(mActor, reach + *mParams.mJustAvoidSideDist_s,
                   reach + *mParams.mJustAvoidBackDist_s, *mParams.mJustAvoidAngle_s, 0);
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD66C(mActor, &query, 0, 0)) {
        m33(*mParams.mWeaponIdx_s, &query.name, _c8 > 0, 1.0f);
        ++_c8;
    } else if (sub_71005DD74C(mActor, nullptr, 0, 0)) {
        sub_71005D79AC(mActor, *mParams.mWeaponIdx_s, act::Unk_71002edaec(1));
    }

    sub_710073FA94(&_98, mActor);
    ksys::as::ASList::Unk4 step_query;
    if (sub_71005DD5B0(mActor, 0x2f, &step_query, 0, 0)) {
        _94 = step_query._10;
        mActor->getMtx().getBase(_bc, 2);
        sead::Vector3f to_target = *mParams.mTargetPos_d - mActor->getMtx().getTranslation();
        to_target.y = 0.0f;
        const f32 distance = to_target.length();
        const f32 close_dist = *mParams.mCloseDist_s;
        const f32 remaining = std::max(
            distance - (close_dist + sub_71007320F0(mActor, *mParams.mWeaponIdx_s)), 0.0f);
        const f32 speed = remaining / step_query._10 * 1.3f;
        _88.value = speed;
        _88.prev_value = speed;
        _88.setToMin(*mParams.mSpeed_s);
    } else if (_94 > 0.0f) {
        ksys::Timer::update(&_94, -1.0f);
        _88 *= 0.94f;
        sub_7100738660(controller, 0.7f);
    } else {
        _88 *= 0.5f;
        sead::Vector3f dir = *mParams.mTargetPos_d;
        dir -= mActor->getMtx().getTranslation();
        dir.y = 0.0f;
        const sead::Vector3f up = getUpDir(controller->get70());
        ksys::util::sub_71011EFA00(&dir, dir, up);
        dir.normalize();
        sub_710074006C(&_98, dir, up, true, 0.12f, *mParams.mRotSpd_s, *mParams.mRotSpd_s * 0.1f);
        sub_7100740E04(_98, controller);
    }
    _88.updateStats();
    controller->sub_7100F5E7F0(_88.value * 30.0f);
    sub_710072C1B4(controller, mActor->getMtx().getBase(2));
    if (isFinishedAS(0, 0))
        setFinished();
}

bool StepDoubleAttack::isChangeable() const {
    return false;
}

int StepDoubleAttack::m32() {
    return 1;
}

// NON_MATCHING: argument copies at entry are scheduled in another order (regalloc only; same as
// ForkWeaponAttackBase::m32)
void StepDoubleAttack::m33(int weapon_idx, const sead::SafeString* name, bool a3, f32 a4) {
    auto* actor = mActor;
    u32 flags = m32();
    if (a3) {
        flags |= 0x40;
        sub_71005D7ADC(actor, weapon_idx, flags, name, nullptr, 1, 1, 0, 1, a4, 1.0f);
    } else {
        sub_71005D7ADC(actor, weapon_idx, flags, name, nullptr, 1, 1, 0, 1, a4, 1.0f);
    }
}

}  // namespace uking::action
