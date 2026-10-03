#include "Game/AI/AI/aiPriestBossEyeBeam.h"
#include "Game/Actor/actBeamBase.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

PriestBossEyeBeam::PriestBossEyeBeam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossEyeBeam::~PriestBossEyeBeam() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->getActorPartsActor(_98).hasProcInCalcState()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&enemy->getActorPartsActor(_98), &accessor);
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        }
        enemy->sub_7100D3CFEC(_98);
    }
}

bool PriestBossEyeBeam::init_(sead::Heap* heap) {
    _98 = m46();
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (!enemy->_1128.getActorPartsActor(_98).hasProc())
            enemy->_1128.sub_7100D3CED8(_98, heap);
    }
    sub_710051459C();
    return true;
}

void PriestBossEyeBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71005D8DE8(mActor, ksys::act::PlayerInfo::getSomeProcLink(), nullptr, nullptr);
    _ac.set(sead::Vector3f::zero);
    m34();
    if (*mParams.mIsChangeable_s)
        mFlags.set(Flag::Changeable);
    else
        mFlags.reset(Flag::Changeable);
    sub_71005D74E8(mActor);
    sub_71005DB3EC(mActor);
    if (mActor->getAttention() && mActor->getAttention()->getClientByName("LockOn"))
        mActor->getAttention()->getClientByName("LockOn")->sub_7100D724FC(1);
}

void PriestBossEyeBeam::calc_() {
    if (m35())
        return;

    sead::Vector3f pos;
    m36(&pos);
    if (!mActor->getCharacterController()) {
        setFailed();
        return;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("照準")) {
            m43();
        } else if (isCurrentChild("チャージ")) {
            m44(pos);
        } else if (isCurrentChild("発射")) {
            m38(pos);
            m45();
        } else if (isCurrentChild("待機")) {
            m41();
            setFinished();
        }
    } else {
        const bool is_aiming = isCurrentChild("照準");
        child = getCurrentChild();
        if (is_aiming) {
            child->setDynamicParam(pos, "AimTargetPos");
            getCurrentChild()->setDynamicParam(getPlayerPosition(), "TargetPos");
        } else {
            child->setDynamicParam(pos, "TargetPos");
        }
    }
}

void PriestBossEyeBeam::leave_() {
    sead::Vector3f pos;
    m36(&pos);
    m38(pos);
    if (mActor->getAttention() && mActor->getAttention()->getClientByName("LockOn"))
        mActor->getAttention()->getClientByName("LockOn")->sub_7100D7250C(1);
    if (_88.hasProc() && ksys::act::isDemoNPCProfile(mActor)) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_88, &accessor);
        if (accessor.hasProc())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

void PriestBossEyeBeam::loadParams_() {
    getStaticParam(&mParams.mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mParams.mAttackPower_s, "AttackPower");
    getStaticParam(&mParams.mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    getStaticParam(&mParams.mShotReviseAngleXU_s, "ShotReviseAngleXU");
    getStaticParam(&mParams.mShotReviseAngleXD_s, "ShotReviseAngleXD");
    getStaticParam(&mParams.mShotReviseAngleY_s, "ShotReviseAngleY");
    getStaticParam(&mParams.mIsCreateGuardEffect_s, "IsCreateGuardEffect");
    getStaticParam(&mParams.mIsChangeable_s, "IsChangeable");
    getStaticParam(&mParams.mReflectOffset_s, "ReflectOffset");
    getStaticParam(&mParams.mShotOffset_s, "ShotOffset");
}

void PriestBossEyeBeam::m34() {
    sead::Vector3f pos;
    m36(&pos);
    m42(pos);
}

bool PriestBossEyeBeam::m35() {
    if (_a8) {
        _a8 = false;
        return true;
    }
    return false;
}

// NON_MATCHING: regalloc (the original rematerialises the accessor address instead of keeping it in x19)
void PriestBossEyeBeam::m41() {
    if (!_88.hasProc())
        return;

    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&_88, &accessor))
        mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000039), nullptr, true);
}

void PriestBossEyeBeam::m38(const sead::Vector3f& pos) {
    sub_71005DB068(mActor, pos);
}

void PriestBossEyeBeam::sub_710051459C() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy || sub_71005D6D10())
        return;

    if (enemy->getActorPartsActor(_98).hasProc())
        return;

    ksys::act::InstParamPack pack;
    pack->add(*mParams.mAttackPower_s, "AttackPower");
    pack->add(*mParams.mAtMinDamage_s, "AtMinDamage");
    pack->add(*mParams.mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    pack->add(*mParams.mReflectOffset_s, "PosOffset");
    auto* beam = ksys::act::ActorCreator::instance()->createActor(
        "Priest_Boss_Beam", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &pack, true,
        false);
    if (!beam)
        return;

    enemy->sub_7100D3D108(_98, beam);
    _88.acquire(beam, false);
    if (auto* beam_actor = sead::DynamicCast<act::BeamBase>(beam))
        beam_actor->sub_710000395C(mActor, "Head", mParams.mShotOffset_s);
}

bool PriestBossEyeBeam::m39(const sead::Vector3f& start, const sead::Vector3f& end) {
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityNPC);
    query.setStartAndEnd(start, end);
    query.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::_0);
    if (auto* body = mActor->findPhysicsBodyByName("Body", "Hat"))
        return query.shapeRayCast(body);
    return query.worldRayCast(ksys::phys::ContactLayerType::Entity);
}

void PriestBossEyeBeam::m42(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "AimTargetPos", -1);
    pack.addVec3(getPlayerPosition(), "TargetPos", -1);
    changeChild("照準", &pack);
}

void PriestBossEyeBeam::m44(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        pack.addActor(enemy->getActorPartsActor(_98), "IgniteActor", -1);
    changeChild("発射", &pack);
}

}  // namespace uking::ai
