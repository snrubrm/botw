#include "Game/Actor/AI/aiPriestBossActorGiantRoot.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_710071edf8.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

// NON_MATCHING: the original keeps `_9c = 2` and `_a0 = 0` as two 32-bit stores (we merge them into one
// 64-bit store).
PriestBossActorGiantRoot::PriestBossActorGiantRoot(const InitArg& arg) : PriestBossActorRoot(arg) {}

PriestBossActorGiantRoot::~PriestBossActorGiantRoot() = default;

bool PriestBossActorGiantRoot::init_(sead::Heap* heap) {
    return PriestBossActorRoot::init_(heap);
}

void PriestBossActorGiantRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossActorRoot::enter_(params);
}

// NON_MATCHING: the original copies `_9c` through a stack slot (str / ldr) for the first test only
void PriestBossActorGiantRoot::calc_() {
    PriestBossActorRoot::calc_();
    if (isFinished() || isFailed())
        return;

    auto* child = getCurrentChild();
    if (!child) {
        setFailed();
        return;
    }

    const sead::Vector3f pos = sub_71005D9330(mActor);
    _dc.update();
    *mIsActive_a = _9c != State::_2;
    if (_9c != State::_7) {
        *mFacePos_a = pos;
        if (_9c == State::_8)
            child->setDynamicParam(pos, "TargetPos");
    }
    m47();
}

// NON_MATCHING: State wrapper temporaries and the shared transition tail differ.
void PriestBossActorGiantRoot::m47() {
    auto* child = getCurrentChild();
    if (m34()) {
        if (_9c != State::_9) {
            *mDestinationPos_a = mActor->getMtx().getTranslation();
            *mIsActive_a = true;
            *mIsArrivedAtDestination_a = true;
            *mKeepDistFromGround_a = -1.0f;
            child->setFinished();
            sub_71005089F4(State::_9);
        }
        return;
    }

    if (_9c == State::_9) {
        _a0 = m46();
        sub_71005089F4(_a0 == 7 ? State::_2 : State::_1);
    }
    if (!child->isFinished() && !child->isFailed())
        return;
    switch (_9c) {
    case State::_1:
        if (*mIsArrivedAtDestination_a)
            sub_71005089F4(State(_a0));
        break;
    case State::_2:
        *mDestinationPos_a = mActor->getMtx().getTranslation();
        sub_71005089F4(State(_a0));
        break;
    default:
        _a0 = m46();
        if (_a0 == 7) {
            sub_71005089F4(State::_2);
        } else {
            sub_71005089F4(State::_1);
            if (sead::GlobalRandom::instance()->getU32(5) != 0)
                sub_710071E3D8(mDestinationPos_a, mActor, *mFloatDistFromPlayer_s);
        }
        break;
    }
}

void PriestBossActorGiantRoot::leave_() {
    PriestBossActorRoot::leave_();
    *mIsActive_a = false;
}

void PriestBossActorGiantRoot::loadParams_() {
    PriestBossActorRoot::loadParams_();
    getStaticParam(&mFreqIronBallAttack_s, "FreqIronBallAttack");
    getStaticParam(&mFreqBigEarthReleaseAttack_s, "FreqBigEarthReleaseAttack");
    getStaticParam(&mFreqEyeBeamAttack_s, "FreqEyeBeamAttack");
    getStaticParam(&mFreqStageRotation_s, "FreqStageRotation");
    getStaticParam(&mFloatDistFromPlayer_s, "FloatDistFromPlayer");
    getStaticParam(&mIsFreeMoving_s, "IsFreeMoving");
    getAITreeVariable(&mKeepDistFromGround_a, "KeepDistFromGround");
    getAITreeVariable(&mIsActive_a, "IsActive");
    getAITreeVariable(&mIsArrivedAtDestination_a, "IsArrivedAtDestination");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
    getAITreeVariable(&mFacePos_a, "FacePos");
}

const char* PriestBossActorGiantRoot::m36() {
    return "第三段階";
}

// NON_MATCHING: the original's two uses of the by-value attack (the switch and the counter index) get
// separate stack slots, in the opposite order (two inline helpers with by-value parameters: the
// switch's slot above the index's); a single helper shares one slot
f32 PriestBossActorGiantRoot::getWeight(Attack attack) {
    f32 freq = 0.0f;
    switch (attack) {
    case Attack::_3:
        freq = *mFreqIronBallAttack_s;
        break;
    case Attack::_4:
        freq = *mFreqBigEarthReleaseAttack_s;
        break;
    case Attack::_5:
        freq = *mFreqEyeBeamAttack_s;
        break;
    case Attack::_7:
        freq = *mFreqStageRotation_s;
        break;
    default:
        break;
    }
    f32 weight = 0.0f;
    weight += freq * sead::GlobalRandom::instance()->getF32();
    weight += std::pow(0.9f, f32(_b0[attack]));
    return weight * 0.5f;
}

f32 PriestBossActorGiantRoot::m37() {
    return 0.0f;
}

f32 PriestBossActorGiantRoot::m38() {
    return 0.01f;
}

f32 PriestBossActorGiantRoot::m39() {
    return 0.0f;
}

f32 PriestBossActorGiantRoot::m40() {
    return getWeight(Attack::_3);
}

// NON_MATCHING: the by-value attack uses one stack slot instead of separate frequency/index slots.
f32 PriestBossActorGiantRoot::m41() {
    if (sub_7100505C74())
        return 0.0f;
    if (sub_71005D9330(mActor).y > mActor->getMtx().getTranslation().y)
        return 0.0f;
    if (!sub_7100508668())
        return 0.0f;
    return getWeight(Attack::_4);
}

f32 PriestBossActorGiantRoot::m42() {
    return getWeight(Attack::_5);
}

f32 PriestBossActorGiantRoot::m44() {
    if (_dc.value <= sead::Mathf::epsilon() && _98 != 4)
        return getWeight(Attack::_7);
    return 0.0f;
}

f32 PriestBossActorGiantRoot::m43() {
    return 0.0f;
}

f32 PriestBossActorGiantRoot::m45() {
    return 0.0f;
}

// NON_MATCHING: ObjList::front folds the node and object null checks into a conditional comparison;
// the original retains separate branches around the node-to-record conversion.
PriestBossActorGiantRoot::Attack PriestBossActorGiantRoot::m46() {
    Attack attack = Attack::_0;
    _a8->sub_710072B330();
    if (auto* record = _a8->mRecords.front())
        attack = Attack(record->mIndex);
    ++_b0[attack];
    return attack;
}

// NON_MATCHING: stack layout (the original keeps the query above the positions) and the ey * 9 scheduling
// 0x7100508668 (placeholder name): whether the navmesh below the actor (within 9 m) reaches the target position
bool PriestBossActorGiantRoot::sub_7100508668() {
    auto* havok = ksys::phys::HavokAI::instance();
    if (!havok)
        return false;
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f to = pos;
    to -= sead::Vector3f::ey * 9.0f;
    sead::Vector3f hit;
    const auto ground = havok->sub_7100F87A80(&hit, pos, to);
    if (!ground.sub_7100F7EB40())
        return false;
    auto* nav = mActor->m45();
    if (!nav)
        return false;
    ksys::phys::HavokAI::Unk2 query;
    query.from = hit;
    query._10 = sub_71005D9330(mActor);
    query._30 = 0xff;
    auto* havok_ai = nav->_18 ? nav->_18 : ksys::phys::HavokAI::instance();
    return havok_ai->sub_7100F86324(nav, query, nullptr);
}

}  // namespace uking::ai
