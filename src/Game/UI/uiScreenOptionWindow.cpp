#include "Game/UI/uiManager.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include <algorithm>
#include "Game/UI/euiButton.h"
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

// 0x7100a2bb7c
// NON_MATCHING: native global-block addressing and flag branch scheduling differ.
void Unk_OptionWindowEntry::sub_7100A2BB7C() {
    const auto& option = sUnk_71025f0678[_50];
    if (option.type == 2) {
        if (_68 == ksys::gdt::FlagType::Bool)
            ksys::gdt::setBoolByKey(_64, option.flag);
    } else if (option.type == 1) {
        if (_68 == ksys::gdt::FlagType::Bool)
            ksys::gdt::setBoolByKey(_58 > 0, option.flag);
        else if (_68 == ksys::gdt::FlagType::S32)
            ksys::gdt::setS32ByKey(_58, option.flag);
    } else if (option.type == 0 && _68 == ksys::gdt::FlagType::Bool) {
        ksys::gdt::setBoolByKey(_54, option.flag);
    }
}

// 0x7100a2b0fc
// NON_MATCHING: native global-block addressing and value-clamp branch scheduling differ.
void Unk_OptionWindowEntry::sub_7100A2B0FC() {
    const auto& option = sUnk_71025f0678[_50];
    if (option.type == 1) {
        if (_0) {
            if (_0->_36a8 == 2)
                ++_58;
            else if (_0->_36a8 == 1)
                --_58;
        }
        _58 = std::clamp(_58, _60, _5c);
    } else if (option.type == 0 && _0) {
        if (_0->_36a8 == 2) {
            _58 = std::clamp(_58 - 1, _60, _5c);
            _54 = _58 != 0;
        } else if (_0->_36a8 == 1) {
            _58 = std::clamp(_58 + 1, _60, _5c);
            _54 = _58 != 0;
        } else if (_0->_36a8 == 0) {
            _54 = !_54;
            _58 = _54 ? _5c : _60;
        }
    }
    if (_50 == 11) {
        createAndLoadScreenIfNeededImpl(ScreenId::SystemWindow00, nullptr);
        if (auto* screen = sead::DynamicCast<ScreenSystemWindow00>(
                    eui::ScreenMgr::instance()->getScreen(ScreenId::SystemWindow00))) {
            screen->m154(11, 0, nullptr);
            if (_0) {
                _0->mButtonGroup->_38 &= ~2;
                _0->_36be &= ~u8(1);
            }
        }
    } else if (_50 == 9) {
        createAndLoadScreenIfNeededImpl(ScreenId::AmiiboWindow, nullptr);
        if (auto* screen = sead::DynamicCast<ScreenAmiiboWindow>(
                    eui::ScreenMgr::instance()->getScreen(ScreenId::AmiiboWindow))) {
            if (_0 && _0->_36bc) {
                s32 type = 0;
                if (_0->_36bd)
                    type = ksys::gdt::getFlag_AmiiboItemOnOff() ? 2 : 1;
                screen->m154(type, false);
                _0->mButtonGroup->_38 &= ~2;
            }
        }
    }
    sub_7100A2BB7C();
    sub_7100A2A570(false);
}

// inline-only in the original; name is a guess. The same type-to-button selection
// appears in A2AD94, A2AF14 and A2B040, as well as the option update callbacks.
static inline eui::AnimButton* getOptionButtonMaybe(const Unk_OptionWindowEntry& entry) {
    switch (sUnk_71025f0678[entry._50].type) {
    case 0:
        return entry._18;
    case 1:
        return entry._20;
    case 2:
        return entry._28;
    default:
        return nullptr;
    }
}

// 0x7100a2a310
// NON_MATCHING: native mode-specific traversal and flag dispatch scheduling differ.
void ScreenOptionWindow::sub_7100A2A310() {
    if (_3698.size() == 0)
        return;
    const bool reset_all = Manager::instance()->_64c38 == 8;
    for (s32 i = 0; i < _3698.size(); ++i) {
        auto* entry = _3698(i);
        if (!reset_all && u32(entry->_50 - 11) <= 1)
            continue;
        const auto& option = sUnk_71025f0678[entry->_50];
        if (entry->_68 == ksys::gdt::FlagType::Bool)
            ksys::gdt::Manager::instance()->resetBool_(option.flag);
        else if (entry->_68 == ksys::gdt::FlagType::S32)
            ksys::gdt::Manager::instance()->resetS32_(option.flag);
    }
}

// 0x7100a2aab8
// NON_MATCHING: native global addressing and message temporaries differ.
void Unk_OptionWindowEntry::sub_7100A2AAB8() {
    const s32 id = sUnk_71025f0678[_50].setting;
    const sead::SafeString pane("T_Caption_00");
    if (_8) {
        sead::FixedSafeString<256> label;
        label.format("%04d", id);
        eui::MessageString message;
        getMessage(sUnk_71025f0668, label, &message);
        setWidgetString(_8, pane, message);
    }
}

// 0x7100a2ad94
// NON_MATCHING: native entry traversal and inlined button selection differ.
void ScreenOptionWindow::m102(eui::AnimButton* button) {
    for (s32 i = 0; i < _3698.size(); ++i) {
        auto* entry = _3698(i);
        if (!entry || getOptionButtonMaybe(*entry) != button)
            continue;
        entry = _3698(i);
        const s32 type = sUnk_71025f0678[entry->_50].type;
        if (auto* selected = getOptionButtonMaybe(*entry)) {
            if ((type | 1) == 1)
                selected->mFlags &= ~4;
            else
                selected->mFlags |= 4;
        }
        entry->sub_7100A2AAB8();
        entry->_70.sub_7100937DA4(false);
        _36b0 = _3698(i);
        return;
    }
}

// 0x7100a2af14
// NON_MATCHING: native entry traversal and inlined button selection differ.
void ScreenOptionWindow::m104(eui::AnimButton* button) {
    for (s32 i = 0; i < _3698.size(); ++i) {
        auto* entry = _3698(i);
        if (!entry || getOptionButtonMaybe(*entry) != button)
            continue;
        entry = _3698(i);
        const s32 type = sUnk_71025f0678[entry->_50].type;
        if (auto* selected = getOptionButtonMaybe(*entry)) {
            if ((type | 1) == 1)
                selected->mFlags &= ~4;
            else
                selected->mFlags |= 4;
        }
        return;
    }
}

// 0x7100a2b040
// NON_MATCHING: native entry traversal and inlined button selection differ.
void ScreenOptionWindow::m106(eui::AnimButton* button) {
    for (s32 i = 0; i < _3698.size(); ++i) {
        auto* entry = _3698(i);
        if (entry && getOptionButtonMaybe(*entry) == button) {
            _3698(i)->sub_7100A2B0FC();
            return;
        }
    }
}

// 0x7100a2b458
// NON_MATCHING: native entry traversal and inlined button selection differ.
void ScreenOptionWindow::m107(eui::AnimButton* button) {
    for (s32 i = 0; i < _3698.size(); ++i) {
        auto* entry = _3698(i);
        if (!entry || getOptionButtonMaybe(*entry) != button)
            continue;
        entry = _3698(i);
        if (sUnk_71025f0678[entry->_50].type == 1 && entry->_20)
            entry->_20->mFlags &= ~4;
        return;
    }
}

}  // namespace uking::ui
