#include "Game/Actor/AI/aiHorseRideChargeAttack.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/System/CameraMgr.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

HorseRideChargeAttack::HorseRideChargeAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseRideChargeAttack::~HorseRideChargeAttack() = default;

bool HorseRideChargeAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRideChargeAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _98 = false;
    _9c = ksys::Timer(8, 8);
    changeToCommand();
}

void HorseRideChargeAttack::changeToCommand() {
    _60.x();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("指令", &pack);
}

// NON_MATCHING: register allocation (epsilon / position) and the final bool conversion of the rider test.
void HorseRideChargeAttack::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("指令")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("待機", &pack);
        } else if (child->isFailed()) {
            setFailed();
        } else {
            setFinished();
        }
    } else if (child->isChangeable()) {
        if (_98)
            setFinished();
        if (_60._30)
            setFinished();
        if (_9c.value <= sead::Mathf::epsilon())
            setFinished();
        if (!isCurrentChild("指令")) {
            const sead::Vector3f pos = mActor->getMtx().getTranslation();
            const sead::Vector3f& target = *mTargetPos_d;
            const sead::Vector3f up = getUpDir(mActor);
            sead::Vector3f to_target = target;
            to_target -= pos;
            ksys::util::sub_71011EFA00(&to_target, to_target, up);
            to_target.normalize();
            sead::Vector3f front;
            mActor->getMtx().getBase(front, 2);
            ksys::util::sub_71011EFA00(&front, front, up);
            front.normalize();
            if (!(to_target.dot(front) >= sead::Mathf::cos(*mAttackableAngle_s)))
                setFinished();
        }
    }

    if (!_98) {
        if (sub_71005DAA70(mActor, *mWeaponIdx_s)) {
            _98 = true;
        } else if (hasAttackInfo(mActor)) {
            _98 = true;
        } else {
            auto* rider = sub_71005D7348(mActor);
            _98 = rider && hasAttackInfo(rider);
        }
    }

    if (ksys::sub_7100D8C658(mActor->get454(), mActor->getScale().x * 0.8f))
        _9c = ksys::Timer(8, 8);
    else
        _9c.update();
    child->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void HorseRideChargeAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRideChargeAttack::loadParams_() {
    getStaticParam(&mUpperBodyASSlot_s, "UpperBodyASSlot");
    getStaticParam(&mLowerBodyASSlot_s, "LowerBodyASSlot");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mAttackableAngle_s, "AttackableAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool HorseRideChargeAttack::handleMessage_(const ksys::Message* message) {
    return _60.m2(*message);
}

}  // namespace uking::ai
