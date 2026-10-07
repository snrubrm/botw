#pragma once

#include <Havok/Physics2012/Utilities/CharacterControl/StateMachine/hkpCharacterState.h>
#include <Havok/Physics2012/Utilities/CharacterControl/StateMachine/hkpCharacterStateManager.h>

class hkpCharacterContext : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpCharacterContext)
    hkpCharacterContext(hkpCharacterStateManager*, hkpCharacterStateType);
    ~hkpCharacterContext() override;

    hkpCharacterStateType sub_710167785C() const;
    void sub_7101677864(hkpCharacterStateType, const hkpCharacterInput&, hkpCharacterOutput&);
    void sub_71016778F8(hkReal gain, hkReal maximum_velocity, hkReal maximum_acceleration);
    void sub_7101677908(hkInt32 type);
    const hkVector4& sub_7101677910() const;

private:
    // Constructor16776B0 reuses the actual referenced-object tail at C.
    hkInt32 mType;
    hkpCharacterStateManager* mStateManager;
    hkpCharacterStateType mCurrentState;
    hkpCharacterStateType mPreviousState;
    // Getter1677910 and independent vector consumers1674658/F61F04 prove hkVector4.
    hkVector4 _20;
    hkInt32 _30;
    hkBool mFilterEnable;
    hkReal mMaximumAcceleration;
    hkReal mMaximumVelocity;
    hkReal mGain;
};
// Constructor16776B0 and original deleting destructor16777A0 independently prove50.
static_assert(sizeof(hkpCharacterContext) == 0x50);
