#include "Game/Actor/Action/actionSiteBossAvoid.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SiteBossAvoid::SiteBossAvoid(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossAvoid::~SiteBossAvoid() = default;

bool SiteBossAvoid::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original computes the x_6 angle before loading getASList() (C++14 evaluation order)
void SiteBossAvoid::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710073FA90(&_6c, mActor);
    _60.reset(*mAvoidEndTime_s);
    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5FB24(sead::Vector3f::zero);

    if (*mIsAvoidHorizon_d) {
        sead::Vector3f cross;
        cross.setCross(front, *mAvoidVec_d);
        mActor->getASList()->x_6(9, 0, cross.y < 0.0f ? 270.0f : 90.0f);
        playAS("Avoid", false, 0, 0, -1.0f);
    }

    mActor->getMtx().getTranslation(_90);
    _90 += *mAvoidVec_d * *mAvoidDist_d;
    _9c = (_90 - *mTargetPos_d).length();
    _a0 = 0.0f;
}

void SiteBossAvoid::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5F6FC(sead::Vector3f::zero);
}

void SiteBossAvoid::loadParams_() {
    getStaticParam(&mAvoidEndTime_s, "AvoidEndTime");
    getStaticParam(&mAvoidMoveSpeed_s, "AvoidMoveSpeed");
    getDynamicParam(&mAvoidDist_d, "AvoidDist");
    getDynamicParam(&mIsAvoidHorizon_d, "IsAvoidHorizon");
    getDynamicParam(&mIsSlerp_d, "IsSlerp");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mAvoidVec_d, "AvoidVec");
    getDynamicParam(&mPlayerPos_d, "PlayerPos");
}

void SiteBossAvoid::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    const sead::Vector3f up = sead::Vector3f::ey;
    sub_710073FA94(&_6c, mActor);
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    sead::Vector3f target = *mTargetPos_d;
    target -= position;
    ksys::util::sub_71011EFA00(&target, target, up);
    target.normalize();
    sub_710074006C(&_6c, target, up, true, 0.93f, 0.03f, 0.001f);
    ksys::VFR::lerp(&_a0, *mAvoidMoveSpeed_s, 0.1f);
    sead::Vector3f next = position + (_90 - position) * _a0;
    if (*mIsSlerp_d) {
        sead::Vector3f direction = next - *mPlayerPos_d;
        f32 distance = direction.normalize();
        ksys::VFR::lerp(&distance, _9c, 0.1f);
        next = *mPlayerPos_d + direction * distance;
    }
    const sead::Matrix34f transform(_6c, next);
    controller->sub_7100F5F938(transform);
    _60.update();
    if (_60.value <= sead::Mathf::epsilon())
        setFinished();
}

}  // namespace uking::action
