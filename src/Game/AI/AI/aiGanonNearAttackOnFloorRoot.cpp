#include "Game/AI/AI/aiGanonNearAttackOnFloorRoot.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

GanonNearAttackOnFloorRoot::GanonNearAttackOnFloorRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GanonNearAttackOnFloorRoot::~GanonNearAttackOnFloorRoot() = default;

bool GanonNearAttackOnFloorRoot::isFinished() const {
    auto* child = getCurrentChild();
    if (child && child->isFinished())
        return true;
    return false;
}

bool GanonNearAttackOnFloorRoot::isFailed() const {
    auto* child = getCurrentChild();
    if (child && child->isFailed())
        return true;
    return false;
}

bool GanonNearAttackOnFloorRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonNearAttackOnFloorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsPrevBeam_d)
        _58 = 4;
    sub_71003EC980();
}

void GanonNearAttackOnFloorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonNearAttackOnFloorRoot::loadParams_() {
    getStaticParam(&mNearDist_s, "NearDist");
    getDynamicParam(&mIsCounter_d, "IsCounter");
    getDynamicParam(&mIsPrevBeam_d, "IsPrevBeam");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GanonNearAttackOnFloorRoot::calc_() {
    auto* child = getCurrentChild();
    if (!child) {
        setFailed();
        return;
    }

    child->setDynamicParam(*mTargetPos_d, "TargetPos");
    if (isCurrentChild("衝撃波")) {
        if (auto* cc = mActor->getCharacterController())
            cc->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

void GanonNearAttackOnFloorRoot::changeToGreatswordAttack() {
    _58 = 1;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addBool(false, "IsMoveSide", -1);
    changeChild("大剣攻撃", &pack);
}

void GanonNearAttackOnFloorRoot::changeToGreatswordSideAttack() {
    _58 = 3;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addBool(false, "IsMoveSide", -1);
    changeChild("大剣横攻撃", &pack);
}

void GanonNearAttackOnFloorRoot::changeToSwordAttack() {
    _58 = 2;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addBool(false, "IsMoveSide", -1);
    changeChild("小剣攻撃", &pack);
}

}  // namespace uking::ai
