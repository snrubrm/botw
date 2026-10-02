#include "Game/AI/AI/aiNPCChasePlayerBlueFire.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

NPCChasePlayerBlueFire::NPCChasePlayerBlueFire(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCChasePlayerBlueFire::~NPCChasePlayerBlueFire() = default;

bool NPCChasePlayerBlueFire::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCChasePlayerBlueFire::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "IsPathRest", -1);
    changeChild("Wander", &pack);
}

void NPCChasePlayerBlueFire::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCChasePlayerBlueFire::loadParams_() {
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mLeaveDist_s, "LeaveDist");
    getStaticParam(&mLostDist_s, "LostDist");
}

// NON_MATCHING: the original builds the translation copy in a vector register (ld1 lane + 8/4-byte
// stores) and keeps &pack in a different register
void NPCChasePlayerBlueFire::sub_71004C34AC() {
    sead::Vector3f pos;
    {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        const auto& mtx = player.hasProc() ? player.getActorMtx() : mActor->getMtx();
        pos = mtx.getTranslation();
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("追跡", &pack);
}

// NON_MATCHING: the original builds the translation copy in a vector register (ld1 lane + 8/4-byte
// stores) and keeps &pack in a different register
void NPCChasePlayerBlueFire::sub_71004C35CC() {
    sead::Vector3f pos;
    {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        const auto& mtx = player.hasProc() ? player.getActorMtx() : mActor->getMtx();
        pos = mtx.getTranslation();
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addBool(false, "TerrorOccurring", -1);
    changeChild("接近待機", &pack);
}

// NON_MATCHING: the original builds the translation copy in a vector register (ld1 lane + 8/4-byte
// stores) and keeps &pack in a different register
void NPCChasePlayerBlueFire::sub_71004C370C() {
    sead::Vector3f pos;
    {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        const auto& mtx = player.hasProc() ? player.getActorMtx() : mActor->getMtx();
        pos = mtx.getTranslation();
    }
    const f32 time = *mLostTimer_s;
    _58.mTimer = ksys::Timer(time, time);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addBool(false, "TerrorOccurring", -1);
    changeChild("見失い", &pack);
}

}  // namespace uking::ai
