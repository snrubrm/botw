#pragma once

#include <Havok/Cloth/Cloth/Action/hclAction.h>
#include <basis/seadTypes.h>
#include <heap/seadHeap.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

class ClothSet;
struct ClothParam;

// Constructor at 0x7101307fe4, vtable at 0x7102520120. Owns an hclAction and
// attaches it to the cloth instances of a ClothSet while enabled.
class ClothActionHandle {
public:
    ClothActionHandle(ClothSet* set, s16 index);
    virtual ~ClothActionHandle();
    virtual void m2(sead::Heap* heap);
    // Called by Action::m5. Argument order is taken from 0x71013082e4 and the override at 0x71013086bc.
    virtual void m3(Unk_71025335A8* sim_cloth, hkVector4f* output, hkReal timestep) = 0;

    void setEnabled(bool enabled);
    bool initialize(sead::Heap* heap);
    hclAction* getAction() const;
    const ClothParam* getClothParam() const;

    ClothSet* mClothSet;
    hclAction* mAction;
    s16 mIndex;
    bool mEnabled;

private:
    // Allocated by initialize (0x18 bytes). Its vtable (0x7102520150) forwards m5 to the owner.
    class Action : public hclAction {
    public:
        HK_DECLARE_CLASS_ALLOCATOR(Action)
        explicit Action(ClothActionHandle* owner) : mOwner(owner) {}
        ~Action() override = default;
        void m5(Unk_71025335A8* sim_cloth, hkVector4f* output, hkReal timestep) override;

        ClothActionHandle* mOwner;
    };
    static_assert(sizeof(Action) == 0x18);
};
KSYS_CHECK_SIZE_NX150(ClothActionHandle, 0x20);

}  // namespace ksys::phys
