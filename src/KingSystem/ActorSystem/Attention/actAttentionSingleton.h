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
    // 0x7100d74d78 (CSV Attention::x_1): updates the target lists with `client` (calls the four operations below).
    void sub_7100D74D78(AttClient* client);
    // 0x7100d74dd4 / 0x7100d74fec / 0x7100d750e0 / 0x7100d751d4 (CSV Attention::x_2 .. x_5; declared only).
    void sub_7100D74DD4(AttClient* client);
    void sub_7100D74FEC(AttClient* client);
    void sub_7100D750E0(AttClient* client);
    void sub_7100D751D4(AttClient* client);
    // 0x7100d7457c (declaration only): the client to use among the target lists; `filter` selects whether
    // `code` (an AttActionCode, None for any) has to match.
    AttClient* sub_7100D7457C(bool filter, u32 code) const;
    // 0x7100d74208: `*out = _58 of the current target`; false if there is none.
    bool sub_7100D74208(u32* out) const;
    // 0x7100d74258: whether `client` is in its target list.
    bool sub_7100D74258(const AttClient* client) const;
    // 0x7100d74550: whether sub_7100D7457C(false, None) has an actor.
    bool sub_7100D74550() const;
    // 0x7100d748b8 (declared only; the original keeps the action code in a stack slot): whether the action
    // code of sub_7100D7457C(false, None) is not Remind.
    bool sub_7100D748B8() const;
    // 0x7100d748fc (declared only; the original zero-extends `code` with an `and x2, x1, #0xffffffff`): whether
    // sub_7100D7457C(true, code) finds a client.
    bool sub_7100D748FC(u64 code) const;
    // 0x7100d74414: number of entries of the target list `list`.
    s32 getTargetCount(s32 list) const;
    // 0x7100d74504: `_c4c = value` for 0 and 1.
    void sub_7100D74504(u32 value);
    // 0x7100d74480 (CSV Attention::setPlayerLink): called by ksys::setPlayerLink.
    void setPlayerLink(PlayerLink* link);
    // 0x7100d74488 (CSV Attention::__auto11): the player's actor, or releases the accessor.
    bool sub_7100D74488(ActorLinkConstDataAccess* out);
    // 0x7100d744a8 (CSV Attention::__auto4): sets bit 0 of the flag byte at +0xe21.
    void sub_7100D744A8();
    // 0x7100d74514 (CSV Attention::__auto1) / 0x7100d74530: set the request state of the flag byte at +0xe22
    // (value 1 / 2) and the requested target.
    void sub_7100D74514(void* target);
    void sub_7100D74530(u64 type, void* target);
    // 0x7100d753d8: whether `client` is the current target.
    bool sub_7100D753D8(const AttClient* client) const;
    // 0x7100d75410 / 18 / 20 / 28: the floats at +0xc30..0xc3c.
    f32 sub_7100D75410() const;
    f32 sub_7100D75418() const;
    f32 sub_7100D75420() const;
    f32 sub_7100D75428() const;
    // 0x7100d75430 / 48 / 60 / 78: forward to the player (PlayerLink slots 18 / 26 / 29 / 67).
    bool sub_7100D75430() const;
    bool sub_7100D75448() const;
    bool sub_7100D75460() const;
    bool sub_7100D75478() const;
    // 0x7100d75490: bit 1 of the flag byte at +0xe21.
    bool sub_7100D75490() const;
    // 0x7100d75654 (CSV Attention::setSomeFn) / 0x7100d75678 (CSV Attention::setController).
    void setSomeFn(void* fn);
    void setController(void* controller);
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
    /* 0xc50 */ u8 _c50[0xd88 - 0xc50];
    /* 0xd88 */ f32 _d88;  // centre / width of the random delay AttClient's constructor picks
    /* 0xd8c */ f32 _d8c;
    /* 0xd90 */ u8 _d90[0xd98 - 0xd90];
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
