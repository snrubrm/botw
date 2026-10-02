#include "Game/AI/Action/actionAnmDrivenSpeedBackWalk.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

AnmDrivenSpeedBackWalk::AnmDrivenSpeedBackWalk(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnmDrivenSpeedBackWalk::~AnmDrivenSpeedBackWalk() = default;

bool AnmDrivenSpeedBackWalk::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: scheduling of the SafeString temporary stores
void AnmDrivenSpeedBackWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mActor->getCharacterController())
        return;

    if (auto* rideable = mActor->m132())
        rideable->_18.sub_7100E786F0("BackWalk");
    else
        playAS("BackWalk", true, 0, 0, -1.0f);

    const f32 time = *mTime_s;
    _78 = ksys::Timer(time, time);
    _84 = ksys::Timer(20, 20);
    sub_710073FA90(&_54, mActor);
    _50 = mActor->getAngVelocity().length();
    mFlags.set(Flag::Changeable);
}

void AnmDrivenSpeedBackWalk::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnmDrivenSpeedBackWalk::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mRotAddRatio_s, "RotAddRatio");
    getStaticParam(&mFinishDist_s, "FinishDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: the original computes each "up" vector (-get70() normalised, else ey) in registers and
// stores it once (as if returned by value from an inline helper); ours normalises it in place in
// its stack slot. Also `_78.value > eps` (b.ls in the original) and &_84 kept in a register.
void AnmDrivenSpeedBackWalk::calc_() {
    auto* cc = mActor->getCharacterController();
    if (!cc) {
        setFailed();
        return;
    }

    sead::Vector3f up = -cc->get70();
    if (up.normalize() < sead::Mathf::epsilon())
        up.set(sead::Vector3f::ey);

    sead::Vector3f dir;
    mActor->getMtx().getTranslation(dir);
    dir -= *mTargetPos_d;
    ksys::util::sub_71011EFA00(&dir, dir, up);
    const f32 dist = dir.normalize();

    sub_710073FA94(&_54, mActor);
    if (dist > *mFinishDist_s + sub_71007320F0(mActor, *mWeaponIdx_s) &&
        _78.value <= sead::Mathf::epsilon()) {
        setFinished();
        return;
    }

    if (isLandedMaybe(mActor, false)) {
        _84.update();
        if (_84.value <= sead::Mathf::epsilon())
            setFailed();
    } else {
        _84 = ksys::Timer(10.0f, 10.0f);
    }

    if (_78.value > sead::Mathf::epsilon())
        _78.update();

    if (sub_710072FEC4(mActor, dir, 2.0f, nullptr, true, nullptr)) {
        setFailed();
        return;
    }

    ksys::VFR::lerp(&_50, *mRotSpd_s, 0.24f, *mRotSpd_s * 0.2f, *mRotSpd_s * 0.05f);

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    sead::Vector3f up2 = -cc->get70();
    if (up2.normalize() < sead::Mathf::epsilon())
        up2.set(sead::Vector3f::ey);
    ksys::util::sub_71011EFA00(&front, front, up2);
    front.normalize();

    if ((-dir).dot(front) >= -4.371139e-08f) {
        const sead::Vector3f back = -dir;
        sead::Vector3f up3 = -cc->get70();
        if (up3.normalize() < sead::Mathf::epsilon())
            up3.set(sead::Vector3f::ey);
        sub_710074006C(&_54, back, up3, true, *mRotAddRatio_s, *mRotSpd_s, *mRotSpd_s * 0.1f);
    } else {
        const sead::Vector3f back = -dir;
        sead::Vector3f up3 = -cc->get70();
        if (up3.normalize() < sead::Mathf::epsilon())
            up3.set(sead::Vector3f::ey);
        sub_710074006C(&_54, back, up3, true, *mRotAddRatio_s, *mRotSpd_s, *mRotSpd_s * 0.4f);
    }

    const sead::Vector3f& anim_move = mActor->getASList()->sub_710115D2D4();
    const f32 speed = sead::Vector2f(anim_move.x, anim_move.z).length();
    sead::Vector3f back_dir;
    mActor->getMtx().getBase(back_dir, 2);
    back_dir = -back_dir;
    sub_7100737708(cc, speed);
    sub_710072C1B4(cc, back_dir);
    sub_7100740E04(_54, cc);
}

}  // namespace uking::action
