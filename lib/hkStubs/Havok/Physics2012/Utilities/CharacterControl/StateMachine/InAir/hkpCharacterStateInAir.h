#pragma once

#include <Havok/Physics2012/Utilities/CharacterControl/StateMachine/hkpCharacterState.h>

class hkpCharacterStateInAir : public hkpCharacterState {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpCharacterStateInAir)
    hkpCharacterStateInAir();
    // NON_MATCHING: D0 schedules the allocator receiver argument before size selection.
    ~hkpCharacterStateInAir() override = default;
    hkpCharacterStateType m5() const override;
    void m8(hkpCharacterContext&, const hkpCharacterInput&, hkpCharacterOutput&) override;
    void m9(hkpCharacterContext&, const hkpCharacterInput&, hkpCharacterOutput&) override;
    void sub_710167A220(hkReal speed);

protected:
    hkReal mGain;
    hkReal mSpeed;
    hkReal mMaximumAcceleration;
};
// Constructor167A0A4 and derived producerF67670 prove18.
static_assert(sizeof(hkpCharacterStateInAir) == 0x18);
