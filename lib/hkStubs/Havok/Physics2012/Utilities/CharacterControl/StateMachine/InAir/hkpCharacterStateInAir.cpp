#include "hkpCharacterStateInAir.h"
#include <Havok/Physics2012/Utilities/CharacterControl/StateMachine/hkpCharacterContext.h>

void hkpCharacterStateInAir::m9(hkpCharacterContext& context, const hkpCharacterInput& input,
                              hkpCharacterOutput& output) {
    if (input.m_surfaceInfo.m_supportedState == hkpSurfaceInfo::SUPPORTED)
        context.sub_7101677864(hkpCharacterStateType(0), input, output);
    else if (input.m_atLadder)
        context.sub_7101677864(hkpCharacterStateType(3), input, output);
}

void hkpCharacterStateInAir::sub_710167A220(hkReal speed) { mSpeed = speed; }
