#include "Game/AI/AI/aiWillBallOperated.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

// inline-only in the original; name is a guess (the accessor shares its stack slot with the SafeString temporaries)
inline void WillBallOperated::getTargetActorPos(sead::Vector3f* pos) const {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mParams.mTargetActor_d, &accessor);
    accessor.getActorMtx().getTranslation(*pos);
}

WillBallOperated::WillBallOperated(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WillBallOperated::~WillBallOperated() = default;

bool WillBallOperated::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WillBallOperated::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WillBallOperated::leave_() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
}

void WillBallOperated::loadParams_() {
    getDynamicParam(&mParams.mWaitTime_d, "WaitTime");
    getDynamicParam(&mParams.mCommand_d, "Command");
    getDynamicParam(&mParams.mBasePos_d, "BasePos");
    getDynamicParam(&mParams.mTargetActor_d, "TargetActor");
    getStaticParam(&mParams.mWarpDist_s, "WarpDist");
    getStaticParam(&mParams.mAttakedChangeDist_s, "AttakedChangeDist");
    getStaticParam(&mParams.mIsAttackedTimeAffect_s, "IsAttackedTimeAffect");
}

bool WillBallOperated::handleMessage_(const ksys::Message* message) {
    if (_78._30 || !_78.m2(*message))
        return false;

    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    _70 = _78._38._44;
    return true;
}

// 0x71005f4638
void WillBallOperated::sub_71005F4638() {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_1000000);
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    getTargetActorPos(&pos);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("待機", &pack);
}

// 0x71005f4754
void WillBallOperated::sub_71005F4754() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    getTargetActorPos(&pos);
    pack.addVec3(pos, "TargetPos", -1);
    pack.addVec3(_78._38._38, "CenterPos", -1);
    changeChild("攻撃", &pack);
}

// 0x71005f4890
void WillBallOperated::sub_71005F4890() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    getTargetActorPos(&pos);
    pack.addVec3(pos, "TargetPos", -1);
    pack.addVec3(_78._38._2c, "Angle", -1);
    pack.addVec3(_78._38._38, "CenterPos", -1);
    changeChild("放物攻撃", &pack);
}

// 0x71005f49ec
void WillBallOperated::sub_71005F49EC() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    getTargetActorPos(&pos);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("落下攻撃", &pack);
}

// 0x71005f4b08
void WillBallOperated::sub_71005F4B08() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    getTargetActorPos(&pos);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("意識途切れ", &pack);
}

// 0x71005f4c24
void WillBallOperated::sub_71005F4C24() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    getTargetActorPos(&pos);
    pack.addVec3(pos, "TargetPos", -1);
    pack.addInt(_78._38._4c, "Level", -1);
    changeChild("予兆", &pack);
}

}  // namespace uking::ai
