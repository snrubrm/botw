#include "hkpCharacterContext.h"

// NON_MATCHING: initialization scheduling and the inlined reference-count CAS block layout differ.
hkpCharacterContext::hkpCharacterContext(hkpCharacterStateManager* manager,
                                         hkpCharacterStateType state)
    : mType(0), mStateManager(manager), mCurrentState(state), mPreviousState(state),
      _20(0, 0, 0, 0), _30(0), mFilterEnable(true), mMaximumAcceleration(625.0f),
      mMaximumVelocity(20.0f), mGain(1.0f) {
    mStateManager->addReference();
}

// NON_MATCHING: reference-count CAS block layout differs; D0 also schedules allocator arguments early.
hkpCharacterContext::~hkpCharacterContext() {
    mStateManager->removeReference();
}

hkpCharacterStateType hkpCharacterContext::sub_710167785C() const { return mCurrentState; }
void hkpCharacterContext::sub_7101677864(hkpCharacterStateType state,
                                      const hkpCharacterInput& input,
                                      hkpCharacterOutput& output) {
    const hkpCharacterStateType previous_state = mCurrentState;
    mStateManager->sub_710167D7D4(previous_state)
        ->sub_7101675D38(*this, state, input, output);
    mCurrentState = state;
    mStateManager->sub_710167D7D4(state)
        ->sub_7101675D34(*this, previous_state, input, output);
    _30 = 0;
}
const hkVector4& hkpCharacterContext::sub_7101677910() const { return _20; }
void hkpCharacterContext::sub_7101677908(hkInt32 type) { mType = type; }
void hkpCharacterContext::sub_71016778F8(hkReal gain, hkReal velocity, hkReal acceleration) {
    mGain = gain;
    mMaximumVelocity = velocity;
    mMaximumAcceleration = acceleration;
}
