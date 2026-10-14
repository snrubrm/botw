#include "Game/Actor/AI/aiLastBossBeamAttackRoot.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/System/VFR.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actBeamBase.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::ai {

LastBossBeamAttackRoot::LastBossBeamAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// NON_MATCHING: the original builds the name arguments before computing `enemy + 0x1128` (scheduling)
LastBossBeamAttackRoot::~LastBossBeamAttackRoot() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->getActorPartsActor("Beam").hasProcInCalcState()) {
            ksys::act::ActorLinkConstDataAccess accessor;
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

inline void LastBossBeamAttackRoot::changeToAim(const sead::Vector3f& target_pos) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    changeChild("照準", &pack);
}

void LastBossBeamAttackRoot::changeToFire(const sead::Vector3f& target_pos) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        pack.addActor(enemy->getActorPartsActor("Beam"), "IgniteActor", -1);
    changeChild("発射", &pack);
}

void LastBossBeamAttackRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    {
        sead::Vector3f target_pos;
        sub_7100475B28(&target_pos);
        changeToAim(target_pos);
    }

    _c0.reset(*mWaitTime_s);
    _cc.value = *mInitSpeed_s;
    _cc.prev_value = *mInitSpeed_s;
    mActor->getMtx().getTranslation(_dc);
    _e8 = 0;
    _ec = 0;
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

bool LastBossBeamAttackRoot::isFinished() const {
    if (getCurrentChild() && isCurrentChild("発射") && getCurrentChild()->isFinishedOrFailed())
        return true;
    return false;
}

bool LastBossBeamAttackRoot::isChangeable() const {
    return *mIsChangeable_s;
}

// Discarded call: `getNumberOfDeadBlights();` before the count is chosen (present in the target asm).
void LastBossBeamAttackRoot::sub_710047555C() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;
    if (sub_71005D6D10())
        return;

    ksys::act::InstParamPack pack;
    getNumberOfDeadBlights();
    s32 count;
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (boss && (boss->_1534 & ~3) == 4)
        count = 3;
    else if (boss && (boss->_1534 & ~3) == 8)
        count = 4;
    else
        count = getNumberOfClearedRemains();
    const s32 add_power = *mAddAttackPower_s * count;
    pack->add(s32(*mAttackPower_s + add_power), "AttackPower");
    pack->add(s32(*mAtMinDamage_s), "AtMinDamage");
    pack->add(s32(*mAttackPowerForPlayer_s + add_power), "AttackPowerForPlayer");
    pack->add(*mReflectOffset_s, "PosOffset");
    auto* beam = ksys::act::ActorCreator::instance()->createActor(
        "CurseGanonBeam", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &pack, true,
        false);
    if (!beam)
        return;

    enemy->sub_7100D3D108("Beam", beam);
    _168.acquire(beam, false);
    if (auto* beam_actor = sead::DynamicCast<act::BeamBase>(beam))
        beam_actor->sub_7100003804(mActor, "Eyeball");
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

// NON_MATCHING: the original shares the speed reset of the first and third branches and keeps the position in
// integer registers (scheduling / register allocation).
void LastBossBeamAttackRoot::sub_710047635C(sead::Vector3f* out, const sead::Vector3f& target) {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const sead::Vector3f moved = pos - _dc;
    _fc.update();
    const f32 moved_dist = moved.length();
    if (moved_dist == 0.0f) {
        _e8 = f32(s32(sead::GlobalRandom::instance()->getU32() & 2) - 1);
        _cc.value = *mInitSpeed_s;
        _cc.prev_value = *mInitSpeed_s;
    } else if (moved_dist >= *mInitSpeed_s * 0.5f) {
        _cc *= _fc.value <= sead::Mathf::epsilon() ? 0.9f : *mAccel_s;
        _cc.setToMin(*mMoveSpeed_s);
    } else {
        // Blocked: turn around (or pick a side) and start over at the initial speed.
        if (_e8 == 0.0f)
            _e8 = f32(s32(sead::GlobalRandom::instance()->getU32() & 2) - 1);
        else
            _e8 = -_e8;
        _cc.value = *mInitSpeed_s;
        _cc.prev_value = *mInitSpeed_s;
    }
    _cc.updateStats();

    sead::Vector3f dir(target.x - pos.x, 0.0f, target.z - pos.z);
    dir.normalize();
    sead::Matrix34f rot;
    rot.makeR({0.0f, _e8 * sead::Mathf::piHalf(), 0.0f});
    const f32 y_speed = *mMoveYSpeed_s;
    const f32 speed = _cc.mean;
    const f32 delta = ksys::VFR::instance()->getDeltaFrame();
    _dc = pos;
    sead::Vector3f side;
    side.setRotated(rot, dir);
    sead::Vector3f next = pos + side * speed;
    next.y = pos.y + y_speed * delta * speed;
    sead::Vector3f away = next - target;
    away.normalize();

    _f0.update();
    f32 extra;
    if (_f0.value <= sead::Mathf::epsilon()) {
        extra = *mKeepDistanceRand_s * sead::GlobalRandom::instance()->getF32();
        _ec = extra;
        _f0 = ksys::Timer(*mRandKeepFrame_s, *mRandKeepFrame_s);
    } else {
        extra = _ec;
    }
    const f32 keep = *mKeepDistance_s + extra;
    sead::Vector3f move = target + away * keep - pos;
    f32 length = move.normalize();
    if (_cc.mean <= length)
        length = _cc.mean;
    *out = pos + move * length;
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
