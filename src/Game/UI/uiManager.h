#pragma once

#include "KingSystem/Resource/resHandle.h"
#include "Game/UI/uiMainFieldArea.h"
#include "KingSystem/Resource/resResourceJpg.h"

#include <container/seadSafeArray.h>
#include <container/seadListImpl.h>
#include <heap/seadDisposer.h>
#include <prim/seadBitFlag.h>
#include <thread/seadCriticalSection.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <common/aglGPUMemAddr.h>
#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <common/aglTextureData.h>
#include <common/aglTextureSampler.h>
#include "Game/UI/uiTimer.h"
#include "Game/UI/uiUnkTiny.h"
#include "KingSystem/System/DebugBoard.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Controller;
class CriticalSection;
}

namespace eui {
class UIController;
}

namespace nn::ui2d {
class Pane;
}

namespace ksys::res {
class EntryFactoryBase;
}

namespace uking::ui {

// Placeholder: the object whose +0x20 field the manager's `_651e0` mirrors (the pin of the map / camera screens).
struct Unk_UiPinInfo {
    u8 _0[0x20];
    /* 0x20 */ s32 _20;
};

// 0x7100a6c0ec (declaration only): stores `value` at controller + 0x4bc and forwards to
// sead::ControllerBase::setLeftStickCrossThreshold with the default pair for the sign of `value`.
void sub_7100A6C0EC(sead::Controller* controller, f32 value);

// Pooled task list the manager destroys in its destructor (native 0x651e8 .. 0x65214). The nodes are
// sead::ListNode members at entry + 0x20; erased entries are pushed on the free list at 0x18.
struct ManagerTaskEntry {
    ManagerTaskEntry* mNextFree;
    u8 _8[0x18];
    sead::ListNode mNode;
};
struct ManagerTaskList : sead::ListImpl {
    sead::ListNode* firstNode() { return front(); }
    void eraseNode(sead::ListNode* node) { erase(node); }

    ManagerTaskEntry* mFreeList;
    ManagerTaskEntry* mBuffer;
    s32 mCapacity;
    s32 _pad;
};
KSYS_CHECK_SIZE_NX150(ManagerTaskList, 0x30);

// The UI manager singleton (CSV: uiManager::createInstance 0x7100a6e038, ctor 0x7100a6e0c4,
// instance pointer 0x71025f5ee0, size 0x653b0, disposer at +0x18). Only the fields that are used
// by the UI facade functions / read inline by AI code are declared (offsets from the original);
// the namespace and class name are guesses.
// Placeholder for the polymorphic base at Manager + 0 (the vtable at 0x710249c4e0 has sub-vtables at +0x8 / +0x10 for
// ActorMessageTransceiver::IHandler; neither the constructor nor the destructor calls anything for this base).
class ManagerBase {
public:
    virtual ~ManagerBase() = default;
};

class Manager : public ManagerBase, public ksys::ActorMessageTransceiver::IHandler {
    SEAD_SINGLETON_DISPOSER(Manager)
    Manager();

public:
    ~Manager() override;

    // 0x7100a7b994 (thunk 0x7100a7bb14): messages with a broker id of 2 - 4 go to sub_7100A7B9E8
    int handleMessage(const ksys::Message* message) override;
    // 0x7100a7b9e8 (CSV unnamed; not decompiled)
    int sub_7100A7B9E8(const ksys::Message& message);

    // 0x7100a7b5d8 (CSV uiManager::createAndLoadScreenIfNeeded)
    void createAndLoadScreenIfNeeded(s32 id);

