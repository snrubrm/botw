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

}  // namespace uking::ai
