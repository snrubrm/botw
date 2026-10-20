#include "KingSystem/Event/evtActorBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtAction.h"
#include "KingSystem/Event/evtEventFlow.h"
#include "KingSystem/Event/evtQuery.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Physics/System/physShapeCastWithInfo.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include <gfx/seadColor.h>

namespace ksys::evt {

// 0x7100da9bb0 (CSV evt::ActorBase::m2), 0x7100da9be8 (m3)
ActorBase::~ActorBase() = default;

// 0x7100da9c2c
ActionBase* ActorBase::getActionByName(const evfl::ResAction* res) const {
    for (s32 i = 0; i < mActions.size(); ++i) {
        ActionBase* action = mActions.at(i);
        if (action->getRes() == res)
            return action;
    }
    return nullptr;
}

// 0x7100da9c90
// NON_MATCHING: induction/register details only (original keeps the at() null-select per iteration
// with a zero-extended size; ours proves it away and uses direct indexing). Tried s32/s64 indices.
Query* ActorBase::getQueryByRes(const evfl::ResQuery* res) const {
    for (s32 i = 0; i < mQueries.size(); ++i) {
        Query* query = mQueries.at(i);
        if (query->mRes == res)
            return query;
    }
    for (s32 i = 0; i < mQueries.size(); ++i) {
        Query* query = mQueries.at(i);
        if (query->mRes == res)
            return query;
    }
    return nullptr;
}

// 0x7100daaa10
bool ActorBase::m6() {
    if (mState == 0x15)
        mState = 0x16;
    return true;
}

void ActorBase::m8() {
    mFlags |= 1;
    sub_7100DAB470();
}

// 0x7100dab470
void ActorBase::sub_7100DAB470() {
    auto* actor = sead::DynamicCast<act::Actor>(mLink.getProc(nullptr));
    if (!actor)
        return;
    if (mFlags & 8) {
        actor->setMtx(mAppliedTransform, true, true);
        actor->nullsub_4648();
    }
    if (mActorSet->mResource->mDemoInfo.isWithTransAnimation())
        actor->_7d0 = &mTransform;
}

// 0x7100dab5f8
void ActorBase::play() {
    if (!(mFlags & 1))
        return;

    for (s32 i = 0; i < mActions.size(); ++i) {
        ActionBase* action = mActions.at(i);
        if (mState == 6) {
            m4();
        } else if (_1b4 && !mLink.hasProc()) {
            mState = 6;
        }
        action->play();
    }
}

// 0x7100dab86c
bool Actor::x_0() {
    for (s32 i = 0; i < mActions.size(); ++i) {
        if (!static_cast<Action*>(mActions.at(i))->x())
            return false;
    }
    return true;
}

// NON_MATCHING: the calls and layers match; clang rotates the ray loop and allocates the loop counter / result
// registers differently (1252 bytes against the original's 1352).
// 0x7100dab8e0
bool Actor::sub_7100DAB8E0(const sead::Vector3f& pos) {
    ksys::phys::SphereCast cast{ksys::phys::ContactLayer::EntityPlayer,
                                ksys::phys::GroundHit::HitAll,
                                nullptr,
                                0x80,
                                ksys::phys::ShapeCast::Mode::_0,
                                sead::Vector3f::zero,
                                0.35f,
                                sead::SafeString::cEmptyString,
                                ksys::phys::LowPriority::No};
    cast.setStartAndEnd(pos + sead::Vector3f(0.0f, 1.45f, 0.0f),
                        pos + sead::Vector3f(0.0f, 0.45f, 0.0f));
    auto* info = cast.getContactPointInfo();
    info->subscribeLayer(ksys::phys::ContactLayer::EntityGround);
    info->subscribeLayer(ksys::phys::ContactLayer::EntityGroundObject);
    info->subscribeLayer(ksys::phys::ContactLayer::EntityGroundRough);
    info->subscribeLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    info->subscribeLayer(ksys::phys::ContactLayer::EntityNPC);
    info->subscribeLayer(ksys::phys::ContactLayer::EntityWater);
    // called through a pointer in the original (not devirtualised)
    const bool hit = (&cast)->executeQuery(ksys::phys::ShapeCast::WeldClosestPoints::Yes);
    cast.setColors(sead::Color4f{1.0f, 0.0f, 0.0f, 0.25f},
                   sead::Color4f{0.0f, 1.0f, 0.0f, 0.25f},
                   sead::Color4f{1.0f, 1.0f, 0.0f, 0.8f}, true);

    bool result = true;
    if (!hit) {
        bool ok = false;
        for (s32 i = 1; i < 4; ++i) {
            ksys::phys::RayCastBodyQuery rc1(nullptr, ksys::phys::GroundHit::HitAll);
            ksys::phys::RayCastBodyQuery rc2(nullptr, ksys::phys::GroundHit::HitAll);
            rc1.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::DoNotCheck);
            rc2.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::_0);

            const f32 ox = ((i - 1) & 1) ? 30.0f : -30.0f;
            const f32 oz = (i > 2) ? -30.0f : 30.0f;
            const sead::Vector3f start = pos + sead::Vector3f(0.0f, 1.0f, 0.0f);
            const sead::Vector3f end = pos + sead::Vector3f(ox, 1.0f, oz);
            rc1.setStartAndEnd(start, end);
            rc2.setStartAndEnd(start, end);

            rc1.enableLayer(ksys::phys::ContactLayer::EntityGround);
            rc1.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
            rc1.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
            rc1.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
            rc1.enableLayer(ksys::phys::ContactLayer::EntityNPC);
            rc1.enableLayer(ksys::phys::ContactLayer::EntityWater);
            rc2.enableLayer(ksys::phys::ContactLayer::EntityGround);
            rc2.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
            rc2.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
            rc2.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
            rc2.enableLayer(ksys::phys::ContactLayer::EntityNPC);
            rc2.enableLayer(ksys::phys::ContactLayer::EntityWater);

            const bool hit1 = rc1.worldRayCast(ksys::phys::ContactLayerType::Entity);
            const bool hit2 = rc2.worldRayCast(ksys::phys::ContactLayerType::Entity);
            bool matched;
            if (hit1 && hit2) {
                sead::Vector3f p1;
                sead::Vector3f p2;
                rc1.getHitPosition(&p1);
                rc2.getHitPosition(&p2);
                const f32 dx = p1.x - p2.x;
                const f32 dy = p1.y - p2.y;
                const f32 dz = p1.z - p2.z;
                matched = dx <= 0.05f && dx >= -0.05f && dy <= 0.05f && dy >= -0.05f &&
                          dz <= 0.05f && dz >= -0.05f;
            } else {
                matched = hit1 && !hit2;
            }
            if (!matched) {
                ok = true;
                break;
            }
        }
        result = ok;
    }
    return result;
}

// 0x7100dac578
void Actor::sub_7100DAC578() {
    for (s32 i = 0; i < mActions.size(); ++i)
        static_cast<Action*>(mActions.at(i))->sub_7100DA7DC4();
}

// 0x7100dab548
void Actor::sub_7100DAB548() {
    if (u32(mState - 9) <= 1) {
        if (auto* actor = sead::DynamicCast<act::Actor>(mLink.getProc(nullptr)))
            actor->sleep(act::BaseProc::SleepWakeReason::_0);
    }
}

// 0x7100daa2e0
bool Actor::sub_7100DAA2E0() const {
    if (u32(mState - 9) < 5)
        return true;
    switch (mState) {
    case 14 ... 20:
    case 27:
        return true;
    default:
        return false;
    }
}

}  // namespace ksys::evt
