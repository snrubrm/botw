#include "Game/AI/AI/aiStalPartNormal.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

StalPartNormal::StalPartNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalPartNormal::~StalPartNormal() = default;

bool StalPartNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalPartNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StalPartNormal::leave_() {
    sub_7100738DC8(mActor);
    if (auto* body = mActor->getMainBody())
        body->clearFlag2000000(_f4);
    ksys::act::enableAttClient(mActor, "UsePick");
    ksys::act::enableAttClient(mActor, "NoticeDo");
    ksys::act::enableAttClient(mActor, "NameBalloon");
}

void StalPartNormal::loadParams_() {
    getStaticParam(&mParams.mTerritoryArea_s, "TerritoryArea");
    getStaticParam(&mParams.mCatchArea_s, "CatchArea");
    getStaticParam(&mParams.mWaitTimer_s, "WaitTimer");
    getStaticParam(&mParams.mTgtOffset_s, "TgtOffset");
}

bool StalPartNormal::handleMessage_(const ksys::Message* message) {
    if (_e8 <= sead::Mathf::epsilon() && !_68._30 && !isCurrentChild("行動禁止") &&
        _68.m2(*message)) {
        if (_58 == _68._38.mLink)
            _68.x();
        return true;
    }
    return false;
}

// NON_MATCHING: register allocation of the Matrix34 * Vector3 product only (the ldp pairs of the matrix columns come out swapped)
// 0x71005a7854
void StalPartNormal::sub_71005A7854() {
    ksys::act::ai::InlineParamPack pack;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_58, &accessor);
    pack.addVec3(accessor.getActorMtx() * *mParams.mTgtOffset_s, "TargetPos", -1);
    changeChild("気づき", &pack);
}

// NON_MATCHING: register allocation of the Matrix34 * Vector3 product only (the ldp pairs of the matrix columns come out swapped)
// 0x71005a815c
void StalPartNormal::sub_71005A815C() {
    if (isCurrentChild("待機")) {
        sub_71005A7854();
        return;
    }
    ksys::act::ai::InlineParamPack pack;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_58, &accessor);
    pack.addVec3(accessor.getActorMtx() * *mParams.mTgtOffset_s, "TargetPos", -1);
    changeChild("移動", &pack);
}

// NON_MATCHING: register allocation of the Matrix34 * Vector3 product only (the ldp pairs of the matrix columns come out swapped)
// 0x71005a82f8
void StalPartNormal::sub_71005A82F8() {
    ksys::act::ai::InlineParamPack pack;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_58, &accessor);
    pack.addVec3(accessor.getActorMtx() * *mParams.mTgtOffset_s, "TargetPos", -1);
    changeChild("ジャンプ", &pack);
}

}  // namespace uking::ai
