#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
}

namespace uking::ui {

// The UI singleton (CSV: UI::createInstance 0x71010a5714, size 0xb0; sInstance 0x710261ebc0).
// The layout is incomplete (only the methods that callers need are declared) and the namespace is
// a guess (neighbouring ui:: functions live in uking::ui).
class UI {
    SEAD_SINGLETON_DISPOSER(UI)
    UI() = default;

public:
    // 0x71010a5b0c (CSV unnamed): called by NpcTebaRoot::calc_ with its actor.
    bool sub_71010A5B0C(ksys::act::Actor* actor);
    // 0x71010a6ccc (CSV: UI::x_0)
    void x_0(bool flag);
    // 0x71010a6bec (CSV unnamed)
    void sub_71010A6BEC(ksys::act::Actor* actor, bool flag);
    // 0x71010a5888 (CSV unnamed): whether the message dialog screen exists and is not closed.
    bool sub_71010A5888();
    // 0x71010a5f18 (CSV messageDialogViewStyleStuff): opens the message dialog screen (the style is
    // picked by `actor`'s tags and `flag1`); `time` is stored in the screen, `close_option` and
    // `flag2` are stored at 0x718 / 0x76c. Returns true if the dialog was opened.
    bool messageDialogViewStyleStuff(const sead::SafeString& message_set,
                                     const sead::SafeString& label, ksys::act::Actor* actor,
                                     f32 time, s32 close_option, bool flag1, bool flag2);
    // 0x71010a6b98 (CSV UI::__auto1): closes the message dialog if it belongs to `actor` (or if
    // `actor` is null).
    void sub_71010A6B98(ksys::act::Actor* actor);
    // 0x71010a6454 (CSV unnamed): called by Message3DText with its message set / message label.
    bool sub_71010A6454(const sead::SafeString& message_set, const sead::SafeString& label,
                        ksys::act::Actor* actor, f32 time, bool flag);
};

}  // namespace uking::ui
