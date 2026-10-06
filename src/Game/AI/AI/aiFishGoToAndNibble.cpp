#include "Game/AI/AI/aiFishGoToAndNibble.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

void FishGoToAndNibble::changeToFinalMove() {
    ksys::act::ActorConstDataAccess target;
    if (ksys::act::acquireActor(mTargetActor_d, &target)) {
        _70 = mActor->getMtx().getTranslation();
        sead::Vector3f position;
        target.getActorMtx().getTranslation(position);
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(position, "TargetPos", -1);
        changeChild("行進最後", &pack);
    } else {
        setFailed();
    }
}

void FishGoToAndNibble::changeToMove() {
    ksys::act::ActorConstDataAccess target;
    if (ksys::act::acquireActor(mTargetActor_d, &target)) {
        sead::Vector3f position;
        target.getActorMtx().getTranslation(position);
        position.y -= _88.getSizeY() * 0.5f * 0.5f + _a0.getSizeY() * 0.5f * 0.5f;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(position, "TargetPos", -1);
        changeChild("前進", &pack);
    } else {
        setFailed();
    }
}

FishGoToAndNibble::FishGoToAndNibble(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FishGoToAndNibble::~FishGoToAndNibble() = default;

// NON_MATCHING: scheduling of the min/max arithmetic (the original multiplies (scale * 0.5) first and stores the six
// results as stp pairs after computing them all)
bool FishGoToAndNibble::init_(sead::Heap* heap) {
    _c0 = mActor->findPhysicsBodyByName("Body", "FoodMover");
    if (_c0) {
        auto* actor = mActor;
        _a0 = actor->getAabb();
        const sead::Vector3f min = _a0.getMin();
        const sead::Vector3f max = _a0.getMax();
        const sead::Vector3f center((max.x + min.x) * 0.5f, (max.y + min.y) * 0.5f,
                                    (max.z + min.z) * 0.5f);
        const sead::Vector3f half(actor->getScale().x * 0.5f * (max.x - min.x),
                                  actor->getScale().y * 0.5f * (max.y - min.y),
                                  actor->getScale().z * 0.5f * (max.z - min.z));
        _a0.set(center - half, center + half);
    }
    return _c0 != nullptr;
}

// NON_MATCHING: instruction scheduling of the AABB copy / half-size arithmetic (the original keeps
// the min/max copy in integer registers and interleaves the _a0 loads; the math is the same)
void FishGoToAndNibble::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(mTargetActor_d, &accessor)) {
        _88 = accessor.sub_7100D0FD54();
        const f32 half_x = (_88.getMax().x - _88.getMin().x) * 0.5f;
        const f32 half_y = (_88.getMax().y - _88.getMin().y) * 0.5f;
        const f32 half_a0_z = (_a0.getMax().z - _a0.getMin().z) * 0.5f;
        const f32 half_z = (_88.getMax().z - _88.getMin().z) * 0.5f;
        _b8 = half_a0_z + sead::Mathf::max(sead::Mathf::max(half_x, half_y), half_z);

        sead::Vector3f target = *mTargetPos_d;
        const f32 half_a0_y = (_a0.getMax().y - _a0.getMin().y) * 0.5f;
        target.y -= half_y + half_a0_y;
        pack.addVec3(target, "TargetPos", -1);
        changeChild("移動", &pack);

        const s32 min_time = *mNumTimeNibbleMin_s;
        const s32 rand_time = *mNumTimeNibbleRand_s;
        _c8 = sead::GlobalRandom::instance()->getU32(rand_time) + min_time;
    } else {
        setFailed();
    }
}

void FishGoToAndNibble::leave_() {
    if (_c0->isAddedToWorld() || _c0->isAddingBodyToWorld())
        _c0->removeFromWorld();
}

void FishGoToAndNibble::loadParams_() {
    getStaticParam(&mNumTimeNibbleMin_s, "NumTimeNibbleMin");
    getStaticParam(&mNumTimeNibbleRand_s, "NumTimeNibbleRand");
    getStaticParam(&mDistStartNibble_s, "DistStartNibble");
    getStaticParam(&mDistBackward_s, "DistBackward");
    getStaticParam(&mDepthGiveUp_s, "DepthGiveUp");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
