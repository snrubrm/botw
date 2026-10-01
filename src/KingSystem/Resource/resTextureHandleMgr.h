#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>

namespace ksys::res {

class ArchiveWork;

// TODO: very incomplete
class TextureHandleMgr {
public:
    virtual ~TextureHandleMgr();

    void preCalc();
    void calc();

    ArchiveWork* getArchiveWork() const;
    void repairAllHandlesForSync();
    void clearAllCache();
    void sub_7100FE60B0(bool on);
    void sub_7100FE60DC(bool on);
    bool sub_7100FE6120() const;

private:
    // TODO
    sead::BitFlag8 mFlags;
    sead::BitFlag8 mFlags2;
    u8 _a[0x768 - 0xa];
    ArchiveWork* mArchiveWork;
};

}  // namespace ksys::res
