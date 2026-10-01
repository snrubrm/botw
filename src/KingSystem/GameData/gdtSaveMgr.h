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
    bool auto0();
    bool enableGdtMgrChangeOnlyMode(s32 x);
    void auto5();
    bool x_6(u32 idx);
    bool auto6(s32 idx);
    bool x_0(s32 idx);
    void auto4();

private:
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
    u8 _40[0xf8 - 0x40];
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
    u8 _f88[0xf98 - 0xf88];
    gdt::TriggerParam* _f98;
    u8 _fa0[0x103c - 0xfa0];
    s32 _103c;
    u8 _1040[0x11c8 - 0x1040];
    sead::ObjArray<Unk3> _11c8;
    u8 _11e8[0x1de8 - 0x11e8];
};
KSYS_CHECK_SIZE_NX150(SaveMgr, 0x1de8);

}  // namespace ksys
