#pragma once

#include "KingSystem/Resource/resHandle.h"

namespace al {
class ByamlIter;
}

namespace sead {
class Heap;
}

namespace ksys::snd {

// The "BarslistInfo.byml" archive: a BYML iterator plus the resource handle it was parsed from.
class BarslistArchive {
public:
    BarslistArchive();
    virtual ~BarslistArchive();

    // 0x710105790c (4 bytes): tail call to load.
    void loadRes(sead::Heap* heap);
    // 0x7101057910: loads Sound/ResourceList/BarslistInfo.byml and builds mIter from its data.
    void load(sead::Heap* heap);
    // 0x7101057520: the sub-iterator of the bars list at `key`.
    al::ByamlIter getIter(const sead::SafeString& key) const;
    // 0x7101057580: the entry count of `iter`.
    s32 getSize(const al::ByamlIter& iter) const;
    // 0x710105767c: the asset name at `index` in `iter`.
    const char* getEntryName(const al::ByamlIter& iter, s32 index) const;

    /* 0x08 */ al::ByamlIter* mIter = nullptr;
    /* 0x10 */ res::Handle mHandle;
};
KSYS_CHECK_SIZE_NX150(BarslistArchive, 0x60);

}  // namespace ksys::snd
