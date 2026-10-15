#include "Game/Actor/AI/aiNPCRoam.h"
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

// NON_MATCHING: animation parameter selection and descriptor register allocation.
void NPCRoam::calc_() {
    if (isFailed())
        return;
    if ((mActor->getMtx().getTranslation() - *mBasisPos_d).length() > *mRadius_s * 1.5f) {
        setFailed();
        return;
    }
    if (isCurrentChild("移動")) {
        if (getCurrentChild()->isFinished()) {
            const char* as_name = mActor->getASList()->x_1(0, 0).getStringTop();
            const bool continuing = mActor->getASList()->x(
                0x16, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true);
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(_78, "TargetPos", -1);
            pack.addString(continuing ? as_name : "Move_End", "DynASKeyName", -1);
            changeChild("減速", &pack);
        } else if (getCurrentChild()->isFailed()) {
            setFailed();
        }
    } else if (isCurrentChild("減速")) {
        if ((mActor->getASList()->x_1(0, 0) == "Move_End" && checkAS(0, 0)) ||
            mActor->getASList()->sub_710115F0BC(0, 0, 0.0f))
            sub_71004D8644();
    } else if (isCurrentChild("待機") && getCurrentChild()->isFinished()) {
        sub_71004D7DD8();
    }
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

// 0x71004d8644
void NPCRoam::sub_71004D8644() {
    const s32 base_frame = *mWaitFrame_s;
    const s32 random_frame = *mWaitFrameRand_s;
    const f32 wait_frame =
        sead::GlobalRandom::instance()->getS32Range(base_frame, base_frame + random_frame);
    ksys::act::ai::InlineParamPack pack;
    pack.addInt(wait_frame, "DynWaitFrame", -1);
    pack.addString(mWaitASName_d, "DynASName", -1);
    changeChild("待機", &pack);
}

}  // namespace uking::ai
