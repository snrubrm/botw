#pragma once

#include <container/seadBuffer.h>
#include <math/seadMatrix.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Resource/resResource.h"

namespace ksys::phys {

class HavokAI;

// Root table 0x7102519a98 contains only the two destructor slots. Native parse
// allocates entries at stride 0xa8; the resource lifecycle tests pointers +8/+28.
class Unk_7102519a98 {
public:
    explicit Unk_7102519a98(s32 value);
    virtual ~Unk_7102519a98();
    // 0x71012a6f50 (placeholder name; called by Unk_7102519b90::parse_): stores the entry data and sets flag 0x200.
    void sub_71012A6F50(s32 value, void* a, void* b, void* c, void* d);
    // 0x71012a705c (declaration only; placeholder name): applies `transform` directly (not added to a HavokAI).
    void sub_71012A705C(const sead::Matrix34f& transform);
    // 0x71012a7324 (placeholder name): through the HavokAI the entry was added to, else directly.
    void sub_71012A7324(const sead::Matrix34f& transform);
    void sub_71012A734C();
    void sub_71012A7544();
    bool sub_71012A7738();

    void* _8 = nullptr;
    void* _10 = nullptr;
    void* _18 = nullptr;
    void* _20 = nullptr;
    void* _28 = nullptr;
    void* _30 = nullptr;
    void* _38 = nullptr;
    void* _40 = nullptr;
    s32 _48;
    // Same request scheme as NavMeshObj2Maybe: the HavokAI it was added to, the pending HavokAI
    // (tag bits 0-1) and request flags (0x3c00: queued on _50).
    HavokAI* _50 = nullptr;
    sead::Atomic<HavokAI*> _58 = nullptr;
    // NavMeshLoadMgr::TileHandle::sub_7100F8AF0C requires bit 10 for every entry with _8 set.
    sead::Atomic<u32> _60 = 0;
    sead::Matrix34f _64 = sead::Matrix34f::ident;
    void* _98 = nullptr;
    void* _a0 = nullptr;
};
KSYS_CHECK_SIZE_NX150(Unk_7102519a98, 0xa8);

// Resource built at 0x71012aa370, with vtable 0x7102519b90 and entries of stride 0xa8.
class Unk_7102519b90 : public res::Resource {
    SEAD_RTTI_OVERRIDE(Unk_7102519b90, res::Resource)
public:
    Unk_7102519b90();
    ~Unk_7102519b90() override;

    const sead::Buffer<Unk_7102519a98>& getEntries() const { return mEntries; }
    sead::Buffer<Unk_7102519a98>& getEntries() { return mEntries; }

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
