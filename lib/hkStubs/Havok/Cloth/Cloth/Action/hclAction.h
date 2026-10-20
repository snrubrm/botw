#pragma once
#include <Havok/Common/Base/hkBase.h>
class Unk_71025335A8;

// Native constructor 0x710140b86c and table 0x7102533520 establish the
// hkReferencedObject prefix and 0x10 extent. The callback spelling is unknown.
class hclAction : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hclAction)
    hclAction();
    ~hclAction() override = default;
    // Native game override 0x71013082e4 retains sim/output in x1/x2 and
    // timestep in s0. Source argument order is inferred from this ABI.
    virtual void m5(Unk_71025335A8* sim_cloth, hkVector4f* output, hkReal timestep) = 0;
    virtual bool m6() const;
    virtual bool m7() const;
};
static_assert(sizeof(hclAction) == 0x10);
