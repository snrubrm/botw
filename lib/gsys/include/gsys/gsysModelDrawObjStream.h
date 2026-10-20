#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>

namespace agl::lght {
class LocalLightMapObj;
}

namespace gsys {

class ModelDrawObj;
class ModelOcclusionQuery;

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
        const ModelOcclusionQuery* mOcclusionQuery;
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

}  // namespace gsys
