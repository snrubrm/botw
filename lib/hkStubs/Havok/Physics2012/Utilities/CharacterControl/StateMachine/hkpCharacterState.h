#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Common/Base/Types/Physics/hkStepInfo.h>

enum hkpCharacterStateType : hkInt32;
// getGround 0x7101679428 writes this 0x40-byte surface record. The supported
// state is read at input+0x40 by the ground/air state implementations.
struct hkpSurfaceInfo {
    enum SupportedState : hkInt32 { UNSUPPORTED, SLIDING, SUPPORTED };

    SupportedState m_supportedState;
    hkUint8 _4[0xc];
    hkVector4f m_surfaceNormal;
    hkVector4f m_surfaceVelocity;
    hkReal m_surfaceDistanceExcess;
    hkBool m_surfaceIsDynamic;
    hkUint8 _35[0xb];
};
static_assert(sizeof(hkpSurfaceInfo) == 0x40);

// The controller allocates 0xd0 at 0x7100f5dc88. Native InAir::m8 at
// 0x710167a114 proves the vectors and step delta; m9 proves the ladder byte.
// Unidentified portions retain padding rather than invented field semantics.
struct hkpCharacterInput {
    hkReal m_inputLR;
    hkReal m_inputUD;
    hkBool m_wantJump;  // OnGround::m9 at 0x71016745d4 dispatches state 1 when set.
    hkUint8 _9[7];
    hkVector4f m_up;
    hkVector4f m_forward;
    hkBool m_atLadder;
    hkUint8 _31[0xf];
    hkpSurfaceInfo m_surfaceInfo;
    hkStepInfo m_stepInfo;
    hkUint8 _90[0x10];
    hkVector4f m_velocity;
    hkVector4f m_characterGravity;
    hkUint8 _c0[0x10];
};
static_assert(sizeof(hkpCharacterInput) == 0xd0);
static_assert(offsetof(hkpCharacterInput, m_surfaceInfo) == 0x40);
static_assert(offsetof(hkpCharacterInput, m_stepInfo) == 0x80);
static_assert(offsetof(hkpCharacterInput, m_velocity) == 0xa0);

// The original minimal state at 0x7100f67b20 stores a complete Q register,
// including a zero W lane; native InAir::m8 also reads/writes all 16 bytes.
struct hkpCharacterOutput {
    hkVector4f m_velocity;
};
static_assert(sizeof(hkpCharacterOutput) == 0x10);
class hkpCharacterContext;

// The state protocol is proved by Context1677864 and the ground/air vtables.
// Unknown virtual spellings retain slot or address placeholders.
class hkpCharacterState : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpCharacterState)
    // Both original state vtables use the existing shared empty base destructor.
    ~hkpCharacterState() override = default;

    virtual hkpCharacterStateType m5() const = 0;
    virtual void sub_7101675D34(hkpCharacterContext&, hkpCharacterStateType,
                              const hkpCharacterInput&, hkpCharacterOutput&);
    virtual void sub_7101675D38(hkpCharacterContext&, hkpCharacterStateType,
                              const hkpCharacterInput&, hkpCharacterOutput&);
    virtual void m8(hkpCharacterContext&, const hkpCharacterInput&, hkpCharacterOutput&) = 0;
    virtual void m9(hkpCharacterContext&, const hkpCharacterInput&, hkpCharacterOutput&) = 0;
};
static_assert(sizeof(hkpCharacterState) == 0x10);
