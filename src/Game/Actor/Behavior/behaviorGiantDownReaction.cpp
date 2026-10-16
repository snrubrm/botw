#include "Game/Actor/Behavior/behaviorGiantDownReaction.h"
#include <prim/seadFormatPrint.h>
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/Ragdoll/physRagdollRigidBody.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {
bool sub_7100EEB19C(ksys::phys::RigidBody*, sead::Vector3f*, sead::Vector3f*,
                    sead::Vector3f*, void*, void*, void*);
}

namespace uking::behavior {

GiantDownReaction::GiantDownReaction(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
GiantDownReaction::~GiantDownReaction() {
    ;
}

bool GiantDownReaction::init_(sead::Heap* heap) {
    return true;
}

void GiantDownReaction::enter() {
    _70 = false;
    _74 = -1.0f;
}

// NON_MATCHING: the matrix angle is loaded after the contact calls; register and stack scheduling differ.
void GiantDownReaction::calc() {
    if (_74 > 0.0f)
        ksys::Timer::update(&_74, -1.0f);
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return;
    sead::Matrix34f matrix;
    if (actor->_868)
        actor->_868->sub_71006EDE54(&matrix, mDownCheckRagdollRbName_s);
    else
        matrix = actor->getMtx();
    auto* ragdoll = actor->getRagdollInstance();
    bool grounded = false;
    for (const auto& name : mGroundCheckRagdollRbName_s) {
        auto* body = ragdoll->getBoneRigidBodyByName(name);
        if (!body)
            continue;
        sead::Vector3f contact;
        if (action::sub_7100EEB19C(body, nullptr, &contact, nullptr, nullptr, nullptr, nullptr)) {
            grounded = true;
            break;
        }
    }
    if (grounded && matrix.m[1][1] < 0.70710677f) {
        if (!_70 && _74 <= 0.0f) {
            _70 = true;
            _74 = static_cast<f32>(*mIntervalTime_s);
            xlinkSearchAndEmit(actor, "Down", 2, nullptr);
        }
    } else {
        _70 = false;
    }
}

void GiantDownReaction::leave() {}

void GiantDownReaction::loadParams() {
    getStaticParam(&mIntervalTime_s, "IntervalTime");
    getStaticParam(&mDownCheckRagdollRbName_s, "DownCheckRagdollRbName");
    sead::FixedSafeString<32> key;
    for (u32 i = 0; i < 3; i++) {
        (sead::StringCutOffPrintFormatter(&key) << "GroundCheckRagdollRbName%d", i) << sead::flush;
        getStaticParam(&mGroundCheckRagdollRbName_s[i], key);
    }
}

}  // namespace uking::behavior
