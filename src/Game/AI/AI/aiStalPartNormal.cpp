#include "Game/AI/AI/aiStalPartNormal.h"
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

}  // namespace uking::ai
