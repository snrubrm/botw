#pragma once

#include "KingSystem/Physics/System/physUserTag.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;
class BaseProcAccessor;

class PhysicsUserTag : public phys::UserTag {
    SEAD_RTTI_OVERRIDE(PhysicsUserTag, phys::UserTag)

public:
    explicit PhysicsUserTag(Actor* actor);
    ~PhysicsUserTag() override;

    Actor* getActor(BaseProcAccessor* accessor, Actor* other_actor) const;
    bool acquireActor(BaseProcAccessor* accessor) const;

    Actor* getActor() const { return mActor; }

    void onMaxPositionExceeded(phys::RigidBody* body) override;
    void onImpulse(phys::RigidBody* body_a, phys::RigidBody* body_b, float impulse_a) override;
    void onBodyShapeChanged(phys::RigidBody* body) override;
    void m5(Unk5* arg) override;
    const sead::SafeString& getName() const override;
    void m7(phys::RigidBody* rigid_body, int a) override;
    const sead::SafeString& getName(phys::RigidBody* rigid_body) const override;

    // Inline-only in the original; name is a guess: the actor reference goes back to -1 and bits
    // 0 / 2 / 3 / 4 of the flag byte are cleared (0xe2 keeps the other bits). Used by
    // sub_71005DC158 (0x71005dc158) when the controller's tag is a PhysicsUserTag.
    void resetMaybe() {
        _10 = -1;
        _14 = 0;
        _15 &= 0xe2;
    }

private:
    Actor* mActor = nullptr;
    int _10 = -1;
    u8 _14 = 0;
    u8 _15 = 0;
};
KSYS_CHECK_SIZE_NX150(PhysicsUserTag, 0x18);

}  // namespace ksys::act
