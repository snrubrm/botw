#include "Game/AI/Action/actionSiteBossSwordWhirlSlashChargeBase.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

SiteBossSwordWhirlSlashChargeBase::SiteBossSwordWhirlSlashChargeBase(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossSwordWhirlSlashChargeBase::~SiteBossSwordWhirlSlashChargeBase() = default;

bool SiteBossSwordWhirlSlashChargeBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossSwordWhirlSlashChargeBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    const sead::Vector3f up = getUpDir(controller->get70());
    sub_710073FA90(&_50, mActor);
    sead::Vector3f to_target = *mTargetPos_d;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    to_target -= pos;
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    to_target.normalize();

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    ksys::util::sub_71011EFA00(&front, front, up);
    front.normalize();

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, to_target, sead::Vector3f::ey);
    mActor->getASList()->x_6(9, 0, sead::Mathf::rad2deg(angle) * axis.y);
    playAS("WhirlSlashCharge", false, 0, 0, -1.0f);
    _38.reset(*mChargeTime_s);
    _44.value = *mInitSpeed_s;
    _44.prev_value = *mInitSpeed_s;
}

void SiteBossSwordWhirlSlashChargeBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossSwordWhirlSlashChargeBase::loadParams_() {
    getStaticParam(&mChargeTime_s, "ChargeTime");
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SiteBossSwordWhirlSlashChargeBase::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    const sead::Vector3f up = getUpDir(controller->get70());
    sub_710073FA94(&_50, mActor);
    sead::Vector3f to_target = *mTargetPos_d;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    to_target -= pos;
    const f32 dist = to_target.normalize();
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    sub_710074006C(&_50, to_target, up, true, 0.16f, sead::Mathf::pi2(), 0.0f);

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    _44 *= 0.9f;
    const f32 max_speed = dist * 0.7f;
    _44.setToMin(max_speed);
    _44.updateStats();
    sub_710073770C(controller, _44.value, front);
    sub_7100740E04(_50, controller);
    _38.update();
    if (_38.value <= sead::Mathf::epsilon())
        setFinished();
}

void SiteBossSwordWhirlSlashChargeBase::m32() {}

}  // namespace uking::action
