#include "hkpCharacterStateManager.h"
#include <Havok/Physics2012/Utilities/CharacterControl/StateMachine/hkpCharacterState.h>
#include <cstring>

// NON_MATCHING: the compiler tail-calls memset rather than retaining the original call and return.
hkpCharacterStateManager::hkpCharacterStateManager() {
    std::memset(mStates, 0, sizeof(mStates));
}

// NON_MATCHING: D0 schedules allocator arguments and restores differently; D2 matches.
hkpCharacterStateManager::~hkpCharacterStateManager() {
    for (int i = 0; i < 11; ++i) {
        if (mStates[i]) {
            mStates[i]->removeReference();
            mStates[i] = nullptr;
        }
    }
}

// NON_MATCHING: the inlined reference-count CAS block layout differs.
void hkpCharacterStateManager::sub_710167D718(hkpCharacterState* state, hkUint32 index) {
    state->addReference();
    if (mStates[index])
        mStates[index]->removeReference();
    mStates[index] = state;
}

hkpCharacterState* hkpCharacterStateManager::sub_710167D7D4(hkUint32 index) const {
    return mStates[index];
}
