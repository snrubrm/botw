#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>
#include <time/seadTickTime.h>

namespace ksys::util {
class Task;
class TaskThread;
}  // namespace ksys::util

namespace ksys::res {

class ArchiveWork;
class Unk_71024F9D48;

// TODO: very incomplete
class TextureHandleMgr {
public:
    virtual ~TextureHandleMgr();
    static TextureHandleMgr* instance() { return sInstance; }
    static void setInstance(TextureHandleMgr* mgr);
    struct InvalidateArg {
        bool _0 = true;
        bool _1 = false;
        Unk_71024F9D48* _8;
    };
    bool invalidateUser(const InvalidateArg& arg);

    void preCalc();
    void calc();

    ArchiveWork* getArchiveWork() const;
    void repairAllHandlesForSync();
    void clearAllCache();
    void sub_7100FE60B0(bool on);
    void sub_7100FE60DC(bool on);
    bool sub_7100FE6120() const;
    // 0x7100fe54c0 (CSV TextureHandleMgr::d; declared only)
    void d();
    // 0x7100fe4cf4 (CSV TextureHandleMgr::xx; declared only)
    void xx();
    void sub_7100FE5190();
    void sub_7100FE53BC();
    void sub_7100FE5334();
    // 0x7100fe56d8 (CSV TextureHandleMgr::isTooSlow): true (and restarts the timer) when bit 2 of the second flag byte is
    // set and at least `seconds` seconds passed since the timer was started.
    bool isTooSlow(s32 seconds);

private:
    static TextureHandleMgr* sInstance;
    // TODO
    sead::BitFlag8 mFlags;
    sead::BitFlag8 mFlags2;
    u8 _a[0x30 - 0xa];
    util::Task* _30;
    u8 _38[0x50 - 0x38];
    util::TaskThread* _50;
    u8 _58[0xa0 - 0x58];
    sead::TickTime mTickTime;
    u8 _a8[0x768 - 0xa8];
    ArchiveWork* mArchiveWork;
};

}  // namespace ksys::res
