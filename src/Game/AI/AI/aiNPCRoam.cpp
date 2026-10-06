#include "Game/AI/AI/aiNPCRoam.h"
#include "random/seadGlobalRandom.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

NPCRoam::NPCRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
NPCRoam::~NPCRoam() {
    ;
}

bool NPCRoam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor))
        npc->_fe8 |= 0x200;
    _88.copy(mWaitASName_d);
    _88.append("Walk");
    if (!mActor->getASList()->sub_710115AA68(_88))
        _88.copy("Walk");
    sub_71004D7DD8();
}

void NPCRoam::leave_() {
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor))
        npc->_fe8 &= ~0x200;
}

void NPCRoam::loadParams_() {
    getStaticParam(&mWaitFrame_s, "WaitFrame");
    getStaticParam(&mWaitFrameRand_s, "WaitFrameRand");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mWalkDistMin_s, "WalkDistMin");
    getStaticParam(&mWalkDistMax_s, "WalkDistMax");
    getDynamicParam(&mWaitASName_d, "WaitASName");
    getDynamicParam(&mBasisPos_d, "BasisPos");
}

// NON_MATCHING: only the order of the sead::GlobalRandom singleton load differs (the original loads the two static
// params first)
// 0x71004d8644
void NPCRoam::sub_71004D8644() {
    const f32 wait_frame =
        sead::GlobalRandom::instance()->getS32Range(*mWaitFrame_s, *mWaitFrame_s + *mWaitFrameRand_s);
    ksys::act::ai::InlineParamPack pack;
    pack.addInt(wait_frame, "DynWaitFrame", -1);
    pack.addString(mWaitASName_d, "DynASName", -1);
    changeChild("待機", &pack);
}

}  // namespace uking::ai
