#pragma once

#include <basis/seadTypes.h>
#include <container/seadObjArray.h>
#include <heap/seadDisposer.h>
#include <mc/seadCoreInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class DelegateThread;
}  // namespace sead

namespace ksys::gdt {
class TriggerParam;
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

    struct Unk2 {
        u32 _0;
        s32 _4;
    };

    struct Unk3 {
        u8 _0[1];
    };

    struct Unk {
        u8 _0[0x20];
        Unk2* _20;
        u32 _28;
    };

    u8 _28[0x30 - 0x28];
    sead::DelegateThread* _30;
    u32 _38;
    u32 _3c;
    u32 _40;
    u8 _44[0x80 - 0x44];
    sead::SafeString _80;
    u8 _90[0xf8 - 0x90];
    bool _f8;
    u8 _f9[0x140 - 0xf9];
    u16 _140;
    u8 _142[0x148 - 0x142];
    s32 _148;
    u8 _14c[0x80];
    u8 _1cc[0xe00 - 0x1cc];
    Unk* _e00;
    u8* _e08;
    u32 _e10;
    u32 _e14;
    u32 _e18;
    u8 _e1c[0xe40 - 0xe1c];
    u32 _e40;
    u32 _e44;
    u32 _e48;
    u8 _e4c[0xf80 - 0xe4c];
    void* _f80;
    u8 _f88[0xf94 - 0xf88];
    s32 _f94;
    gdt::TriggerParam* _f98;
    u8 _fa0[0x1020 - 0xfa0];
    Unk1020* _1020;
    u8 _1028[0x103c - 0x1028];
    s32 _103c;
    u8 _1040[0x11c8 - 0x1040];
    sead::ObjArray<Unk3> _11c8;
    u8 _11e8[0x1de8 - 0x11e8];
};
KSYS_CHECK_SIZE_NX150(SaveMgr, 0x1de8);

}  // namespace ksys
