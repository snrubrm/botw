#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <mc/seadCoreInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

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

private:
    struct Unk {
        u8 _0[0x28];
        u32 _28;
    };

    u8 _28[0x38 - 0x28];
    u32 _38;
    u8 _3c[0x140 - 0x3c];
    u16 _140;
    u8 _142[0xe00 - 0x142];
    Unk* _e00;
    u8 _e08[0xe10 - 0xe08];
    u32 _e10;
    u8 _e14[0xe40 - 0xe14];
    u32 _e40;
    u8 _e44[0xf80 - 0xe44];
    void* _f80;
    u8 _f88[0x1de8 - 0xf88];
};
KSYS_CHECK_SIZE_NX150(SaveMgr, 0x1de8);

}  // namespace ksys
