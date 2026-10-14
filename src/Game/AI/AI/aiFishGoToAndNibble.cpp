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

// NON_MATCHING: stack slots of the accessors / vectors and the order of the depth test product.
void FishGoToAndNibble::calc_() {
    if (isFinished() || isFailed())
        return;
    auto* child = getCurrentChild();
    if (!child)
        return;
    if (!mTargetActor_d->hasProc()) {
        setFailed();
        return;
    }

    if (!mActor->get68f() || mActor->get6f0() + _a0.getSizeY() * -0.5f <= *mDepthGiveUp_s) {
        child->setFinished();
        changeToFinalMove();
        return;
    }

    if (child->isFinished() || child->isFailed()) {
        if (child->isFailed()) {
            setFailed();
            return;
        }
        if (isCurrentChild("移動")) {
            changeChild("待機");
            return;
        }
        if (isCurrentChild("待機")) {
            changeToMove();
            return;
        }
    }

    if (isCurrentChild("移動")) {
        ksys::act::ActorConstDataAccess target;
        if (!ksys::act::acquireActor(mTargetActor_d, &target)) {
            setFailed();
            return;
        }
        sead::Vector3f position;
        target.getActorMtx().getTranslation(position);
        position.y -= _88.getSizeY() * 0.5f + _a0.getSizeY() * 0.5f;
        if ((position - mActor->getMtx().getTranslation()).squaredLength() <=
            *mDistStartNibble_s * *mDistStartNibble_s)
            changeChild("待機");
        else
            child->setDynamicParam(position, "TargetPos");
    } else if (isCurrentChild("前進")) {
        ksys::act::ActorConstDataAccess target;
        if (!ksys::act::acquireActor(mTargetActor_d, &target)) {
            setFailed();
            return;
        }
        sead::Vector3f position;
        target.getActorMtx().getTranslation(position);
        child->setDynamicParam(position, "TargetPos");
        if ((position - mActor->getMtx().getTranslation()).squaredLength() <= _b8 * _b8) {
            ksys::act::ActorConstDataAccess food;
            if (!ksys::act::acquireActor(mTargetActor_d, &food)) {
                setFailed();
                return;
            }
            sead::Vector3f food_pos;
            food.getActorMtx().getTranslation(food_pos);
            food_pos.y -= _88.getSizeY() * 0.5f * 0.5f + _a0.getSizeY() * 0.5f * 0.5f;
            _c0->setPosition(food_pos);
            _c0->addToWorld();
            _7c.value = 5;
            _7c.previous_value = 5;
            if (_c8 < 2) {
                changeToFinalMove();
            } else {
                _70 = mActor->getMtx().getTranslation();
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(_70, "TargetPos", -1);
                changeChild("行進", &pack);
            }
        }
    } else if (isCurrentChild("行進") || isCurrentChild("行進最後")) {
        if (_c0->isAddedToWorld()) {
            _7c.update();
            if (_7c.value <= sead::Mathf::epsilon())
                _c0->removeFromWorld();
        }
        if ((_70 - mActor->getMtx().getTranslation()).squaredLength() <
            *mDistBackward_s * *mDistBackward_s)
            return;
        if (--_c8 < 1) {
            setFinished();
            return;
        }
        changeChild("待機");
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
