#include "Game/AI/Action/actionSiteBossLswordAtk.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

SiteBossLswordAtk::SiteBossLswordAtk(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossLswordAtk::~SiteBossLswordAtk() = default;

bool SiteBossLswordAtk::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossLswordAtk::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossLswordAtk::leave_() {
    sub_71005D79AC(mActor, 0, act::Unk_71002edaec(1));
    if (auto* chemical = mActor->sub_71011D8A44(1))
        chemical->sub_7100D91098(false);
    sub_71005D74E8(mActor);
}

void SiteBossLswordAtk::loadParams_() {
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mNearMoveSpeed_s, "NearMoveSpeed");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mFarMoveSpeed_s, "FarMoveSpeed");
    getStaticParam(&mIsIgnoreCancelAttack_s, "IsIgnoreCancelAttack");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SiteBossLswordAtk::calc_() {
    ksys::act::ai::Action::calc_();
}

bool SiteBossLswordAtk::isChangeable() const {
    return true;
}

bool SiteBossLswordAtk::isFinished() const {
    return isFinishedAS(0, 0);
}

void SiteBossLswordAtk::m32(f32 ratio) {
    if (auto* controller = mActor->getCharacterController())
        sub_7100737C0C(controller, ratio, controller->get70());
}

int SiteBossLswordAtk::m34() {
    return 0x100;
}

int SiteBossLswordAtk::m35() {
    int level = getNumberOfDeadBlights();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        const s32 kind = boss->_1534 & ~3;
        if (kind == 4)
            level = 3;
        else if (kind == 8)
            level = 4;
    }
    return *mAttackPower_s + *mAddAttackPower_s * level;
}

int SiteBossLswordAtk::m36() {
    return *mAtMinDamage_s;
}

}  // namespace uking::action