    // Placeholder-named members (the CSV calls them uiManager::__autoN / x_N or leaves them unnamed).
    void sub_7100A76180();  // CSV loadSaveForStageUnload's target
    void sub_7100A76420();  // empty (CSV nullsub_6139)
    void sub_7100A76424();
    void sub_7100A79968();
    // 0x7100a7a6c0 (CSV uiManager::__auto6; placeholder name): stores `value` at 0x653a8 and applies it.
    void sub_7100A7A6C0(f32 value);
    // 0x7100a7ef28 (CSV uiManager::__auto7; placeholder name): stores 40.0f at 0x653a8 and applies it.
    void sub_7100A7EF28();
    // 0x7100a79a04: the pause callback: suspends the dialogue ducker, updates the map singleton and runs the
    // pause / unpause side of the Root38, OnUiActorMgr and StageState flags; always true.
    bool sub_7100A79A04();
    bool sub_7100A79B38();
    void sub_7100A79ED4();
    void sub_7100A7A4C0();
    void sub_7100A7A4C4();
    void sub_7100A7A6E4(s32 a1);
    void sub_7100A7A704(s32 a1);
    // 0x7100a7a72c (declared only; ScreenAppMenuBtn::m107 passes the Pa_CheckBtn_00 check state)
    void sub_7100A7A72C(bool checked);
    // 0x7100a7fe9c (declared only)
    void sub_7100A7FE9C();
    // 0x7100a7fd64: remembers `pane` in the list of panes at 0x652f0 (ignored when it is null or the list is full)
    void sub_7100A7FD64(nn::ui2d::Pane* pane);
    void sub_7100A7C904();
    void sub_7100A7DA38();
    void sub_7100A7C71C();
    void sub_7100A7F0D0();
    bool checkLoadResource(ksys::res::Handle* handle, const sead::SafeString& path);
    bool parseLocations();
    bool sub_7100A7F2EC(f32 radius, sead::SafeString* out_name, const sead::Vector3f* pos);
    // 0x7100a7f930 (declared only; Unk_7102485670::sub_7100A01918 passes a message / tip id)
    bool sub_7100A7F930(s32 id);
    bool sub_7100A7F468(sead::SafeString* out_name, const sead::Vector3f* position, f32 radius);
    void sub_7100A7C8D4();
    void sub_7100A7C9AC();
    void sub_7100A7CA68();
    void sub_7100A7C9C0();
    // inline-only in the original; name is a guess: 0x71009e3b84 and 0x7100990690 (twice: fixed strings and computed
    // ones) store both values together before calling sub_7100A7C9C0
    void setWarpDestination(const char* map, const char* point) {
        _65180 = map;
        _65188 = point;
    }
    void sub_7100A7CACC();
    void sub_7100A7A1A8();
    void sub_7100A7E590();
    static void sub_7100AA8698();  // 0x7100aa8698 (CSV unnamed; called by sub_7100A7C8D4)
    // 0x7100a7f81c (lane2 s47): under the lock at `_650f8`: false if `_650f0 > 0`, else sets it to 1, asks the graphics
    // system and returns true
    bool sub_7100A7F81C();
    // 0x7100a702e8 (CSV uiManager::x_1)
    void sub_7100A702E8(eui::UIController* controller);
    // 0x7100a7f8e8 / 0x7100a7f900 (CSV uiManager::__auto1 / __auto15; placeholder names): copy `_651e0` from / to
    // the pin info (ignored for null)
    void sub_7100A7F8E8(const Unk_UiPinInfo* info);
    void sub_7100A7F900(Unk_UiPinInfo* info) const;
    // 0x7100a7f918 / 0x7100a7fdb4 (CSV uiManager::__auto4 / __auto11; placeholder names)
    bool sub_7100A7F918() const;
    bool sub_7100A7FDB4() const;
    void sub_7100A7FDCC();
    // 0x7100a7f890 / 0x7100a7f8d4 (lane2 s47): restart the timer `_651ac` once the flag `_651c4` is set / init `_651c8`
    void sub_7100A7F890();
    void sub_7100A7F8D4();
    void sub_7100A7FBA4();
    bool sub_7100A7FDAC();
    // 0x7100a7b8cc / 0x7100a7b92c (placeholder names): whether the screen id is in one of the screen load /
    // unload lists of the manager's static 0x71025f5f90 object (0x1b0 / 0x170); the second also returns true above
    // ScreenId::PlainScreen (77).
    bool sub_7100A7B8CC(s32 id);
    bool sub_7100A7B92C(s32 id);
    // 0x7100a7041c (CSV uiManager::loadStaticInfo, 5.8 KB; declaration only)
    void loadStaticInfo(sead::Heap* heap);

    // inline-only in the original; name is a guess. The same test is inlined at the start of
    // 14 functions (the GanonBeast actor "rain" update 0x7100710938, GameSceneSubsys14::postCalc,
    // IceBlockMgr::__auto0, ...): state 1 - 4, flag bits 3 / 4 of the byte at 0x64c30 or the field at
    // 0x64c2c being 1.
    bool isPausedMaybe() const {
        return u32(_64c24 - 1) < 4 || (_64c30 & 0x18) != 0 || _64c2c == 1;
    }

