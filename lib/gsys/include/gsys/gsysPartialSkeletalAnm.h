#pragma once

#include <container/seadBuffer.h>
#include <gsys/gsysModelAccessKey.h>

namespace gsys {

// The vtable at 0x71024c9f98 and initialize at 0x7100bff364 identify this base.
// Its byte-flag buffer occupies +0x10/+0x18; the Ex constructor initializes +8/+a.
class PartialSkeletalAnmBase {
public:
    PartialSkeletalAnmBase() = default;
    virtual ~PartialSkeletalAnmBase();

    void initialize(s32 count, sead::Heap* heap);

    // 0x7100bff4cc operates on one 0x80-byte mask per Model unit.
    struct BoneMask {
        u32 words[32];
    };
    void sub_7100BFF4CC(Model* model, sead::Buffer<BoneMask>* masks) const;

protected:
    virtual void initializeImpl_(s32 count, sead::Heap* heap) = 0;
    virtual BoneAccessKey* getBoneAccessKeyImpl_(s32 index) = 0;
    virtual const BoneAccessKey* getBoneAccessKeyImpl_(s32 index) const = 0;

public:
    // Registered key count; ASList::Unk1::sub_7101164FF8 resets this halfword.
    u16 mCount = 0;
protected:
    u16 _a = 1;
    sead::Buffer<u8> mFlags;
};

// The vtable at 0x71024c9fd0 adds no slots. Its key array has 0x38-byte elements
// constructed by BoneAccessKeyEx::BoneAccessKeyEx at 0x7100bff834.
class PartialSkeletalAnmEx : public PartialSkeletalAnmBase {
public:
    PartialSkeletalAnmEx();
    ~PartialSkeletalAnmEx() override;

    bool sub_7100BFF8E4(const Model* model, const sead::SafeString& name, u8 flag);
    bool sub_7100BFF95C(const Model* model, const sead::SafeString& name, u8 flag);

protected:
    void initializeImpl_(s32 count, sead::Heap* heap) override;
    BoneAccessKey* getBoneAccessKeyImpl_(s32 index) override;
    const BoneAccessKey* getBoneAccessKeyImpl_(s32 index) const override;

    sead::Buffer<BoneAccessKeyEx> mBoneKeys;
};

static_assert(sizeof(PartialSkeletalAnmBase) == 0x20);
static_assert(sizeof(PartialSkeletalAnmEx) == 0x30);

}  // namespace gsys
