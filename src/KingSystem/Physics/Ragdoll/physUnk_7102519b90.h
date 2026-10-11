#pragma once

#include <container/seadBuffer.h>
#include "KingSystem/Resource/resResource.h"

namespace ksys::phys {

// Root table 0x7102519a98 contains only the two destructor slots. Native parse
// allocates entries at stride 0xa8; the resource lifecycle tests pointers +8/+28.
class Unk_7102519a98 {
public:
    explicit Unk_7102519a98(s32 value);
    virtual ~Unk_7102519a98();
    void sub_71012A734C();
    void sub_71012A7544();
    bool sub_71012A7738();

    void* _8;
    u8 _10[0x28 - 0x10];
    void* _28;
    u8 _30[0xa8 - 0x30];
};
KSYS_CHECK_SIZE_NX150(Unk_7102519a98, 0xa8);

// Resource built at 0x71012aa370, with vtable 0x7102519b90 and entries of stride 0xa8.
class Unk_7102519b90 : public res::Resource {
    SEAD_RTTI_OVERRIDE(Unk_7102519b90, res::Resource)
public:
    Unk_7102519b90();
    ~Unk_7102519b90() override;

protected:
    bool needsParse() const override { return true; }
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;
    void finalize_() override;
    bool finishParsing_() override;
    bool m7_() override;

private:
    sead::Buffer<Unk_7102519a98> mEntries;
};
KSYS_CHECK_SIZE_NX150(Unk_7102519b90, 0x48);

}  // namespace ksys::phys
