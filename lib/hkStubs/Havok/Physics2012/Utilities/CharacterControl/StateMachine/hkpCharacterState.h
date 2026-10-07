#pragma once

#include <Havok/Common/Base/hkBase.h>

enum hkpCharacterStateType : hkInt32;
struct hkpCharacterInput;
struct hkpCharacterOutput;
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
