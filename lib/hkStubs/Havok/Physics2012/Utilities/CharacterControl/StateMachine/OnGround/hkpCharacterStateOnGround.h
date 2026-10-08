#pragma once

#include <Havok/Physics2012/Utilities/CharacterControl/StateMachine/hkpCharacterState.h>

class hkpCharacterStateOnGround : public hkpCharacterState {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpCharacterStateOnGround)
    hkpCharacterStateOnGround();
    // NON_MATCHING: D0 schedules the allocator receiver argument before size selection.
    ~hkpCharacterStateOnGround() override = default;
    hkpCharacterStateType m5() const override;
    void m8(hkpCharacterContext&, const hkpCharacterInput&, hkpCharacterOutput&) override;
    void m9(hkpCharacterContext&, const hkpCharacterInput&, hkpCharacterOutput&) override;
    void sub_7101674940(hkReal speed);

protected:
    hkReal mGain;
    hkReal mSpeed;
    hkReal mMaximumAcceleration;
    hkBool _18;
    hkBool _19;
    hkBool _1a;
};
// Constructor1674590 and derived producerF67B54 prove20.
static_assert(sizeof(hkpCharacterStateOnGround) == 0x20);
