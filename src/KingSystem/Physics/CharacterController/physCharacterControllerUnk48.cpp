#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include <Havok/Physics2012/Utilities/CharacterControl/StateMachine/hkpCharacterContext.h>

namespace ksys::phys {

CharacterControllerUnk48::CharacterControllerUnk48(u32 x) : _8c(x) {}

// Native Horse deleting destructors call this base destructor across translation units.
CharacterControllerUnk48::~CharacterControllerUnk48() = default;

void CharacterControllerUnk48::sub_7101675D38(hkpCharacterContext& context,
                                              hkpCharacterStateType type,
                                              const hkpCharacterInput& input,
                                              hkpCharacterOutput& output) {
    _30.setZero();
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
