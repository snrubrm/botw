#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include <Havok/Physics2012/Utilities/CharacterControl/StateMachine/hkpCharacterContext.h>

namespace ksys::phys {

// NON_MATCHING: the vtable lacks slots 10-12 (0x7100f68f48, 0x7100f68fb8, 0x7100f69014: undeclared), so the
// second vtable pointer offset differs; the zero vector store is also scheduled differently.
CharacterControllerUnk48::CharacterControllerUnk48(u32 x) : _8c(x) {}

void CharacterControllerUnk48::sub_7101675D38(hkpCharacterContext& context,
                                              hkpCharacterStateType type,
                                              const hkpCharacterInput& input,
                                              hkpCharacterOutput& output) {
    _30 = 0;
    _34 = 0;
    _38 = 0;
    _3c = 0;
    _40 = 1.0f;
    _44.set(0, 0, 0);
    _90 = 0;
    _98 = false;
    _9c = -1.0f;
}

void CharacterControllerUnk48::m9(hkpCharacterContext& context, const hkpCharacterInput& input,
                                  hkpCharacterOutput& output) {
    if (input.m_wantJump || input.m_surfaceInfo.m_supportedState != hkpSurfaceInfo::SUPPORTED)
        context.sub_7101677864(hkpCharacterStateType(1), input, output);
}

f32* CharacterControllerUnk48::sub_7100F68F38() {
    return &_5c;
}

f32* CharacterControllerUnk48::sub_7100F68F40() {
    return &_74;
}

}  // namespace ksys::phys
