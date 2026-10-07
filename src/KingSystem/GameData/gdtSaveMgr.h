#pragma once

#include <basis/seadTypes.h>
#include <container/seadObjArray.h>
#include <heap/seadDisposer.h>
#include <mc/seadCoreInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/GameData/gdtTriggerParam.h"
#include "KingSystem/Resource/resResourceGameSaveData.h"
#include "KingSystem/Resource/resHandle.h"
#include <container/seadSafeArray.h>
#include <filedevice/seadFileDevice.h>

namespace sead {
class DelegateThread;
}  // namespace sead

namespace ksys::gdt {
class TriggerParam;
template <typename T>
class FlagT;
}  // namespace ksys::gdt

namespace uking {
class SaveSystem;
class StartupSaveCheckStage;
}

namespace ksys {

// FIXME
class SaveMgr {
    SEAD_SINGLETON_DISPOSER(SaveMgr)
    SaveMgr();
    virtual ~SaveMgr();

public:
    struct InitArg {
        sead::Heap* heap;
        u32 _8;
        u32 buf_size;
        u32 buf_alignment;
        u32 size2;
        u32 thread_priority;
        u32 _1c;
        sead::CoreIdMask thread_affinity;
        sead::SafeString save_common_str = "save_common";
        sead::SafeString save_act_str = "save_act";
        bool is_demo = false;
        sead::SafeString save_rid_demo_dir;
        void* _60 = nullptr;
        u32 _68 = 0;
        u32 _6c;
    };
    KSYS_CHECK_SIZE_NX150(InitArg, 0x70);

    void init(const InitArg& arg);
    void loadGameSaveData();
    void registerGameSavedataFactoryAndLoad();
    void loadSavedataformat(const sead::SafeString& path, sead::Heap* heap);
    u32 sub_7100E0F578() const;
    void unloadResources();
    void loadFlagValuesFromTriggerParam(gdt::TriggerParam* buffer);
    void invokedLoadFlagValueFromTriggerParam(res::GameSaveData::Flag& flag);

    void auto3();
    bool someCheck() const;
    // lane4 s49 (placeholder name): the save thread state (`SaveSystem::isFinishedSavingMaybe` tests it for 0).
    u32 get38() const { return _38; }
    bool auto0();
    bool enableGdtMgrChangeOnlyMode(s32 x);
    void auto5();
    bool x_6(u32 idx);
    bool auto6(s32 idx);
    bool x_0(s32 idx);
    // 0x7100e089f0 (CSV x_5; declared only): writes `value` at the saved position _103c of the buffer when it is set.
    void x_5(u32 value);
    // 0x7100e0402c (CSV trackerFileExistsStuff): whether `path` exists on the file device named by the save mount
    // string at +0x80.
    bool sub_7100E0402C(const sead::SafeString& path);
    // 0x7100e044a8 (CSV unnamed; declared only): writes `size` bytes of `data` for the save file `path`; `value` is the
    // UI manager field.
    bool sub_7100E044A8(const sead::SafeString& path, void* data, u32 value, u32 size);
    // 0x7100e04968 (CSV x; declared only): writes `size` bytes of `buffer` to the save file `path`.
    bool x(const sead::SafeString& path, void* buffer, u32 size);
    bool saveAlbumPicture(const sead::SafeString& path, void* data, s32 size, u32 capacity);
    bool sub_7100E0461C(const sead::SafeString& path, void* data, s32 size, u32 capacity);
    bool x_1(s32 index, const sead::SafeString& path, bool a, bool byte_swap);
    bool sub_7100E041D0(s32 index, const sead::SafeString& file_name);
    bool sub_7100E04810(s32 index, const sead::SafeString& file_name);
    bool sub_7100E081E4(const res::GameSaveData::Flag& entry,
                        const gdt::FlagT<sead::FixedSafeString<32>>* flag, u32 size, u32 offset);
    bool sub_7100E083AC(const res::GameSaveData::Flag& entry,
                        const gdt::FlagT<sead::FixedSafeString<64>>* flag, u32 size, u32 offset);
    bool sub_7100E08574(const res::GameSaveData::Flag& entry,
                        const gdt::FlagT<sead::FixedSafeString<256>>* flag, u32 size, u32 offset);
    void x_7();
    void x_8(const sead::ObjArray<gdt::TriggerParam::FlagCopyRecord>& records);
    void x_11(const sead::ObjArray<gdt::TriggerParam::FlagCopyRecord>& records);
    void x_12(const sead::ObjArray<gdt::TriggerParam::FlagCopyRecord>& records);
    void x_13(const sead::ObjArray<gdt::TriggerParam::FlagCopyRecord>& records);
    void x_14(const sead::ObjArray<gdt::TriggerParam::FlagCopyRecord>& records);
    void x_15(const sead::ObjArray<gdt::TriggerParam::FlagCopyRecord>& records);
    void x_16(const sead::ObjArray<gdt::TriggerParam::FlagCopyRecord>& records);
    void x_17(const sead::ObjArray<gdt::TriggerParam::FlagCopyRecord>& records);
    bool sub_7100E05560(const sead::SafeString& mount, const sead::SafeString& path, s32 mode, bool retry);
    void sub_7100E0BC7C();
    bool sub_7100E0C688();
    void sub_7100E07E3C(const sead::ObjArray<gdt::TriggerParam::FlagCopyRecord>& records);
    void someCheck_0(gdt::FlagT<bool>* flag);
    void someStuff(gdt::FlagT<s32>* flag);
    void auto4();

