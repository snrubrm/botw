#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>

namespace ksys::act {

class ActorLinkConstDataAccess;
class BaseProcLink;

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
    // 0x7100d74880 (CSV Attention::__auto8): the target's type, or 0x1800029 if there is none.
    u32 sub_7100D74880();
    // 0x7100d744b8 (CSV Attention::__auto12): sets the requested target link.
    void sub_7100D744B8(const BaseProcLink& link);
};

}  // namespace ksys::act
