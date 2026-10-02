#pragma once

#include <container/seadObjArray.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"

namespace uking::action {

// CSV name (AirOctaWoodBridgeUserTag::rtti1): the main body's user tag while AirOctaWoodBridge runs.
// vtable 0x7102363380 (D1 is PhysicsUserTag's).
class AirOctaWoodBridgeUserTag : public ksys::act::PhysicsUserTag {
    SEAD_RTTI_OVERRIDE(AirOctaWoodBridgeUserTag, ksys::act::PhysicsUserTag)
public:
    explicit AirOctaWoodBridgeUserTag(ksys::act::Actor* actor) : PhysicsUserTag(actor) {}

    void onImpulse(ksys::phys::RigidBody* body_a, ksys::phys::RigidBody* body_b,
                   float impulse_a) override;

    f32 _18 = 0;  // last impulse
};
KSYS_CHECK_SIZE_NX150(AirOctaWoodBridgeUserTag, 0x20);

class AirOctaWoodBridge : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AirOctaWoodBridge, ksys::act::ai::Action)
public:
    explicit AirOctaWoodBridge(const InitArg& arg);
    ~AirOctaWoodBridge() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void sub_7100089F18();

    AirOctaWoodBridgeUserTag _20{mActor};
    sead::FixedObjArray<ksys::act::BaseProcLink, 2> _40;
    f32 _90 = 3.0f;
    bool _94 = false;
};
KSYS_CHECK_SIZE_NX150(AirOctaWoodBridge, 0x98);

}  // namespace uking::action
