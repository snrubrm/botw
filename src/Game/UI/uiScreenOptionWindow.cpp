#include "Game/UI/uiManager.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include <algorithm>
#include "Game/UI/euiButton.h"
#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/gameStageBinder.h"
#include "Game/UI/euiPartsEx.h"
#include "Game/gameSaveSystem.h"
#include <devenv/seadEnvUtil.h>
#include <new>
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
// Native A28824 binds the 12 displayed option IDs at 2491298.
static const s32 sUnk_7102491298[] = {9, 1, 2, 7, 4, 3, 6, 8, 5, 10, 11, 12};
static sead::Buffer<const s32> sUnk_71025f0688(sUnk_7102491298);

// 0x7100a2b53c
Unk_OptionWindowEntry::Unk_OptionWindowEntry(ScreenOptionWindow* screen, eui::LayoutEx* caption,
                                           eui::LayoutEx* layout, s32 index)
    : _0(screen), _8(caption), _10(layout), _18(nullptr), _20(nullptr), _28(nullptr),
      _30(nullptr), _38(nullptr), _40(nullptr), _48(nullptr), _50(index), _54(false),
      _58(-1), _5c(-1), _60(-1), _64(false), _68(ksys::gdt::FlagType::Invalid) {
    if (!_10)
        return;
    if (auto* parts = _10->findPartsLayout("Pa_Btn_00"))
        _18 = nn::font::DynamicCast<eui::UniteButton>(_0->sub_7100A4810C(parts));
    if (auto* parts = _10->findPartsLayout("Pa_Btn_01")) {
        _20 = nn::font::DynamicCast<eui::UniteButton>(_0->sub_7100A4810C(parts));
        if (_20) {
            if (auto* arrow = _20->mLayout->findPartsLayout("Pa_ArrowL_00")) {
                _30 = arrow->tryCreateAnimatorAuto("Decide", true);
                _38 = arrow->tryCreateAnimatorAuto("Invalid", true);
            }
            if (auto* arrow = _20->mLayout->findPartsLayout("Pa_ArrowR_00")) {
                _40 = arrow->tryCreateAnimatorAuto("Decide", true);
                _48 = arrow->tryCreateAnimatorAuto("Invalid", true);
            }
        }
    }
    if (auto* parts = _10->findPartsLayout("Pa_Btn_02"))
        _28 = nn::font::DynamicCast<eui::UniteButton>(_0->sub_7100A4810C(parts));
    _70._10 = _10->GetPane();
}

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

// 0x7100a2905c
// NON_MATCHING: RTTI branch scheduling and message temporaries differ.
void Unk_OptionWindowEntry::setEnabledMaybe(bool enabled) {
    auto* button = getOptionButtonMaybe(*this);
    if (!button)
        return;
    button->PlayDisableAnim(!enabled);
    if (_50 == 4) {
        auto* check = nn::font::DynamicCast<eui::UniteButton>(button);
        if (!check)
            return;
        check->ForceSetChecked(enabled ? _54 : false);
        if (!enabled)
            check->mFlags &= ~4;
        return;
    }
    if (_50 != 10)
        return;
    auto* layout = button->mLayout;
    const sead::SafeString pane("T_Text_00");
    if (layout) {
        const s32 value = enabled ? _58 : _5c;
        const s32 first = sUnk_71025f0678[10].choiceBegin;
        sead::FixedSafeString<256> label;
        label.format("%04d", value + first);
        eui::MessageString text;
        getMessage(sUnk_71025f0668, label, &text);
        setWidgetString(layout, pane, text);
    }
    sub_7100A2B91C(false);
}

// 0x7100a2936c
// NON_MATCHING: mode-specific option filtering and layout creation use different registers.
void ScreenOptionWindow::m92(sead::Heap* heap) {
    const s32 count = sUnk_71025f0688.size();
    if (count < 1)
        return;
    _3698.allocBuffer(count, heap);
    auto* parts = eui::sub_7100945088(sub_7100A48104("Pa_SlideBtn_00", nullptr));
    if (!parts)
        return;
    const auto language = sead::EnvUtil::getRegionLanguage();
    for (s32 i = count - 1; i > 0; --i) {
        const s32 id = sUnk_71025f0688[i];
        if (language != sead::RegionLanguageID::JPja && id == 5)
            continue;
        if (id == 11 || id == 12) {
            if ((id == 12) != (Manager::instance()->_64c38 == 8))
                continue;
            if (isE3DemoMode())
                continue;
            if (auto* save = SaveSystem::instance(); save && save->_1a44)
                continue;
        }
        sead::FormatFixedSafeString<64> name("Pa_SlideBtn_%02d", i);
        // PartsEx owns an eui layout, as in the existing pick-up and map layout-copy callers.
        auto* layout = sub_7100A47A5C(heap, 1,
            static_cast<eui::LayoutEx*>(parts->mPartsLayoutLink.layout), name, parts, true, true);
        if (layout) {
            if (auto* entry = new (heap) Unk_OptionWindowEntry(this, mLayout, layout,
                                                              sUnk_71025f0688[i]))
                _3698.insert(0, entry);
        }
    }
    _3698.insert(0, new (heap) Unk_OptionWindowEntry(
        this, mLayout, static_cast<eui::LayoutEx*>(parts->mPartsLayoutLink.layout),
        sUnk_71025f0688[0]));
}

