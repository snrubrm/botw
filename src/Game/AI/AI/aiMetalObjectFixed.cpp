#include "Game/AI/AI/aiMetalObjectFixed.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

MetalObjectFixed::MetalObjectFixed(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MetalObjectFixed::~MetalObjectFixed() = default;

bool MetalObjectFixed::init_(sead::Heap* heap) {
    _40 = true;
    return true;
}

// NON_MATCHING: the original loads mActor after reading *mIsFixedPlace_m (scheduling)
void MetalObjectFixed::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_40) {
        _40 = false;
        auto* actor = mActor;
        if (*mIsFixedPlace_m) {
            ksys::act::disableAllAttClients(actor);
            if (auto* body = actor->getMainBody())
                body->changeMotionType(ksys::phys::MotionType::Keyframed);
            changeChild("固定中");
            return;
        }
        ksys::act::enableAllAttClients(actor);
    } else {
        auto* actor = mActor;
        if (*mIsFixedPlace_m) {
            if (auto* physics = actor->getPhysics())
                physics->sub_7100FBADDC();
        }
        ksys::act::enableAllAttClients(actor);
    }
    changeChild("通常");
}

void MetalObjectFixed::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MetalObjectFixed::loadParams_() {
    getMapUnitParam(&mIsFixedPlace_m, "IsFixedPlace");
}

}  // namespace uking::ai
