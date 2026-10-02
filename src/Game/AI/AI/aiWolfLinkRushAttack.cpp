#include "Game/AI/AI/aiWolfLinkRushAttack.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actWolfLink.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

WolfLinkRushAttack::WolfLinkRushAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkRushAttack::~WolfLinkRushAttack() = default;

bool WolfLinkRushAttack::init_(sead::Heap* heap) {
    _58 = sead::DynamicCast<act::WolfLink>(mActor);
    return _58 != nullptr;
}

void WolfLinkRushAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    mActor->m45();
    if (!controller) {
        setFailed();
        return;
    }

    if (!sub_710060C1E4(true))
        setFailed();

    _60 = ksys::Timer(*mAllowUpdateTimerLength_s, *mAllowUpdateTimerLength_s);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_6c, "TargetPos", -1);
    changeChild("突進", &pack);
}

void WolfLinkRushAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkRushAttack::loadParams_() {
    getStaticParam(&mAttackPosOffsetLength_s, "AttackPosOffsetLength");
    getStaticParam(&mAllowUpdateTimerLength_s, "AllowUpdateTimerLength");
    getStaticParam(&mCheckSafeGround_s, "CheckSafeGround");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: instruction scheduling of the XZ differences (same operations)
bool WolfLinkRushAttack::sub_710060C1E4(bool x) {
    const auto& pos = mActor->getMtx().getTranslation();
    sead::Vector3f dir{mTargetPos_d->x - pos.x, 0.0f, mTargetPos_d->z - pos.z};
    dir.normalize();
    sead::Vector3f attack_pos;
    attack_pos.setScaleAdd(*mAttackPosOffsetLength_s, dir, *mTargetPos_d);

    sead::Vector3f safe_pos;
    if (sub_710072E154(mActor, attack_pos, &safe_pos, -1)) {
        _6c.set(attack_pos);
        return true;
    }

    const f32 safe_dx = pos.x - safe_pos.x;
    const f32 safe_dz = pos.z - safe_pos.z;
    const f32 target_dx = pos.x - mTargetPos_d->x;
    const f32 target_dz = pos.z - mTargetPos_d->z;
    if (safe_dx * safe_dx + safe_dz * safe_dz < target_dx * target_dx + target_dz * target_dz &&
        !x) {
        return false;
    }
    _6c.set(safe_pos);
    return true;
}

}  // namespace uking::ai
