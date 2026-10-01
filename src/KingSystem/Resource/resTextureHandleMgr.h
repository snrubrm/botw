#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>

namespace ksys::util {
class Task;
class TaskThread;
}  // namespace ksys::util

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
    void sub_7100FE5190();
    void sub_7100FE5334();

private:
    // TODO
    sead::BitFlag8 mFlags;
    sead::BitFlag8 mFlags2;
    u8 _a[0x30 - 0xa];
    util::Task* _30;
    u8 _38[0x50 - 0x38];
    util::TaskThread* _50;
    u8 _58[0x768 - 0x58];
    ArchiveWork* mArchiveWork;
};

}  // namespace ksys::res
