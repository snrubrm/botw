#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <prim/seadBitFlag.h>
#include <prim/seadDelegate.h>
#include <time/seadTickTime.h>
#include "KingSystem/Resource/resResource.h"

namespace nn::gfx {
class ResTexture;
}

namespace ksys::util {
class Task;
class TaskThread;
class TaskMgr;
}  // namespace ksys::util

namespace ksys::res {

// Native table 24F9B08 and the complete FE43B8 stack producer establish a
// Context containing a borrowed FileDevice and path, with extent 0x20.
class Unk_71024f9b08 : public Context {
    SEAD_RTTI_OVERRIDE(Unk_71024f9b08, Context)
public:
    ~Unk_71024f9b08() override;

    sead::FileDevice* mFileDevice;
    sead::SafeString mPath;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f9b08, 0x20);

class ArchiveWork;
class Counter;
class Unk_71024f9a08;
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

    // Complete FE8074 produces this 0x50-byte record; FE59AC independently
    // copies its fields into a texture validation task request.
    struct ValidateArg {
        void setPath(const sead::SafeString& path);
        void setHash(u32 hash);

        bool _0 = true;
        bool _1 = false;
        bool _2 = false;
        bool _3 = true;
        bool _4 = true;
        nn::gfx::ResTexture* mTexture = nullptr;
        Unk_71024F9D48* mHandle = nullptr;
        sead::FileDevice* mFileDevice = nullptr;
        sead::SafeString mRequester;
        u32 mTextureFlags = 0;
        sead::SafeString mPath;
        u32 mHash = 0;
    };
    KSYS_CHECK_SIZE_NX150(ValidateArg, 0x50);
    // Native FE59AC, declared only.
    bool validateUser(const ValidateArg& arg);

    void preCalc();
    void calc();

    ArchiveWork* getArchiveWork() const;
    // inline-only in the original; name is a guess. FE848C and FE84D4 repeat this read.
    s32 getGeneration() const { return mGeneration; }
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
    u8 _a[2];
    // Native FE2534 zeroes +C; FE54C0 increments it modulo the signed maximum.
    s32 mGeneration;
    u8 _10[0x28 - 0x10];
    Counter* mHeapCounter;
    util::Task* _30;
    u8 _38[0x48 - 0x38];
    util::TaskMgr* _48;
    util::TaskThread* _50;
    u8 _58[0xa0 - 0x58];
    sead::TickTime mTickTime;
    u8 _a8[0x118 - 0xa8];
    // FE2534 sets the node offset to 8; FE3004 inserts texture resources here.
    sead::OffsetList<Unk_71024f9a08> mResources;
    u8 _130[0x158 - 0x130];
    sead::Delegate1R<TextureHandleMgr, void*, bool> _158{nullptr, nullptr};
    u8 _178[0x768 - 0x178];
    ArchiveWork* mArchiveWork;
};

}  // namespace ksys::res
