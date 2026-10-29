#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>

namespace agl::cull {
class OcclusionQuery;
}

namespace agl::lght {
class LocalLightMapObj;
}

namespace gsys {

class ModelDrawObj;

// A per-frame list of draw objects written into the ModelWorkBuffer of one core: either plain
// object pointers or 0x30-byte entries (flag bit 1), see begin/add/end.
class ModelDrawObjStream {
public:
    struct Entry {
        u32 _0;
        u16 _4;
        u8 _6;
        const agl::lght::LocalLightMapObj* mLocalLightMapObj;
        void* _10;
        const agl::cull::OcclusionQuery* mOcclusionQuery;
        u16 _20;
        u8 _22[0x30 - 0x22];
    };
    static_assert(sizeof(Entry) == 0x30);

    ModelDrawObjStream();
    ~ModelDrawObjStream();

    void begin(bool use_entries, bool flag, s32 core);
    void add(const ModelDrawObj* obj, u32 value, s32 param);
    void end(s32 core);
    const Entry* mount() const;

private:
    s32 mCount;
    Entry* mEntries;
    const ModelDrawObj** mObjs;
    sead::BitFlag16 mFlags;
};
static_assert(sizeof(ModelDrawObjStream) == 0x20);

// Partial: the environment info bound to a draw object stream. The constructor 0x7100c7e24c
// stores a vtable at +0 (the destructor is the only virtual), -1 at +8 and 0xffff at +0xc;
// bind 0x7100c7e278 is still undecompiled.
class ModelEnvInfo {
public:
    ModelEnvInfo();
    virtual ~ModelEnvInfo();

    s32 _8;        // 0x7100c7e278 stores a lookup index here; set by the constructor
    u16 _c = 0xffff;
};
static_assert(sizeof(ModelEnvInfo) == 0x10);

}  // namespace gsys