    // Placeholder (type unknown): the object at +0x1020; EventAutoSaveAction calls its first virtual
    // function with (true, false).
    class Unk1020 {
    public:
        virtual bool m0(bool a1, bool a2) = 0;
    };
    Unk1020* get1020() const { return _1020; }

private:
    friend class uking::SaveSystem;
    friend class uking::StartupSaveCheckStage;

    struct Unk3 {
        u8 _0[1];
    };

    sead::Heap* mHeap;
    sead::DelegateThread* _30;
    u32 _38;
    u32 _3c;
    u32 _40;
    u8 _44[0x80 - 0x44];
    sead::SafeString _80;
    u8 _90[0xf8 - 0x90];
    bool _f8;
    u8 _f9[0x100 - 0xf9];
    sead::FileDevice* _100;
    u8 _108[0x140 - 0x108];
    u16 _140;
    u16 _142;
    u8 _144[4];
    s32 _148;
    s32 _14c[32];
    u8 _1cc[4];
    sead::FixedSafeString<256> _1d0;
    sead::FileHandle mFileHandle;
    res::Handle mSaveDataArcHandle;
    sead::SafeArray<res::Handle, 32> mSaveDataHandles;
    u8 _d78[0xe00 - 0xd78];
    res::GameSaveData* _e00;
    u8* _e08;
    u32 _e10;
    u32 _e14;
    u32 _e18;
    u8 _e1c[0xe28 - 0xe1c];
    u32 _e28;
    bool _e2c;
    u8 _e2d[3];
    void* _e30;
    u8 _e38[8];
    u32 _e40;
    u32 _e44;
    u32 _e48;
    bool _e4c;
    u8 _e4d[3];
    void* _e50;
    u32 _e58;
    u8 _e5c[4];
    sead::FixedSafeString<256> _e60;
    u32 _f78;
    u8 _f7c[4];
    void* _f80;
    u8 _f88[0xf94 - 0xf88];
    s32 _f94;
    gdt::TriggerParam* _f98;
    u8 _fa0[0x1020 - 0xfa0];
    Unk1020* _1020;
    u8 _1028[0x103c - 0x1028];
    s32 _103c;
    u8 _1040[0x1058 - 0x1040];
    u8 _1058;
    u8 _1059;
    bool _105a;
    bool _105b;
    u8 _105c[4];
    res::Handle mLoadHandle;
    sead::FixedSafeString<128> _10b0;
    u8 _1148[0x11c8 - 0x1148];
    sead::ObjArray<Unk3> _11c8;
    u8 _11e8[0x1de8 - 0x11e8];
};
KSYS_CHECK_SIZE_NX150(SaveMgr, 0x1de8);

}  // namespace ksys
