#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <container/seadObjList.h>
#include <container/seadTreeMap.h>
#include <prim/seadBitFlag.h>
#include <prim/seadDelegate.h>
#include <time/seadTickTime.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Resource/resTempResourceLoader.h"
#include "KingSystem/Utils/Thread/Task.h"

namespace nn::g3d {
class ResFile;
}

namespace nn::gfx {
class ResTexture;
}

namespace ksys {
class Task;
class TaskThread;
class TaskMgr;
}  // namespace ksys

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
class CompactedHeap;
class Unk_710251A740;
template <typename T>
class EntryFactory;
// Complete FE6E9C constructs this native factory within its global state.
extern EntryFactory<Unk_710251A740> sUnk_710260EA08;
class Unk_71024f9a08;
class Unk_71024f9a50;
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
    bool validateUser(const ValidateArg& arg);

    bool doCalc();
    void preCalc();
    void calc();

    ArchiveWork* getArchiveWork() const;
    // inline-only in the original; name is a guess. FE848C and FE84D4 repeat this read.
    s32 getGeneration() const { return mGeneration; }
    void repairAllHandlesForSync();
    bool invoked2(void* data);
    bool invoked3(void* data);
    void x_1(s32* count);
    bool invoked4(void* data);
    // Complete FE5754 removes this resource from the manager and frees its allocations.
    void x(Unk_71024f9a08* resource);
    bool invoked5(void*);
    bool invoked6(void* data);
    bool bfres_file_stuff(void* data);
    bool bfres_file_stuff_2(void* data);
    // Complete FE6134 and independent FE3760 establish this native helper.
    bool x_0(nn::g3d::ResFile* file, bool tex1, Unk_71024f9a08** resource);
    void invoked7(TaskPostRunResult* result, const TaskPostRunContext& context);
    void repairExecute(TaskPostRunResult* result, const TaskPostRunContext& context);
    void invoked8(const TaskRemoveCallbackContext& context);
    void invoked9(const TaskRemoveCallbackContext& context);
    bool repairTexture(Unk_71024f9a08* resource);
    void repairHandleForSync(Unk_71024f9a08* resource);
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
    u8 _10[0x20 - 0x10];
    CompactedHeap* mTextureHeap;
    Counter* mHeapCounter;
    Task* _30;
    u8 _38[0x48 - 0x38];
    TaskMgr* _48;
    TaskThread* _50;
    // Complete FE2534 constructs this lock; FE4318 holds it during repair.
    sead::CriticalSection mCS;
    sead::TickTime _98;
    sead::TickTime mTickTime;
    u8 _a8[0xb8 - 0xa8];
    // Complete FE2890 allocates 24-byte pointer nodes for each of these lists.
    // Independent FE5754 recycles resources; FE3628 / FE2F58 queue and pop them.
    sead::ObjList<Unk_71024f9a08*> mFreeResources;
    sead::ObjList<Unk_71024f9a08*> mPendingRemoval;
    // FE2534 sets the node offset to 8; FE3004 inserts texture resources here.
    sead::OffsetList<Unk_71024f9a08> mResources;
    sead::TreeMapImpl<Unk_71024f9a50> mResourceMap;
    u8 _138[0x158 - 0x138];
    sead::Delegate1R<TextureHandleMgr, void*, bool> _158{nullptr, nullptr};
    // Complete FE2890 initializes this task delegate for FE3004; FE59AC uses it.
    sead::Delegate1R<TextureHandleMgr, void*, bool> _178{nullptr, nullptr};
    // Complete FE2890 initializes this delegate for FE3628; FE5B44 uses it.
    sead::Delegate1R<TextureHandleMgr, void*, bool> _198{nullptr, nullptr};
    // Complete FE2890 initializes this delegate for FE3760.
    TaskDelegateT<TextureHandleMgr> _1b8{nullptr, nullptr};
    // Complete FE2890 initializes this delegate for FE3DC0.
    TaskDelegateT<TextureHandleMgr> _1d8{nullptr, nullptr};
    // Complete FE2890 initializes this delegate for FE4318; FE5C98 uses it.
    sead::Delegate1R<TextureHandleMgr, void*, bool> _1f8{nullptr, nullptr};
    // FE5D84 / FE5EC4 independently supply these as the native task callbacks.
    TaskPostRunCallbackT<TextureHandleMgr> _218{nullptr, nullptr};
    // Complete FE2890 initializes this post-run callback for FE4918.
    TaskPostRunCallbackT<TextureHandleMgr> _238{nullptr, nullptr};
    // Complete FE2890 initializes this removal callback for FE4B6C.
    TaskRemoveCallbackT<TextureHandleMgr> _258{nullptr, nullptr};
    TaskRemoveCallbackT<TextureHandleMgr> _278{nullptr, nullptr};
    // Complete FE2890 initializes this task delegate for FE43B8.
    TaskDelegateT<TextureHandleMgr> _298{nullptr, nullptr};
    u8 _2b8[0x5e0 - 0x2b8];
    // Complete FE2534 constructs this loader; independent FE4B6C unloads it.
    TempResourceLoader mLoader;
    ArchiveWork* mArchiveWork;
};

// Complete FE2890 independently passes its manager to setter FE11CC.
// Native 260E858 is distinct from sInstance at 260EAC8.
extern TextureHandleMgr* sUnk_710260E858;
void sub_7100FE11CC(TextureHandleMgr* manager);
void sub_7100FE11F0(nn::gfx::ResTexture* texture, nn::gfx::ResTexture* fallback);
nn::gfx::ResTexture* sub_7100FE124C();

}  // namespace ksys::res
