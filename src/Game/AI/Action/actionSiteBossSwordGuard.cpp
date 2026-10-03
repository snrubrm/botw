#include "Game/AI/Action/actionSiteBossSwordGuard.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

SiteBossSwordGuard::SiteBossSwordGuard(const InitArg& arg) : Guard(arg) {}

SiteBossSwordGuard::~SiteBossSwordGuard() = default;

bool SiteBossSwordGuard::init_(sead::Heap* heap) {
    return Guard::init_(heap);
}

void SiteBossSwordGuard::enter_(ksys::act::ai::InlineParamPack* params) {
    Guard::enter_(params);
}

void SiteBossSwordGuard::leave_() {
    Guard::leave_();
}

void SiteBossSwordGuard::loadParams_() {
    Guard::loadParams_();
}

void SiteBossSwordGuard::calc_() {
    Guard::calc_();
    const sead::Vector3f front = _98;
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Matrix34f mtx;
    ksys::util::sub_71011F0260(&mtx, front, sead::Vector3f::ey, pos, false);
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5FC8C(mtx);
}

}  // namespace uking::action
