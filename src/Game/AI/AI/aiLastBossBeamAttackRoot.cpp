#include "Game/AI/AI/aiLastBossBeamAttackRoot.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

LastBossBeamAttackRoot::LastBossBeamAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// NON_MATCHING: the original builds the name arguments before computing `enemy + 0x1128` (scheduling)
LastBossBeamAttackRoot::~LastBossBeamAttackRoot() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->getActorPartsActor("Beam").hasProcInCalcState()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&enemy->getActorPartsActor("Beam"), &accessor);
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        }
        enemy->sub_7100D3CFEC("Beam");
    }
}

bool LastBossBeamAttackRoot::init_(sead::Heap* heap) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CED8("Beam", heap);
    sub_710047555C();
    return true;
}

// NON_MATCHING: stack slot order of the target position vs the "TargetPos" SafeString and the placement of the
// InlineParamPack's `count = 0` store relative to the sub_7100475B28 call; everything else matches
void LastBossBeamAttackRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    {
        ksys::act::ai::InlineParamPack pack;
        sead::Vector3f target_pos;
        sub_7100475B28(&target_pos);
        pack.addVec3(target_pos, "TargetPos", -1);
        changeChild("照準", &pack);
    }

    _c0.reset(*mWaitTime_s);
    _cc.value = *mInitSpeed_s;
    _cc.prev_value = *mInitSpeed_s;
    mActor->getMtx().getTranslation(_dc);
    _e8 = 0;
    _f0.reset(*mRandKeepFrame_s);
    _fc.reset(*mBrakeStartFrame_s);

    if (auto* model = mActor->getModel())
        _130.search(model, "Eyeball");
    else
        _130.getKey().reset();
    _d8 = true;
    if (*mIsChangeable_s)
        mFlags.set(Flag::Changeable);
    else
        mFlags.reset(Flag::Changeable);

    sub_71005D74E8(mActor);
    sub_71005DB3EC(mActor);
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (boss->_1558.isOnBit(4)) {
            switch (boss->_1534) {
            case 2:
            case 6:
            case 10:
                boss->sub_71002D20B8();
                boss->x_5(false);
                boss->x_6(false);
                ksys::eft::searchAndEmitELink(mActor, "Elec_Sword_Off");
                ksys::eft::searchAndEmitELink(mActor, "Elec_Shield_Off");
                ksys::eft::searchAndEmitSLink(mActor, "Elec_Sword_Off", false);
                break;
            default:
                break;
            }
        }
    }
}

// NON_MATCHING: branch layout (the original returns the constants 1 / 0 from separate blocks; ours
// ends with `and w0, w0, #1` on isFailed's result)
bool LastBossBeamAttackRoot::isFinished() const {
    if (getCurrentChild()) {
        if (isCurrentChild("発射")) {
            auto* child = getCurrentChild();
            if (child->isFinished() || child->isFailed())
                return true;
        }
    }
    return false;
}

bool LastBossBeamAttackRoot::isChangeable() const {
    return *mIsChangeable_s;
}

void LastBossBeamAttackRoot::sub_7100475B28(sead::Vector3f* out) {
    auto* actor = mActor;
    if (!actor)
        return;

    auto* target = sub_71005D9050(actor);
    const sead::Vector3f* pos;
    if (target && target->hasProc() && ksys::act::isPlayerProfile(target))
        pos = &sub_71005D9330(actor);
    else
        pos = &getPlayerPosition();
    *out = *pos;
    out->y += 1.0f;

    sead::Vector3f start;
    if (_130.isValid() && actor->getModel()) {
        sead::Matrix34f mtx;
        actor->getModel()
            ->getUnits()
            .unsafeAt(_130.getKey().model_unit_index)
            ->mModelUnit->getBoneWorldMatrix(&mtx, _130.getKey().bone_index);
        start.x = mtx.m[0][3];
        start.y = mtx.m[1][3];
        start.z = mtx.m[2][3];
    } else {
        start.x = actor->getMtx().m[0][3];
        start.y = actor->getMtx().m[1][3];
        start.z = actor->getMtx().m[2][3];
    }

    sead::Vector3f hit;
    if (sub_710072EB10(start, *out, ksys::phys::RayCast::NormalCheckingMode::_0, actor, &hit,
                       nullptr, nullptr, 0.0f))
        *out = hit;
}

void LastBossBeamAttackRoot::leave_() {
    sead::Vector3f pos;
    sub_7100475B28(&pos);
    if (auto* parts = sub_71005DB0EC(mActor)) {
        parts->sub_7100D89C64();
        parts->sub_7100D89CDC();
        parts->sub_7100D89D54();
        parts->sub_7100D89DC4();
        parts->sub_7100D89F60();
        parts->sub_7100D89FD8();
        parts->sub_7100D8A050();
        parts->sub_7100D8A0C0();
    }
    sub_71005DB068(mActor, pos);
    sub_71005D74E8(mActor);
}

void LastBossBeamAttackRoot::loadParams_() {
    getStaticParam(&mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mKeepDistance_s, "KeepDistance");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mAccel_s, "Accel");
    getStaticParam(&mKeepDistanceRand_s, "KeepDistanceRand");
    getStaticParam(&mRandKeepFrame_s, "RandKeepFrame");
    getStaticParam(&mBrakeStartFrame_s, "BrakeStartFrame");
    getStaticParam(&mMoveYSpeed_s, "MoveYSpeed");
    getStaticParam(&mIsMove_s, "IsMove");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mIsCreateGuardEffect_s, "IsCreateGuardEffect");
    getStaticParam(&mReflectOffset_s, "ReflectOffset");
}

}  // namespace uking::ai
