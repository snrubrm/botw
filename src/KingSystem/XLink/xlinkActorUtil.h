#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <xlink2/xlink2HandleELink.h>
#include <xlink2/xlink2HandleSLink.h>

namespace ksys::act {
class Actor;
}

namespace ksys::xlink {
class XLink;
}

// Free functions at the end of the xlink manager translation unit (0x7101240fe8 - 0x7101241d20)
// that emit / hold / stop xlink events of an actor. `kind` selects the user instances:
// 0 = ELink, 1 = SLink, 2 = both. Names are from the CSV or placeholders.

// A pair of xlink2 handles (ELink + SLink) filled by the emit functions below. AI classes embed it
// as two consecutive handles. Placeholder name (first method address); its methods (0x71012419b4 -
// 0x7101241bb0) are declared only (they use xlink2 Handle/Event internals lib/xlink2 lacks).
struct Unk_71012419b4 {
    /// Sets the emitted events' position.
    void sub_71012419B4(const sead::Vector3f& pos);
    /// Sets the emitted events' matrix.
    void sub_7101241A44(const sead::Matrix34f& mtx);
    /// Whether the handle of `kind` (0 = ELink, 1 = SLink, 2 = both) is active.
    bool sub_7101241AD8(int kind);
    /// Whether either handle is active (CSV eft::Effect::x_0).
    bool sub_7101241B6C() const;
    /// Fades both events (CSV eft::Effect::fadeXLink).
    void fadeXLink();

    xlink2::HandleELink mELink;
    xlink2::HandleSLink mSLink;
};

/// 0x7101240fe8: which user instances the actor has (0 = ELink, 1 = SLink, 2 = both, 3 = none).
int sub_7101240FE8(ksys::act::Actor* actor);
void sub_71012410C8(ksys::xlink::XLink* xlink, const char* name, int kind,
                    Unk_71012419b4* handle);
void xlinkSearchAndEmit(ksys::act::Actor* actor, const char* name, int kind,
                        Unk_71012419b4* handle);
/// searchAndHold version of xlinkSearchAndEmit (CSV name).
void flyingObjectEmitXlink(ksys::act::Actor* actor, const char* name, int kind,
                           Unk_71012419b4* handle);
/// 0x710124127c: kills all ELink events / stops all SLink events.
void sub_710124127C(ksys::act::Actor* actor, int kind);
/// 0x71012412e4: sets an xlink property (if assigned, or always if `force`).
void sub_71012412E4(ksys::act::Actor* actor, u32 idx, f32 value, bool force);
/// 0x7101241390 (CSV Actor::xlinkEventOn): int version of sub_71012412E4.
void xlinkEventOn(ksys::act::Actor* actor, u32 idx, s32 value, bool force);

namespace ksys::eft {

// Names from the CSV (eft::searchAndEmitELink 0x7100da07fc, eft::searchAndEmitSLink 0x710105dd24; the
// SLink one sits in the UI sound TU). They emit an event on the actor's ELink / SLink user instance
// (XLink::_48 / _50) and return its handle, or a copy of a function-local static empty handle when
// the actor has none (ELink: also for a null actor; SLink: also when XLink::_cc bit 8 is set unless
// `force`). Defined in xlinkEmit.cpp.
xlink2::HandleELink searchAndEmitELink(act::Actor* actor, const char* name);
xlink2::HandleSLink searchAndEmitSLink(act::Actor* actor, const char* name, bool force);
/// 0x710105ddb8 (declaration only): searchAndEmit(name, handle) on the actor's SLink user instance (XLink::_50),
/// unless `handle` is null or XLink::_cc bit 1 is set.
void sub_710105DDB8(act::Actor* actor, const char* name, xlink2::HandleSLink* handle);
/// 0x710105e030 (declaration only; lane2 s21): sets property `idx` of the actor's SLink user instance (XLink::_50);
/// false if the actor has none.
bool sub_710105E030(act::Actor* actor, u32 idx, s32 value);
/// 0x710105df6c (declaration only; lane2 s21): forwards (name, a, false, b) to the 0x1232fb4 emit routine of the
/// actor's XLink (`actor->_568`); nothing if the actor has none.
void sub_710105DF6C(act::Actor* actor, const char* name, bool a, bool b);

}  // namespace ksys::eft
