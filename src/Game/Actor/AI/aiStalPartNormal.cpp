#include "Game/Actor/AI/aiStalPartNormal.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/aiUnk_7100724C64.h"
#include "KingSystem/ActorSystem/aiRootAi.h"

bool sub_710001AAA8(const ksys::act::ActorLinkConstDataAccess& accessor, const sead::SafeString& name);

namespace uking::ai {

StalPartNormal::StalPartNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalPartNormal::~StalPartNormal() = default;

bool StalPartNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalPartNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->getMainBody()) {
        _f4 = !body->hasFlag(ksys::phys::RigidBody::Flag::_2000000);
        body->clearFlag2000000(false);
    }
    _ec = 0;
    _e8 = 0;
    _f0 = 0;
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0))
        sub_71005A7750();
    else
        _58.reset();

    if (_58.hasProc()) {
        sub_7100738CB0(mActor, &_58);
        sub_71005A7854();
    } else if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0)) {
        sub_7100738DC8(mActor);
        _58.reset();
        changeChild("待機");
    } else {
        _58.reset();
        changeChild("行動禁止");
    }
    ksys::act::enableAttClient(mActor, "UsePick");
    ksys::act::enableAttClient(mActor, "NoticeDo");
    ksys::act::enableAttClient(mActor, "NameBalloon");
}

void StalPartNormal::sub_71005A7750() {
    if (!_58.hasProcInCalcState())
        return;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_58, &accessor);
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    const char* name = sub_71007251D0();
    if (!enemy)
        name = sub_71007251DC();
    if (sub_710001AAA8(accessor, name)) {
        sub_7100738DC8(mActor);
        _58.reset();
    }
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
    ksys::act::ActorLinkConstDataAccess accessor;
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
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_58, &accessor);
    pack.addVec3(accessor.getActorMtx() * *mParams.mTgtOffset_s, "TargetPos", -1);
    changeChild("移動", &pack);
}

// NON_MATCHING: register allocation of the Matrix34 * Vector3 product only (the ldp pairs of the matrix columns come out swapped)
// 0x71005a82f8
void StalPartNormal::sub_71005A82F8() {
    ksys::act::ai::InlineParamPack pack;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_58, &accessor);
    pack.addVec3(accessor.getActorMtx() * *mParams.mTgtOffset_s, "TargetPos", -1);
    changeChild("ジャンプ", &pack);
}

}  // namespace uking::ai
