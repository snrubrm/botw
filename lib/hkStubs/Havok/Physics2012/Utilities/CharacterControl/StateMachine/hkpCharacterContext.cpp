#include "hkpCharacterContext.h"

hkpCharacterStateType hkpCharacterContext::sub_710167785C() const { return mCurrentState; }
const hkVector4& hkpCharacterContext::sub_7101677910() const { return _20; }
void hkpCharacterContext::sub_7101677908(hkInt32 type) { mType = type; }
void hkpCharacterContext::sub_71016778F8(hkReal gain, hkReal velocity, hkReal acceleration) {
    mGain = gain;
    mMaximumVelocity = velocity;
    mMaximumAcceleration = acceleration;
}