// 0x7100a29710
// NON_MATCHING: checked entry traversal and scroll-parameter temporaries differ.
void ScreenOptionWindow::m93(sead::Heap* heap) {
    if (Manager::instance()->_64c38 == 8)
        _36bc = sub_7100AA88A4(&_36bd);
    else {
        _36bd = checkIsGetRune(7, 0);
        _36bc = true;
    }
    const s32 count = _3698.size();
    for (s32 i = 0; i < count; ++i)
        _3698[i]->sub_7100A29900();
    Unk_7102474df8_Params params;
    params.corner1.set(0.0f, 0.0f);
    params.corner2.set(0.0f, 0.0f);
    params.count = sUnk_71025f0688.size();
    if (auto* pane = static_cast<nn::ui2d::Pane*>(sub_7100A48328("N_SlideArea_00", nullptr))) {
        sead::Vector2f bottom_left, top_left, top_right, bottom_right;
        getPaneCorners(pane, &bottom_left, &top_left, &top_right, &bottom_right);
        params.corner1.x = bottom_left.x < top_right.x ? bottom_left.x : top_right.x;
        params.corner2.x = bottom_left.x < top_right.x ? top_right.x : bottom_left.x;
        params.corner1.y = bottom_left.y < top_right.y ? bottom_left.y : top_right.y;
        params.corner2.y = bottom_left.y < top_right.y ? top_right.y : bottom_left.y;
    }
    const Unk_7102474df8_Speeds speeds;
    _3610.sub_7100937FA4(heap, this, &params, &speeds);
    for (s32 i = 0, n = _3698.size(); i < n; ++i)
        _3610.sub_7100938408(&_3698(i)->_70);
    _36c0 = new (heap) Settings;
    _36be = 0;
    _36e8 = 0;
}

// 0x7100a2a80c
// NON_MATCHING: entry searches and button-flag traversal use different registers.
void ScreenOptionWindow::m98() {
    mActiveCursorNode = nullptr;
    for (s32 i = 0, count = _3698.size(); i < count; ++i) {
        if (_3698(i)->_50 != sUnk_71025f0688[0])
            continue;
        if (auto* entry = _3698[i]) {
            if (auto* button = getOptionButtonMaybe(*entry))
                setReservedBoxCursorNode(findBoxCursorNodeByButton(button));
            entry->sub_7100A2AAB8();
        }
        break;
    }
    for (s32 i = 0, count = _3698.size(); i < count; ++i) {
        if (_3698(i)->_50 != 4)
            continue;
        if (auto* entry = _3698[i])
            entry->setEnabledMaybe(true);
        break;
    }
    const bool text_enabled = sub_7100A94A80();
    for (s32 i = 0, count = _3698.size(); i < count; ++i) {
        if (_3698(i)->_50 != 10)
            continue;
        if (auto* entry = _3698[i])
            entry->setEnabledMaybe(text_enabled);
        break;
    }
    // Native A2A9E0 calls the Settings constructor on the existing snapshot storage.
    if (_36c0)
        new (_36c0) Settings;
    for (s32 i = 0; i < _3698.size(); ++i) {
        auto* entry = _3698[i];
        if (!entry)
            continue;
        const s32 type = sUnk_71025f0678[entry->_50].type;
        if (auto* button = getOptionButtonMaybe(*entry)) {
            if ((type | 1) == 1)
                button->mFlags &= ~4;
            else
                button->mFlags |= 4;
        }
    }
}

