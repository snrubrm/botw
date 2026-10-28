#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUtils.h"
#include <prim/seadSafeString.h>

namespace uking::ui {

// NoBtn group of the original TU at 0x9fb828: the album's discard flow calls sub_71009FB970 out of
// line, so the method needs its own translation unit here.

// 0x71009fb930
void ScreenAppSystemWindowNoBtn::sub_71009FB930() {
    if (!_3610 || _3610->mRate != 0)
        return;
    _3610->PlayAuto(1.0f);
}

// 0x71009fb958
void ScreenAppSystemWindowNoBtn::sub_71009FB958() {
    _3618 = 1;
    open(2);
}

// 0x71009fb970
void ScreenAppSystemWindowNoBtn::sub_71009FB970() {
    _3618 = 2;
    open(2);
}

// 0x71009fb988
void ScreenAppSystemWindowNoBtn::m93(sead::Heap*) {
    _3610 = mLayout->createAnimatorAuto("FadeOut", false);
}

namespace {
// 0x7102483440: message set, label and text widget of ScreenAppSystemWindowNoBtn::m98
const sead::SafeString sAppSystemWindowNoBtnText[] = {
    sead::SafeString(sead::SafeString::ConstInitTag{}, "LayoutMsg/AppSystemWindowNoBtn_00"),
    sead::SafeString(sead::SafeString::ConstInitTag{}, "0002"),
    sead::SafeString(sead::SafeString::ConstInitTag{}, "T_Text_00")};
}  // namespace

namespace {
// 0x7102482ea0 / 0x7102483420: the sensor state message labels, in UiSubsys1::get38a8 order
const sead::SafeString sSensorStateLabelNames[] = {"0000", "0001", "0003"};
const sead::SafeString* const sSensorStateLabels[] = {&sSensorStateLabelNames[1], &sSensorStateLabelNames[0],
                                                      &sSensorStateLabelNames[2]};
}  // namespace

// 0x71009fb9bc
void ScreenAppSystemWindowNoBtn::m94() {
    if ((_291 & 2) || isOpened() ||
        (_3610 && _3610->mFrame == static_cast<f32>(_3610->GetFrameSize())))
        _292 |= 0x20;
}

// 0x71009fba20
// NON_MATCHING: GlobalMerge places the text array 0x20 into a merged constant block (the original addresses it directly)
void ScreenAppSystemWindowNoBtn::m98() {
    switch (_3618) {
    case 1:
        sub_71009FBADC();
        break;
    case 2: {
        eui::MessageString message;
        if (getMessage(sAppSystemWindowNoBtnText[0], sAppSystemWindowNoBtnText[1], &message))
            setWidgetString(mLayout, sAppSystemWindowNoBtnText[2], sead::SafeString::cEmptyString);
        else
            setWidgetString(mLayout, sAppSystemWindowNoBtnText[2], message);
        break;
    }
    default:
        setWidgetString(mLayout, sAppSystemWindowNoBtnText[2], sead::SafeString::cEmptyString);
        break;
    }
}

// 0x71009fbadc
void ScreenAppSystemWindowNoBtn::sub_71009FBADC() {
    const s32 state = UiSubsys1::instance()->get38a8();
    eui::MessageString message;
    if (u32(state) <= 2 &&
        !getMessage(sAppSystemWindowNoBtnText[0], *sSensorStateLabels[state], &message)) {
        if (state == 2)
            invokeSoundLink2Event_("mc_SensorOff");
        else
            invokeSoundLink2Event_("mc_SensorOn");
        setWidgetString(mLayout, sAppSystemWindowNoBtnText[2], message);
    } else {
        setWidgetString(mLayout, sAppSystemWindowNoBtnText[2], sead::SafeString::cEmptyString);
    }
}

}  // namespace uking::ui
