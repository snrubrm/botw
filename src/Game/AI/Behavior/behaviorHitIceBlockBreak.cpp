#include "Game/AI/Behavior/behaviorHitIceBlockBreak.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::behavior {

HitIceBlockBreak::HitIceBlockBreak(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
HitIceBlockBreak::~HitIceBlockBreak() {
    ;
}

void HitIceBlockBreak::m8() {}

void HitIceBlockBreak::m9() {}

void HitIceBlockBreak::loadParams() {
    getStaticParam(&mRigidBodyName_s, "RigidBodyName");
}

bool HitIceBlockBreak::m6(sead::Heap* heap) {
    auto* actor = mActor;
    _38 = actor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), mRigidBodyName_s.cstr());
    return true;
}

void HitIceBlockBreak::m7() {
    if (_38)
        sub_7100627F7C(_38);
}

}  // namespace uking::behavior
