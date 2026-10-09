#include "Game/AI/AI/aiGanonBeamOnFloor.h"
#include "Game/AI/aiUnk_71002C52DC.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/Actor/actLastBoss.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"
#include <math/seadMathCalcCommon.h>
#include <cfloat>

namespace uking::ai {

GanonBeamOnFloor::GanonBeamOnFloor(const InitArg& arg) : LastBossShootNormalArrowRoot(arg) {}

// The SafeString members make the original keep the vtable store that a defaulted destructor drops;
// written as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
GanonBeamOnFloor::~GanonBeamOnFloor() { ; }

bool GanonBeamOnFloor::init_(sead::Heap* heap) {
    return LastBossShootNormalArrowRoot::init_(heap);
}

void GanonBeamOnFloor::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossShootNormalArrowRoot::enter_(params);
    mFlags.set(Flag::Changeable);
    _2d4 = false;
    _2d5 = false;
}

bool GanonBeamOnFloor::m38() {
    if (LastBossShootNormalArrowRoot::m38())
        return true;
    if (sub_71002C52DC(mActor, 0.5f))
        return false;
    return _a0 > 0;
}

void GanonBeamOnFloor::calc_() {
    LastBossShootNormalArrowRoot::calc_();

    if (!isCurrentChild("準備")) {
        if (auto* controller = mActor->getCharacterController()) {
            sub_71007377D4(controller, 0.98f);
            sub_7100738660(controller, 0.8f);
        }
        return;
    }

    const bool was_turning = _2d4;
    auto* as_list = mActor->getASList();
    if (as_list && as_list->x(41, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        sub_71003E4208();
        sub_7100740F1C(_298, mActor);
    }

    if (_2d4) {
        if (as_list &&
            !as_list->x(22, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
            changeAS(mTurnAS_s.cstr(), true, 0, 0);
        }
    } else if (was_turning) {
        changeAS("Attack_Eye_Loop", true, 0, 0);
    }
}

// NON_MATCHING: stack/vector scheduling and the native duplicated angle-test shape differ.
void GanonBeamOnFloor::sub_71003E4208() {
    sub_710073FA94(&_298, mActor);
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    const sead::Vector3f gravity = controller->get70();
    const f32 length = gravity.length();
    sead::Vector3f up = -gravity;
    if (length > 0.0f)
        up *= 1.0f / length;
    if (length < FLT_EPSILON)
        up = sead::Vector3f::ey;
    sead::Vector3f target;
    m37(&target);
    target -= mActor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&target, target, up);
    target.normalize();
    sead::Vector3f forward = mActor->getMtx().getBase(2);
    ksys::util::sub_71011EFA00(&forward, forward, up);
    forward.normalize();
    _2bc.lerp(0.16f, 0.16f, 0.016f);
    _2bc.updateStats();
    const f32 start_angle = *mTurnStartAng_s;
    if (start_angle != 0.0f) {
        const f32 threshold = _2d4 ? start_angle * 0.1f : start_angle;
        if (forward.dot(target) >= sead::Mathf::cos(threshold)) {
            _2d4 = false;
            _2bc.lerp(0.0f, 0.16f, 0.016f);
            return;
        }
    }
    sub_710074006C(&_298, target, up, true, *mTurnRate_s, _2bc.value, _2bc.value * 0.1f);
    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, forward, target, sead::Vector3f::ey);
    mActor->getASList()->x_6(9, 0, (angle * 57.295776f) * axis.y);
    _2d4 = true;
}

void GanonBeamOnFloor::leave_() {
    LastBossShootNormalArrowRoot::leave_();
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor))
        boss->_14e8.reset(0x200);
}

void GanonBeamOnFloor::loadParams_() {
    LastBossShootNormalArrowRoot::loadParams_();
    getStaticParam(&mTurnStartAng_s, "TurnStartAng");
    getStaticParam(&mKeepMinDist_s, "KeepMinDist");
    getStaticParam(&mTurnRate_s, "TurnRate");
    getStaticParam(&mWalkAS_s, "WalkAS");
    getStaticParam(&mTurnAS_s, "TurnAS");
}

}  // namespace uking::ai
