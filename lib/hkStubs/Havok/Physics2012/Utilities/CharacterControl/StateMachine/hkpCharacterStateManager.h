#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkpCharacterState;

class hkpCharacterStateManager : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpCharacterStateManager)
    hkpCharacterStateManager();
    ~hkpCharacterStateManager() override;
    void sub_710167D718(hkpCharacterState* state, hkUint32 index);
    hkpCharacterState* sub_710167D7D4(hkUint32 index) const;

private:
    // Constructor167D55C clears eleven pointers; registration167D718 retains each state.
    hkpCharacterState* mStates[11];
};
static_assert(sizeof(hkpCharacterStateManager) == 0x68);
