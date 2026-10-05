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
    // 0x71010a6e48: source owner inferred from the passed UI receiver.
    void closeMessageTipsScreen();
    // 0x71010a5cac / 0x71010a6f04: get-item dialog query and close.
    bool sub_71010A5CAC();
    void sub_71010A6F04();
    // 0x71010a7118: declared only; updates the placed-item stock count and choice mode.
    void setPlacedItemStockNum(bool choice_mode, s32 stock);
    // 0x71010a719c / 0x71010a71a8: scalar defaults queried by the game tag processor.
    f32 sub_71010A719C() const;
    f32 sub_71010A71A8() const;
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
    // 0x71010a5c68 / 0x71010a5cfc / 0x71010a5db0 / 0x71010a5e64 (CSV unnamed, declared only): polled by
    // the Open* dialog / title actions' calc_ (each returns true when its screen has finished).
    bool sub_71010A5C68();
    bool sub_71010A5CFC();
    bool sub_71010A5DB0();
    bool sub_71010A5E64();
    // 0x71010a6454 (CSV unnamed): called by Message3DText with its message set / message label.
    bool sub_71010A6454(const sead::SafeString& message_set, const sead::SafeString& label,
                        ksys::act::Actor* actor, f32 time, bool flag);
};

}  // namespace uking::ui
