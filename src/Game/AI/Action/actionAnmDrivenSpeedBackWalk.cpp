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

// NON_MATCHING: the original keeps &_84 in a callee-saved register (x22) across the Timer::update() call
void AnmDrivenSpeedBackWalk::calc_() {
    auto* cc = mActor->getCharacterController();
    if (!cc) {
        setFailed();
        return;
    }

    const sead::Vector3f up = getUpDir(cc->get70());
    sead::Vector3f dir;
    dir = mActor->getMtx().getTranslation();
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

    if (!(_78.value <= sead::Mathf::epsilon()))
        _78.update();

    if (sub_710072FEC4(mActor, dir, 2.0f, nullptr, true, nullptr)) {
        setFailed();
        return;
    }

    ksys::VFR::lerp(&_50, *mRotSpd_s, 0.24f, *mRotSpd_s * 0.2f, *mRotSpd_s * 0.05f);

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    ksys::util::sub_71011EFA00(&front, front, getUpDir(cc->get70()));
    front.normalize();

    if ((-dir).dot(front) >= -4.371139e-08f) {
        const sead::Vector3f back = -dir;
        sub_710074006C(&_54, back, getUpDir(cc->get70()), true, *mRotAddRatio_s, *mRotSpd_s, *mRotSpd_s * 0.1f);
    } else {
        const sead::Vector3f back = -dir;
        sub_710074006C(&_54, back, getUpDir(cc->get70()), true, *mRotAddRatio_s, *mRotSpd_s, *mRotSpd_s * 0.4f);
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
