#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
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

// Native two-element angle table: attempts 0..49 use pi/2, then attempts 50..99 use pi.
static const f32 sUnk_7101e78ecc[] = {3.1415927410125732f, 1.5707963705062866f};

// 0x71004d7dd8
// NON_MATCHING: native navigation/no-navigation loop specialization and matrix scheduling differ.
void NPCRoam::sub_71004D7DD8() {
    auto* nav = mActor->m45();
    const sead::Vector3f origin = mActor->getMtx().getTranslation();
    bool found = false;
    for (s32 i = 0; i < 100; ++i) {
        const f32 distance = sead::GlobalRandom::instance()->getF32Range(*mWalkDistMin_s, *mWalkDistMax_s);
        const sead::Vector3f forward = mActor->getMtx().getBase(2) * distance;
        const f32 angle_range = sUnk_7101e78ecc[i < 50];
        const f32 yaw = sead::GlobalRandom::instance()->getF32Range(-angle_range, angle_range);
        sead::Matrix33f rotation;
        rotation.makeR(sead::Vector3f(0.0f, yaw, 0.0f));
        const sead::Vector3f candidate = origin + rotation * forward;
        // Native also evaluates this length when there is no navigation character.
        const f32 from_basis = (candidate - *mBasisPos_d).length();
        if (nav && from_basis < *mRadius_s) {
            ksys::phys::HavokAI::Unk2 query;
            const f32 nan = std::numeric_limits<f32>::quiet_NaN();
            query.from.set(nan, nan, nan);
            query._10 = candidate;
            query._30 = 0xff;
            auto* havok = nav->_18 ? nav->_18 : ksys::phys::HavokAI::instance();
            if (havok->sub_7100F86324(nav, query, nullptr)) {
                _78 = candidate;
                found = true;
                break;
            }
        }
    }
    if (!found)
        _78 = *mBasisPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_78, "TargetPos", -1);
    pack.addString(_88, "DynASKeyName", -1);
    changeChild("移動", &pack);
}

}  // namespace uking::ai
