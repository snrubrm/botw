#include "Game/AI/Action/actionBattleCloseAction.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

// NON_MATCHING: store ordering/merging of the zero-initialised members (original merges 0x88-0x97 into one stp)
BattleCloseAction::BattleCloseAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BattleCloseAction::~BattleCloseAction() = default;

bool BattleCloseAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BattleCloseAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BattleCloseAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void BattleCloseAction::loadParams_() {
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mSpeed_s, "Speed");
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getStaticParam(&mParams.mFinRadius_s, "FinRadius");
    getStaticParam(&mParams.mFinRotate_s, "FinRotate");
    getStaticParam(&mParams.mBaseRotRatio_s, "BaseRotRatio");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void BattleCloseAction::calc_() {
    ksys::act::ai::Action::calc_();
}

ksys::act::Unk_7100d78e50* BattleCloseAction::m33(int idx) {
    return nullptr;
}

bool BattleCloseAction::m34(ksys::act::Unk_7100d78e50* entry) {
    return false;
}

f32 BattleCloseAction::m35() {
    return *mParams.mSpeed_s;
}

void BattleCloseAction::m36(const sead::Matrix34f& mtx) {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5FC8C(mtx);
}

bool BattleCloseAction::m37(ksys::phys::CharacterController* controller, f32 speed,
                            const sead::Vector3f& dir) {
    return true;
}

bool BattleCloseAction::m39() {
    auto* actor = mActor;
    if (!actor)
        return false;

    sead::Vector3f dir;
    actor->getMtx().getBase(dir, 2);
    dir.normalize();
    if (!isLandedMaybe(actor, false))
        return false;
    return dir.dot(sub_71007A471C(actor, 0)->_c) < 0.0f;
}

int BattleCloseAction::m38(f32 distance) {
    auto* actor = mActor;
    if (!actor)
        return 1;

    sead::Vector3f dir;
    dir = actor->getVelocity();
    dir.y = 0.0f;
    dir.normalize();
    sead::Vector3f front;
    actor->getMtx().getBase(front, 2);
    front.normalize();
    if (front.dot(dir) >= 0.9659258f) {
        bool flag = false;
        if (sub_710072FEC4(actor, dir, sead::Mathf::min(distance, 2.0f), nullptr, false, &flag))
            return 0;
        return flag ? 2 : 1;
    }
    return 1;
}

}  // namespace uking::action
