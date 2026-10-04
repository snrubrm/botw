#include "Game/AI/AI/aiLynelArrowBattle.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actWeapon.h"

namespace uking::ai {

LynelArrowBattle::LynelArrowBattle(const InitArg& arg) : EnemyBattle(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
LynelArrowBattle::~LynelArrowBattle() {
    ;
}

bool LynelArrowBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void LynelArrowBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    _b8 = *mAttackCount_s;
    EnemyBattle::enter_(params);
}

void LynelArrowBattle::calc_() {
    EnemyBattle::calc_();
}

void LynelArrowBattle::leave_() {
    sub_71005D787C(mActor, *mWeaponIdx_s, uking::act::Unk_71002eda38(5));
    EnemyBattle::leave_();
}

void LynelArrowBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mAttackCount_s, "AttackCount");
    getStaticParam(&mFrontCheckBoneName_s, "FrontCheckBoneName");
    getStaticParam(&mFrontDirFromBone_s, "FrontDirFromBone");
}

void LynelArrowBattle::m37() {
    EnemyBattle::m37();
}

bool LynelArrowBattle::m41() {
    return true;
}

void LynelArrowBattle::m38() {
    --_b8;
    EnemyBattle::m38();
}

// Whether the Lynel faces the target: the direction `mFrontDirFromBone_s` rotated by the world matrix of the bone
// `mFrontCheckBoneName_s` (the actor's front if there is no such bone), flattened onto the XZ plane, must be
// within `mAttackAngle_s` of the direction to the target.
bool LynelArrowBattle::m40() {
    sead::Vector3f front(0.0f, 0.0f, 0.0f);
    if (!mFrontCheckBoneName_s.isEmpty()) {
        auto* model = mActor->getModel();
        const auto key = model->searchBone(mFrontCheckBoneName_s);
        if (key.isValid()) {
            sead::Matrix34f mtx;
            model->getUnits()
                .unsafeAt(key.model_unit_index)
                ->mModelUnit->getBoneWorldMatrix(&mtx, key.bone_index);
            front = *mFrontDirFromBone_s;
            front.rotate(mtx);
            front.y = 0.0f;
            front.normalize();
        }
    }
    if (front.x == 0.0f && front.y == 0.0f && front.z == 0.0f)
        sub_71000891C8(&front, mActor);

    sead::Vector3f target;
    m36(&target);
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f dir(target.x - pos.x, 0.0f, target.z - pos.z);
    dir.normalize();
    const f32 angle = *mAttackAngle_s;
    return dir.dot(front) >= sead::Mathf::cos(angle);
}

bool LynelArrowBattle::isFinished() const {
    return ActionBase::isFinished() ||
           (getCurrentChild()->isFinished() && *mAttackCount_s > 0 && _b8 <= 0);
}

}  // namespace uking::ai
