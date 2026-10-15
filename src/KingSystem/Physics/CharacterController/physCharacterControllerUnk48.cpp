#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include <Havok/Physics2012/Utilities/CharacterControl/StateMachine/hkpCharacterContext.h>

namespace ksys::phys {

void CharacterControllerUnk48::m9(hkpCharacterContext& context, const hkpCharacterInput& input,
                                  hkpCharacterOutput& output) {
    if (input.m_wantJump || input.m_surfaceInfo.m_supportedState != hkpSurfaceInfo::SUPPORTED)
        context.sub_7101677864(hkpCharacterStateType(1), input, output);
}

f32* CharacterControllerUnk48::sub_7100F68F38() {
    return &_5c;
}

}  // namespace ksys::phys