// 0x7100a29a4c
// NON_MATCHING: dialog return paths, input tests and option traversal use different registers.
void ScreenOptionWindow::m94() {
    _3610.sub_7100938090(getAnimationStep_());
    if (!_36bc) {
        if (Manager::instance()->_64c38 == 8)
            _36bc = sub_7100AA88A4(&_36bd);
        else {
            _36bd = checkIsGetRune(7, 0);
            _36bc = true;
        }
    }
    s32 dialog = 99;
    if (eui::ScreenMgr::instance()->getScreen(ScreenId::AmiiboWindow))
        dialog = ScreenId::AmiiboWindow;
    else if (eui::ScreenMgr::instance()->getScreen(ScreenId::SystemWindow00))
        dialog = ScreenId::SystemWindow00;
    if ((_36be & 4) == 0) {
        if (dialog != 99) {
            _36b8 = dialog;
            _36a8 = 3;
            if (dialog != ScreenId::SystemWindow00)
                return;
            auto* screen = sead::DynamicCast<ScreenSystemWindow00>(
                eui::ScreenMgr::instance()->getScreen(ScreenId::SystemWindow00));
            if ((_36be & 1) == 0) {
                if (!screen || sub_7100A64304() != 0)
                    return;
                createTitleStageBinder(true, true);
                _36be |= 2;
            } else {
                if (!screen || (screen->_291 & 4) == 0 || sub_7100A64304() != 0)
                    return;
                sub_7100A2A310();
            }
            return;
        }
        if ((_36e8.load() & 1) != 0) {
            if ((_36e8.load() & 2) == 0)
                return;
            showLoadSaveIcon(false);
            close(-1);
            return;
        }
        if (_36b8 != 99) {
            if (_36b8 == ScreenId::SystemWindow00) {
                if ((_36be & 1) != 0 && _3698.size() != 0) {
                    for (s32 i = 0, count = _3698.size(); i < count; ++i) {
                        _3698(i)->sub_7100A2A450();
                        auto* button = getOptionButtonMaybe(*_3698(i));
                        if (!button || !button->IsPlayDisableAnim())
                            _3698(i)->sub_7100A2A570(false);
                    }
                }
                _36b8 = 99;
            } else if (_36b8 == ScreenId::AmiiboWindow) {
                const s32 count = _3698.size();
                for (s32 i = 0; i < count; ++i) {
                    if (_3698(i)->_50 != 9)
                        continue;
                    if (auto* entry = _3698[i]) {
                        entry->sub_7100A2A450();
                        entry->sub_7100A2A570(false);
                    }
                    break;
                }
            }
            if ((_36be & 2) == 0)
                mButtonGroup->_38 |= 2;
        }
    } else {
        _36be &= ~u8(4);
        mButtonGroup->_38 |= 2;
    }
    if (!isOpened())
        return;
    _36a8 = 3;
    if (mActiveCursorNode) {
        if (_36b0 && mActiveCursorNode->mButton == getOptionButtonMaybe(*_36b0)) {
            bool press = false;
            if (isTrigMaybe(1)) {
                _36a8 = 0;
                press = sUnk_71025f0678[_36b0->_50].type == 0;
            } else if (isTrigMaybe(0x440000) ||
                       ((_292 & 0x40) && sub_71010AA9D0() && mUIController &&
                        mUIController->isRepeat(0x440000))) {
                _36a8 = 1;
                const s32 type = sUnk_71025f0678[_36b0->_50].type;
                if (type == 0)
                    press = _36b0->_58 < _36b0->_5c;
                else if (type == 1)
                    press = _36b0->_60 < _36b0->_58;
            } else if (isTrigMaybe(0x880000) ||
                       ((_292 & 0x40) && sub_71010AA9D0() && mUIController &&
                        mUIController->isRepeat(0x880000))) {
                _36a8 = 2;
                const s32 type = sUnk_71025f0678[_36b0->_50].type;
                if (type == 0)
                    press = _36b0->_60 < _36b0->_58;
                else if (type == 1)
                    press = _36b0->_58 < _36b0->_5c;
            }
            if (press) {
                if (auto* button = getOptionButtonMaybe(*_36b0)) {
                    if (!button->IsPlayDisableAnim()) {
                        button->mFlags |= 4;
                        button->Down();
                    }
                }
            }
        }
        if (_36a8 != 3)
            return;
    }
    if ((mButtonGroup->_38 & 2) == 0)
        return;
    if (isTrigMaybe(0x10)) {
        invokeSoundLink2Event_("mc_SetDefault");
        createAndLoadScreenIfNeededImpl(ScreenId::SystemWindow00, nullptr);
        if (auto* screen = sead::DynamicCast<ScreenSystemWindow00>(
                eui::ScreenMgr::instance()->getScreen(ScreenId::SystemWindow00))) {
            screen->m154(8, 0, nullptr);
            _36be |= 1;
        }
        mButtonGroup->_38 &= ~2;
    } else if (isTrigMaybe(2) && (_36be & 2) == 0) {
        sub_71010AA894();
        mButtonGroup->_38 &= ~2;
        if (!ksys::snd::SoundMgr::instance()->_60->sub_7101058B74(&_36c8)) {
            close(-1);
            return;
        }
        showLoadSaveIcon(true);
        _36e8 |= 1;
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
