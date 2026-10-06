#include "Game/AI/Action/actionGoronHeroDescendentJump.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::action {

GoronHeroDescendentJump::GoronHeroDescendentJump(const InitArg& arg) : MoveToTargetCurveBase(arg) {}

GoronHeroDescendentJump::~GoronHeroDescendentJump() = default;

bool GoronHeroDescendentJump::init_(sead::Heap* heap) {
    return MoveToTargetCurveBase::init_(heap);
}

void GoronHeroDescendentJump::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveToTargetCurveBase::enter_(params);
    playAS("Act_Ball_Jump", false, 0, 0, -1.0f);
}

void GoronHeroDescendentJump::leave_() {
    MoveToTargetCurveBase::leave_();
}

void GoronHeroDescendentJump::loadParams_() {
    MoveToTargetCurveBase::loadParams_();
    getDynamicParam(&mIsIntoCannon_d, "IsIntoCannon");
    getDynamicParam(&mJumpTargetPos_d, "JumpTargetPos");
}

void GoronHeroDescendentJump::calc_() {
    MoveToTargetCurveBase::calc_();
}

void GoronHeroDescendentJump::m32() {
    auto* actor = mActor;
    auto* cc = actor->getCharacterController();
    if (!cc)
        return;
    cc->sub_7100F605F0();
    cc->sub_7100F62BC0(false);
    cc->sub_7100F5EDD8(1.0f);
    if (*mIsIntoCannon_d)
        return;
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    cc->disableContactLayer(ksys::phys::ContactLayer::EntityGround);
}

// NON_MATCHING: the original moves the float argument (s0 -> v8) before the pos pointer (x1 -> x22) at the
// start; everything else is identical.
void GoronHeroDescendentJump::m33(f32 dist, sead::Vector3f* pos) {
    auto* actor = mActor;
    auto* cc = actor->getCharacterController();
    if (!cc)
        return;
    sead::Matrix34f mtx = actor->getMtx();
    mtx.setTranslation(*pos);
    cc->sub_7100F5F938(mtx);
    if (*mIsIntoCannon_d) {
        if (_60 > dist / _58) {
            actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
            cc->sub_7100F62BC0(true);
            setFinished();
        }
    } else if (_60 > dist / (_58 + _58)) {
        if (sub_710018E9A8(1.5f)) {
            cc->sub_7100F60604();
            setFinished();
        }
    }
}

void GoronHeroDescendentJump::m34(sead::Vector3f* target) {
    target->set(*mJumpTargetPos_d);
}

f32 GoronHeroDescendentJump::m35(const sead::Vector3f* from, const sead::Vector3f* to) {
    const f32 dy = to->y - from->y;
    const f32 height = *mMaxHeight_s;
    return height > dy ? height : dy + 5.0f;
}

bool GoronHeroDescendentJump::sub_710018E9A8(f32 dist) {
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityTree);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.setStartAndDisplacementScaled(mActor->getMtx().getTranslation(), -sead::Vector3f::ey,
                                        dist);
    return query.worldRayCast(ksys::phys::ContactLayerType::Entity);
}

}  // namespace uking::action
