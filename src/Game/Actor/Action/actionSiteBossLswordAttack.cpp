#include "Game/Actor/Action/actionSiteBossLswordAttack.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

SiteBossLswordAttack::SiteBossLswordAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossLswordAttack::~SiteBossLswordAttack() = default;

bool SiteBossLswordAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossLswordAttack::enter_(ksys::act::ai::InlineParamPack* params) {
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

void SiteBossLswordAttack::leave_() {
    sub_71005D79AC(mActor, 0, act::Unk_71002edaec(1));
    if (auto* chemical = mActor->sub_71011D8A44(1))
        chemical->sub_7100D91098(false);
    sub_71005D74E8(mActor);
}

void SiteBossLswordAttack::loadParams_() {
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

// NON_MATCHING: stack frame layout only (the original also saves x28 and places the up vector lower).
void SiteBossLswordAttack::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    const sead::Vector3f up = sead::Vector3f::ey;
    sub_710073FA94(&_bc, mActor);
    sead::Vector3f dir = *mTargetPos_d;
    sub_71005D7444(mActor, dir, true, true);
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    dir -= pos;
    sead::Vector3f velocity = sead::Vector3f::zero;
    m33(&velocity);
    if (sub_71005DD798(mActor, 0x29, nullptr, 0, 0)) {
        _b0.lerp(*mRotSpd_s, 0.08f, 0.01f, 0.001f);
        _b0.updateStats();
        sub_710074006C(&_bc, dir, up, true, *mBaseRotRatio_s, _b0.value, _b0.value / 10.0f);
        pos += velocity;
    }
    controller->sub_7100F5F938(sead::Matrix34f(_bc, pos));

    sub_71005DAB2C(mActor, *mJustAvoidSideDist_s + 7.0f, *mJustAvoidBackDist_s + 7.0f,
                   *mJustAvoidAngle_s, 0);

    ksys::as::ASList::Unk4 query;
    if (sub_71005DD66C(mActor, &query, 0, 0) || sub_71005DD780(mActor, 0x51, &query, 0, 0)) {
        _e0 = true;
        {
            auto* actor = mActor;
            const u32 attack_flags = m34();
            const f32 power = f32(m35());
            sub_71005D7ADC(actor, 0, attack_flags, &query.name, nullptr, m36(), 1, 0, 1, power,
                           1.0f);
        }
        if (auto* chemical = mActor->sub_71011D8A44(1))
            chemical->sub_7100D91098(true);
        auto* actor = mActor;
        const u32 attack_flags = m34();
        const f32 power = f32(m35());
        sub_71005D7ADC(actor, 0, attack_flags, &query.name, nullptr, m36(), 1, 0, 1, power, 1.0f);
    } else if (sub_71005DD74C(mActor, nullptr, 0, 0)) {
        sub_71005D79AC(mActor, 0, act::Unk_71002edaec(1));
        if (auto* chemical = mActor->sub_71011D8A44(1))
            chemical->sub_7100D91098(false);
        if (_e0)
            mFlags.set(Flag::Changeable);
    }

    if (isFinishedAS(0, 0))
        setFinished();
}

bool SiteBossLswordAttack::isChangeable() const {
    return true;
}

bool SiteBossLswordAttack::isFinished() const {
    return isFinishedAS(0, 0);
}

void SiteBossLswordAttack::m32(f32 ratio) {
    if (auto* controller = mActor->getCharacterController())
        sub_7100737C0C(controller, ratio, controller->get70());
}

int SiteBossLswordAttack::m34() {
    return 0x100;
}

int SiteBossLswordAttack::m35() {
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

int SiteBossLswordAttack::m36() {
    return *mAtMinDamage_s;
}

}  // namespace uking::action
