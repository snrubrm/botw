#include "hkpCharacterStateOnGround.h"
#include <Havok/Physics2012/Utilities/CharacterControl/StateMachine/hkpCharacterContext.h>

void hkpCharacterStateOnGround::m9(hkpCharacterContext& context, const hkpCharacterInput& input,
                                 hkpCharacterOutput& output) {
    if (input.m_wantJump)
        context.sub_7101677864(hkpCharacterStateType(1), input, output);
    else if (input.m_atLadder)
        context.sub_7101677864(hkpCharacterStateType(3), input, output);
    else if (input.m_surfaceInfo.m_supportedState != hkpSurfaceInfo::SUPPORTED) {
        if (_18)
            output.m_velocity.subMul(input.m_up, input.m_velocity.dot<3>(input.m_up));
        context.sub_7101677864(hkpCharacterStateType(2), input, output);
    }
}

void hkpCharacterStateOnGround::sub_7101674940(hkReal speed) { mSpeed = speed; }