    // The first member (destroyed last): a polymorphic object with a virtual destructor only.
    /* 0x38 */ u8 _38;
    u8 _39[0x40 - 0x39];
    /* 0x40 */ Unk_710249c410 _40;
    /* 0x48 */ s32 _48;
    /* 0x4c */ s32 _4c;
    /* 0x50 */ f32 _50;
    /* 0x54 */ f32 _54;
    /* 0x58 */ f32 _58;
    /* 0x5c */ f32 _5c;
    /* 0x60 */ f32 _60;
    /* 0x64 */ f32 _64;
    /* 0x68 */ f32 _68;
    /* 0x6c */ f32 _6c;
    /* 0x70 */ f32 _70;
    /* 0x74 */ u8 _74;
    u8 _75[0x78 - 0x75];
    /* 0x78 */ s32 _78;
    /* 0x7c */ s32 _7c;
    /* 0x80 */ sead::Vector3f _80;
    /* 0x8c */ sead::Vector3f _8c;
    /* 0x98 */ sead::Vector2f _98;
    /* 0xa0 */ f32 _a0;
    /* 0xa4 */ s32 _a4;
    /* 0xa8 */ s32 _a8;
    /* 0xac */ f32 _ac;
    /* 0xb0 */ sead::SafeArray<s32, 5> _b0;
    /* 0xc4 */ s32 _c4;
    /* 0xc8 */ s32 _c8;
    /* 0xcc */ s32 _cc;
    /* 0xd0 */ s32 _d0;
    /* 0xd4 */ s32 _d4;
    /* 0xd8 */ u64 _d8;
    /* 0xe0 */ u64 _e0;

    // inline-only in the original; names are guesses (the facade stores `*value` after fetching the
    // singleton, which a plain assignment through instance() does not reproduce).
    void setD8(const u64* value) { _d8 = *value; }
    void setE0(const u64* value) { _e0 = *value; }
    void set64c68(bool value) { _64c68 = value; }

    // 0x7100a7f2b0: indexed area list, with a shared empty list for an absent index.
    const MainFieldArea& sub_7100A7F2B0(s32 index) const;

    u8 _e8[0x5dda8 - 0xe8];
    // A6CC5C constructs this 15-element pool; A71EB4 fills it from the area resource.
    /* 0x5dda8 */ sead::FixedObjList<MainFieldArea, 15> mMainFieldAreas;
    u8 _627e8[0x649ec - 0x627e8];
    /* 0x649ec */ sead::BitFlag8 _649ec;
    u8 _649ed[0x649f0 - 0x649ed];
    /* 0x649f0 */ sead::Controller* _649f0;  // the controller the screens' UIControllers are registered with
    // Pad repeat settings applied to every screen's UIController (Manager::sub_7100A702E8).
    struct PadRepeat {
        u32 mask;
        u32 _4;
        u32 _8;
        u8 delay_frame;
        u8 pulse_frame;
        u8 _e[2];
    };
    /* 0x649f8 */ PadRepeat _649f8[6];
    u8 _64a58[0x64a80 - 0x64a58];
    // The screen message transceiver and the three debug-board transceivers (destructor A6E76C).
    /* 0x64a80 */ ksys::ActorMessageTransceiver _64a80;
    /* 0x64ad8 */ Unk_710246c458 _64ad8;
    /* 0x64ae8 */ Unk_710246c4d8 _64ae8;
    /* 0x64af8 */ Unk_710246c498 _64af8;
    u8 _64b08[0x64b0c - 0x64b08];
    /* 0x64b0c */ u32 _64b0c;
    /* 0x64b10 */ u32 _64b10;
    /* 0x64b14 */ u8 _64b14;
    /* 0x64b15 */ bool _64b15;
    u8 _64b16[0x64b20 - 0x64b16];
    // Constructor A6E0C4, destructor A6E76C and resource creators 9CE600 / 9CE27C / 9CAA34.
    /* 0x64b20 */ Unk_710247ee68 _64b20;
    /* 0x64b40 */ Unk_710247ee68 _64b40;
    /* 0x64b60 */ Unk_710247ee68 _64b60;
    /* 0x64b80 */ ksys::res::Handle mLocationResource;
    /* 0x64bd0 */ ksys::res::Handle _64bd0;
    u8 _64c20[0x64c24 - 0x64c20];
    /* 0x64c24 */ s32 _64c24;
    /* 0x64c28 */ s32 _64c28;
    /* 0x64c2c */ s32 _64c2c;

