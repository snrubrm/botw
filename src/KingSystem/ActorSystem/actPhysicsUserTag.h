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

    // Inline-only in the original; name is a guess: stores the actor reference and the value, then ORs
    // in one flag per true argument (bits 0 / 2 / 3 / 4 of _15, the ones resetMaybe clears). Used by
    // sub_71005DBE1C (0x71005dbe1c).
    void setStateMaybe(s32 actor_id, u8 value, bool a3, bool a4, bool a5, bool a6) {
        _10 = actor_id;
        _14 = value;
        if (a3)
            _15 |= 0x1;
        if (a4)
            _15 |= 0x4;
        if (a5)
            _15 |= 0x8;
        if (a6)
            _15 |= 0x10;
    }

private:
    Actor* mActor = nullptr;
    int _10 = -1;
    u8 _14 = 0;
    u8 _15 = 0;
};
KSYS_CHECK_SIZE_NX150(PhysicsUserTag, 0x18);

}  // namespace ksys::act
