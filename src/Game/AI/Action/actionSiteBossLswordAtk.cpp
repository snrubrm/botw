#include "Game/AI/Action/actionSiteBossLswordAtk.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

SiteBossLswordAtk::SiteBossLswordAtk(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossLswordAtk::~SiteBossLswordAtk() = default;

bool SiteBossLswordAtk::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossLswordAtk::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mActor->getCharacterController())
        return;
    const sead::Vector3f up = sead::Vector3f::ey;
    _b0.value = 0;
    _b0.prev_value = 0;
    sub_710073FA90(&_bc, mActor);

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
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
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
