#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkTiny.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiMessageMgr.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking::ui {

// Native 0x7100a28824 initializes the 13 rows at 0x71025f0290 and binds
// count 13 / pointer at 0x71025f0678 / 0x71025f0680. Each record is 0x30 bytes.
struct OptionDefinition {
    sead::SafeString flag;
    s32 type;
    s32 setting;
    s32 title;
    s32 choiceBegin;
    s32 choiceEnd;
    s32 checkedText;
    s32 uncheckedText;
};
static_assert(sizeof(OptionDefinition) == 0x30);
static OptionDefinition sUnk_71025f0290[] = {
    {"BalloonTextOnOff", 0, 0, 18, -1, -1, -1, -1},
    {"CameraUpDownReverse", 0, 1, 19, -1, -1, -1, -1},
    {"CameraRLReverse", 0, 2, 20, -1, -1, -1, -1},
    {"JumpButtonChange", 0, 3, 21, -1, -1, -1, -1},
    {"GyroOnOff", 0, 4, 22, -1, -1, -1, -1},
    {"TextRubyOnOff", 0, 5, 23, -1, -1, -1, -1},
    {"MiniMapDirection", 0, 6, 24, -1, -1, -1, -1},
    {"StickSensitivity", 1, 8, 25, 10, 14, -1, -1},
    {"MainScreenOnOff", 1, 7, 27, 29, 30, -1, -1},
    {"AmiiboItemOnOff", 2, 9, 26, -1, -1, 16, 15},
    {"TextWindowChange", 1, 17, 28, 31, 33, -1, -1},
    {"VoiceLanguage", 2, 46, 34, -1, -1, 35, 35},
    {"VoiceLanguage", 1, 46, 34, 36, 45, -1, -1},
};
static sead::Buffer<OptionDefinition> sUnk_71025f0678(sUnk_71025f0290);
static sead::SafeString sUnk_71025f0668 = "LayoutMsg/OptionWindow_00";

// 0x7100a2a570
// NON_MATCHING: native global block addressing and branch scheduling differ.
void Unk_OptionWindowEntry::sub_7100A2A570(bool notify) {
    const auto& option = sUnk_71025f0678[_50];
    if (option.type == 2) {
        if (_28) {
            const bool disabled = _50 == 9 ? _64 && _0->_36bd : _50 == 11 || _64;
            _28->ForceSetChecked(!disabled);
            auto* layout = _28->mLayout;
            const sead::SafeString pane("T_Text_00");
            if (!layout)
                return;
            const s32 id = disabled ? option.checkedText : option.uncheckedText;
            sead::FixedSafeString<256> label;
            label.format("%04d", id);
            eui::MessageString text;
            getMessage(sUnk_71025f0668, label, &text);
            setWidgetString(layout, pane, text);
        }
    } else if (option.type == 1) {
        if (_20) {
            auto* layout = _20->mLayout;
            const sead::SafeString pane("T_Text_00");
            if (layout) {
                sead::FixedSafeString<256> label;
                label.format("%04d", _58 + option.choiceBegin);
                eui::MessageString text;
                getMessage(sUnk_71025f0668, label, &text);
                setWidgetString(layout, pane, text);
            }
            sub_7100A2B91C(notify);
        }
    } else if (option.type == 0 && _18) {
        _18->ForceSetChecked(_54);
    }
}

// 0x7100a2b91c
// NON_MATCHING: native global block addressing and branch scheduling differ.
void Unk_OptionWindowEntry::sub_7100A2B91C(bool notify) {
    if (sUnk_71025f0678[_50].type != 1)
        return;
    if (_58 >= _5c) {
        if (_38 && _38->mFrame != 0) {
            if (notify)
                _38->StopAtMin();
            else
                _38->PlayAuto(-1);
        }
        if (_48 && _48->mFrame != _48->GetFrameSize()) {
            if (notify)
                _48->StopAtMax();
            else
                _48->PlayAuto(1);
        }
    } else {
        if (_60 < _58) {
            if (_38 && _38->mFrame != 0) {
                if (notify)
                    _38->StopAtMin();
                else
                    _38->PlayAuto(-1);
            }
        } else if (_38 && _38->mFrame != _38->GetFrameSize()) {
            if (notify)
                _38->StopAtMax();
            else
                _38->PlayAuto(1);
        }
        if (_48 && _48->mFrame != 0) {
            if (notify)
                _48->StopAtMin();
            else
                _48->PlayAuto(-1);
        }
    }
    if (_0) {
        if (_0->_36a8 == 2) {
            if (_40)
                _40->PlayAuto(1);
        } else if (_0->_36a8 == 1) {
            if (_30)
                _30->PlayAuto(1);
        }
    }
}

// NON_MATCHING: native global block addressing and branch scheduling differ.
// 0x7100a2a450: reads the current flag value and numeric limits for this entry.
void Unk_OptionWindowEntry::sub_7100A2A450() {
    const auto& option = sUnk_71025f0678[_50];
    if (option.type == 2) {
        if (_68 == ksys::gdt::FlagType::Bool)
            _64 = ksys::gdt::getBoolByKey(option.flag);
    } else if (option.type == 1) {
        if (_68 == ksys::gdt::FlagType::Bool) {
            _58 = ksys::gdt::getBoolByKey(option.flag);
            _5c = 1;
            _60 = 0;
        } else if (_68 == ksys::gdt::FlagType::S32) {
            _58 = ksys::gdt::getS32ByKey(option.flag);
            ksys::gdt::Manager::instance()->getParam().get1().getBuffer()->getMaxValueForS32(
                    &_5c, option.flag);
            ksys::gdt::Manager::instance()->getParam().get1().getBuffer()->getMinValueForS32(
                    &_60, option.flag);
        }
    } else if (option.type == 0 && _68 == ksys::gdt::FlagType::Bool) {
        _54 = ksys::gdt::getBoolByKey(option.flag);
        _58 = _54;
        _5c = 1;
        _60 = 0;
    }
}

// NON_MATCHING: native global block addressing and branch scheduling differ.
// 0x7100a29900: sets the label and control kind, then loads and presents its flag value.
void Unk_OptionWindowEntry::sub_7100A29900() {
    const auto& option = sUnk_71025f0678[_50];
    const s32 title = option.title;
    auto* layout = _10;
    const sead::SafeString pane("T_Option_00");
    if (layout) {
        sead::FixedSafeString<256> label;
        label.format("%04d", title);
        eui::MessageString text;
        getMessage(sUnk_71025f0668, label, &text);
        setWidgetString(layout, pane, text);
    }
    sub_7100A2B76C(option.type);
    _68 = ksys::gdt::Manager::instance()->getParam().get1().getBuffer()->getFlagType(option.flag);
    sub_7100A2A450();
    sub_7100A2A570(true);
}

}  // namespace uking::ui
