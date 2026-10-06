#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {

class ActorLinkConstDataAccess;
class BaseProcLink;
class AttClient;
class PlayerLink;

// Name from the CSV (Attention::createInstance 0x7100d73aa0, ctor 0x7100d73b28, calc 0x7100d75680,
// init, setPlayerLink, setPauseState, ...; instance pointer at 0x71026009b0, object size 0xe28).
// The global lock-on / target attention manager (the per-actor object is ActorAttention). A
// polymorphic sead singleton. Only the accessors that the AI actions call are declared; the member
// layout is not modelled: 8 target lists (stride 0x50 from +0x7a8: count at +0, array at +8) and the
// current-target list at +0x7f8 / +0x800 (enabled by the byte at +0xe20).
// TODO: incomplete.
class Attention {
    SEAD_SINGLETON_DISPOSER(Attention)
    Attention();
    virtual ~Attention();

public:
    // 0x7100d741a8 (CSV Attention::x): acquires the current target; false if there is none.
    bool x(ActorLinkConstDataAccess* out);
    // 0x7100d74148 (CSV Attention::__auto9): same for a BaseProcLink.
    bool sub_7100D74148(BaseProcLink* out);
    // 0x7100d74114 (CSV Attention::__auto7): whether there is a current target.
    bool sub_7100D74114() const;
    // 0x7100d753b0: enabled-state query used by the ride input actions; declaration only.
    bool sub_7100D753B0() const;
    // 0x7100d742e8 (CSV Attention::__auto10): whether the target list `list` is empty.
    bool sub_7100D742E8(s32 list) const;
    // 0x7100d7438c (CSV Attention::x_0): acquires entry `index` of the target list `list`.
    bool x_0(s32 list, s32 index, ActorLinkConstDataAccess* out);
    // 0x7100d7430c (CSV Attention::__auto3): same for a BaseProcLink.
    bool sub_7100D7430C(s32 list, s32 index, BaseProcLink* out);
    // 0x7100d7482c (CSV Attention::__auto0): acquires the target that `__auto8` describes.
    bool sub_7100D7482C(ActorLinkConstDataAccess* out);
    // 0x7100d747d8 (CSV Attention::__auto2): same for a BaseProcLink.
    bool sub_7100D747D8(BaseProcLink* out);
    // 0x7100d74880 (CSV Attention::__auto8; declared only, the original zero-extends the result with `and x0, x0,
    // #0xffffffff`): the target's type, or 0x1800029 if there is none.
    u64 sub_7100D74880();
    // 0x7100d744b8 (CSV Attention::__auto12): sets the requested target link.
    void sub_7100D744B8(const BaseProcLink& link);
    // 0x7100d748fc (declaration only; placeholder name): whether a target of `type` exists (wraps 0x7100d7457c).
    bool sub_7100D748FC(u64 type);
    // 0x7100d74530 (declaration only; placeholder name): sets bits 2-3 of the flag byte at +0xe22 to 2, +0xdb8 = `type`,
    // +0xdc0 = `target`.
    void sub_7100D74530(u64 type, void* target);
    // 0x7100d7565c (CSV Attention::setPauseState): bit 0 of the flag byte at +0xe22.
    void setPauseState(bool paused);

    // lane4 s30: partial layout (the CSV's 8 target lists, one per AttType; list 1 = Lock is the current target).
    struct TargetList {
        /* 0x00 */ s32 mCount;
        /* 0x08 */ AttClient** mEntries;
        /* 0x10 */ u8 _10[0x40];
    };

    /* 0x028 */ u8 _28[0x7a8 - 0x28];
    /* 0x7a8 */ sead::SafeArray<TargetList, 8> mLists;
    /* 0xa28 */ u8 _a28[0xc18 - 0xa28];
    /* 0xc18 */ void* _c18;  // set by setController (RootTask::calc)
    /* 0xc20 */ PlayerLink* _c20;
    /* 0xc28 */ void* _c28;  // set by setSomeFn
    /* 0xc30 */ f32 _c30;
    /* 0xc34 */ f32 _c34;
    /* 0xc38 */ f32 _c38;
    /* 0xc3c */ f32 _c3c;
    /* 0xc40 */ u8 _c40[0xc4c - 0xc40];
    /* 0xc4c */ u32 _c4c;
    /* 0xc50 */ u8 _c50[0xd98 - 0xc50];
    /* 0xd98 */ BaseProcLink mRequestedTarget;
    /* 0xda8 */ u8 _da8[0xdb8 - 0xda8];
    /* 0xdb8 */ u32 _db8;
    /* 0xdbc */ u8 _dbc[0xdc0 - 0xdbc];
    /* 0xdc0 */ void* _dc0;
    /* 0xdc8 */ u8 _dc8[0xe20 - 0xdc8];
    /* 0xe20 */ bool mEnabled;
    /* 0xe21 */ u8 mFlagsE21;
    /* 0xe22 */ sead::BitFlag8 mFlagsE22;
};

}  // namespace ksys::act
