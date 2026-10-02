#include "Game/AI/AI/aiPriestBossEyeBeam.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

// NON_MATCHING: this+0x88 is kept in x20 across the memset instead of being recomputed
PriestBossEyeBeam::PriestBossEyeBeam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossEyeBeam::~PriestBossEyeBeam() = default;

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
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossEyeBeam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossEyeBeam::loadParams_() {
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    getStaticParam(&mShotReviseAngleXU_s, "ShotReviseAngleXU");
    getStaticParam(&mShotReviseAngleXD_s, "ShotReviseAngleXD");
    getStaticParam(&mShotReviseAngleY_s, "ShotReviseAngleY");
    getStaticParam(&mIsCreateGuardEffect_s, "IsCreateGuardEffect");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mReflectOffset_s, "ReflectOffset");
    getStaticParam(&mShotOffset_s, "ShotOffset");
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

// NON_MATCHING: stack slot of the MessageType temporary (same issue as AirOctaFlyUp / OctarockEscape)
void PriestBossEyeBeam::m41() {
    if (!_88.hasProc())
        return;

    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&_88, &accessor))
        mActor->sendMessage(*accessor.getMessageTransceiverId(), 0x8000039, nullptr, true);
}

void PriestBossEyeBeam::m38(const sead::Vector3f& pos) {
    sub_71005DB068(mActor, pos);
}

}  // namespace uking::ai
