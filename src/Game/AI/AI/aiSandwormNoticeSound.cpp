#include "Game/AI/AI/aiSandwormNoticeSound.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SandwormNoticeSound::SandwormNoticeSound(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormNoticeSound::~SandwormNoticeSound() = default;

bool SandwormNoticeSound::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormNoticeSound::enter_(ksys::act::ai::InlineParamPack* params) {
    _70.set(*mTargetPos_d);
    mActor->m93(2, 0.0f);
    _60 = ksys::Timer(-1.0f, -1.0f, 0.0f);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("振り向き", &pack);
}

void SandwormNoticeSound::leave_() {
    _98.reset();
    mActor->m93(0, 0.0f);
    if (auto* unk = sub_71005D9D68(mActor))
        unk->sub_71002DCBDC(4);
}

void SandwormNoticeSound::loadParams_() {
    getStaticParam(&mRetryDist_s, "RetryDist");
    getStaticParam(&mTargetActorLockOnDist_s, "TargetActorLockOnDist");
    getStaticParam(&mTargetPosLockOnDist_s, "TargetPosLockOnDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

// 0x710055c464
void SandwormNoticeSound::sub_710055C464() {
    _6c = false;
    _6d = false;
    sub_710055C800();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("移動", &pack);
}

// 0x710055c714
void SandwormNoticeSound::sub_710055C714() {
    mActor->m93(0, 0.0f);
    _98.reset();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("見失い", &pack);
}

// NON_MATCHING: operand load order of the XZ distance test (the original loads both target components first)
// 0x710055c800
void SandwormNoticeSound::sub_710055C800() {
    if (!isCurrentChild("移動") || _6d)
        return;
    const auto& mtx = mActor->getMtx();
    const f32 dx = mtx.m[0][3] - mTargetPos_d->x;
    const f32 dz = mtx.m[2][3] - mTargetPos_d->z;
    if (!(dx * dx + dz * dz <= *mTargetActorLockOnDist_s * *mTargetActorLockOnDist_s))
        return;
    mActor->m93(4, 0.0f);
    _60 = ksys::Timer(15.0f, 15.0f);
    _6c = false;
    _6d = true;
    _7c = *mTargetPos_d;
    _98 = *mTargetActor_d;
}

}  // namespace uking::ai
