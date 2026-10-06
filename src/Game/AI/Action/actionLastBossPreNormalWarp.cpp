#include "Game/AI/Action/actionLastBossPreNormalWarp.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"

// 0x71002c67e8 (declaration only).
void sub_71002C67E8(f32 a1, ksys::act::Actor* actor, bool a3);

namespace uking::action {

LastBossPreNormalWarp::LastBossPreNormalWarp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossPreNormalWarp::~LastBossPreNormalWarp() = default;

bool LastBossPreNormalWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossPreNormalWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LastBossPreNormalWarp::leave_() {
    ksys::act::ai::Action::leave_();
}

void LastBossPreNormalWarp::loadParams_() {
    getStaticParam(&mPreWarpWaitTime_s, "PreWarpWaitTime");
    getStaticParam(&mPosReduce_s, "PosReduce");
    getStaticParam(&mIsDeleteEffect_s, "IsDeleteEffect");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mIsPartsWarpEffectSync_d, "IsPartsWarpEffectSync");
}

void LastBossPreNormalWarp::calc_() {
    ksys::act::ai::Action::calc_();
}

void LastBossPreNormalWarp::m33() {
    if (auto* client = mActor->getAttention()->getClientByName("LockOn"))
        client->disable();
    if (auto* client = mActor->getAttention()->getClientByName("AutoAim"))
        client->disable();
}

void LastBossPreNormalWarp::m34(f32 a1, ksys::act::Actor* actor, bool a3) {
    sub_71002C67E8(a1, actor, a3);
}

}  // namespace uking::action