    // The flag word at 0x64c30 (bit 3 / 4 = pause related, see isPausedMaybe; 0x20, 0x40, 0x80 set /
    // cleared by the UI facade); byte 5 is also read on its own.
    union {
        /* 0x64c30 */ u64 _64c30;
        u8 _64c30_bytes[8];
    };
    /* 0x64c38 */ s32 _64c38;
    /* 0x64c3c */ s32 _64c3c;
    /* 0x64c40 */ s32 _64c40;
    /* 0x64c44 */ s32 _64c44;
    /* 0x64c48 */ s32 _64c48;  // the debug board message's target (0: none)
    u8 _64c4c[1];
    /* 0x64c4d */ u8 _64c4d;
    u8 _64c4e[0x64c60 - 0x64c4e];
    // Updated each frame by A76424; texture requests wait for two elapsed frames.
    /* 0x64c60 */ u32 mFrameNumber;
    u8 _64c64[0x64c68 - 0x64c64];
    /* 0x64c68 */ bool _64c68;
    u8 _64c69[0x64c78 - 0x64c69];
    // UI textures / render targets (the destructor frees the texture's image block first)
    /* 0x64c78 */ agl::TextureData mTextureData;
    /* 0x64da0 */ agl::RenderTargetColor mRenderTargetColor;
    /* 0x64f18 */ agl::RenderBuffer mRenderBuffer;
    /* 0x64f80 */ agl::TextureSampler mTextureSampler;
    /* 0x650f0 */ s32 _650f0;
    /* 0x650f8 */ sead::CriticalSection _650f8;
    // pointers released by the destructor (slot 0x20 / slot 0x8 virtual calls, delete[])
    /* 0x65138 */ void* _65138;
    /* 0x65140 */ agl::GPUMemVoidAddr _65140;
    /* 0x65158 */ void* _65158;
    /* 0x65160 */ void* _65160;
    /* 0x65168 */ s32 _65168;
    u8 _6516c[0x65170 - 0x6516c];
    // A6F194 constructs EntryFactory<Unk_710247eb88>; the texture worker passes it in LoadRequest.
    /* 0x65170 */ ksys::res::EntryFactoryBase* _65170;
    /* 0x65178 */ void* _65178;
    // map name / escape destination for the dungeon exit (set by sub_71009E3B84)
    /* 0x65180 */ const char* _65180;
    /* 0x65188 */ const char* _65188;
    u8 _65190[0x651ac - 0x65190];
    /* 0x651ac */ UiTimer _651ac;
    /* 0x651c4 */ bool _651c4;
    u8 _651c5[3];
    /* 0x651c8 */ UiTimer _651c8;
    /* 0x651e0 */ s32 _651e0;
    u8 _651e4[0x651e8 - 0x651e4];
    /* 0x651e8 */ ManagerTaskList mTaskList;
    /* 0x65218 */ bool _65218;
    u8 _65219[0x652e8 - 0x65219];
    /* 0x652e8 */ u8 _652e8;
    u8 _652e9[0x652f0 - 0x652e9];
    /* 0x652f0 */ s32 _652f0;  // count of the panes
    /* 0x652f4 */ s32 _652f4;  // capacity
    /* 0x652f8 */ nn::ui2d::Pane** _652f8;
    u8 _65300[0x65387 - 0x65300];
    /* 0x65387 */ u8 _65387;
    /* 0x65388 */ UiTimer _65388;
    /* 0x653a0 */ f32 _653a0;
    /* 0x653a4 */ s32 _653a4;  // frames since sub_7100A7FDCC started the timer (up to 150)
    /* 0x653a8 */ f32 _653a8;  // left-stick cross threshold mirrored to the UI controller (see sub_7100A6C0EC)
    u8 _653ac[0x653b0 - 0x653ac];
};
KSYS_CHECK_SIZE_NX150(Manager, 0x653b0);

}  // namespace uking::ui
