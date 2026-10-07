#include "Game/AI/AI/aiGanonNearAttackOnFloorRoot.h"
#include "Game/Actor/actLastBoss.h"
#include <random/seadGlobalRandom.h>
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

// NON_MATCHING: boss-state checks and attack weights are scheduled differently.
void GanonNearAttackOnFloorRoot::sub_71003EC980() {
    s32 choices;
    if (_58 == 5) {
        choices = 3;
    } else {
        const auto position = mActor->getMtx().getTranslation();
        const f32 dx = position.x - mTargetPos_d->x;
        const f32 dz = position.z - mTargetPos_d->z;
        if (dx * dx + dz * dz < *mNearDist_s * *mNearDist_s) {
            changeToShockwave();
            return;
        }
        choices = _58 == 0 ? 3 : 2;
    }
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor)) {
        if (boss->_14e8.isOn(2) && _58 != 4)
            ++choices;
    }
    const u32 roll = sead::GlobalRandom::instance()->getU32(choices * 10);
    const u32 greatsword_weight = _58 == 1 ? 0 : 10;
    const u32 sword_weight = _58 == 2 ? 0 : 10;
    const u32 side_weight = _58 == 3 ? 0 : 10;
    if (!*mIsCounter_d) {
        if (roll < greatsword_weight) {
            changeToGreatswordAttack();
            return;
        }
        if (roll < greatsword_weight + sword_weight) {
            changeToSwordAttack();
            return;
        }
        if (roll >= greatsword_weight + sword_weight + side_weight) {
            _58 = 4;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("ビーム攻撃", &pack);
            return;
        }
    } else if (_58 != 1 && (_58 == 3 || (roll & 1) == 0)) {
        changeToGreatswordAttack();
        return;
    }
    changeToGreatswordSideAttack();
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

void GanonNearAttackOnFloorRoot::changeToShockwave() {
    _58 = 5;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addBool(false, "IsMoveSide", -1);
    changeChild("衝撃波", &pack);
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor))
        boss->_14e8.setBit(13);
}

}  // namespace uking::ai
