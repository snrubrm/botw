#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiMessageString.h"
#include "Game/UI/euiMassDrawPane.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameHorseMgr.h"
#include "Game/gameWolfLinkMgr.h"
#include "Game/Actor/actHorseBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include <nn/ui2d/Pane.h>
#include "Game/gameUnkRttiPlaceholders.h"

namespace uking::ui {

Unk_7102477fc0::~Unk_7102477fc0() {
    _8 = nullptr;
    _10 = nullptr;
    _18 = nullptr;
    _20 = nullptr;
    _28 = 33;
    _2c = false;
}

void Unk_7102477fc0::m4() {
    m9();
    if (_18)
        _18->m8();
    m7();
    m8();
    if (_18 && _18->sub_7100951048()) {
        if (auto* entry = sead::DynamicCast<Unk_71024754c0>(_18)) {
            if (entry->_50)
                entry->_50->m4();
        }
    }
}

void Unk_7102477fc0::m5() {
    m13();
    if (_18)
        _18->m8();
    m10();
    m11();
    if (_18 && _18->sub_7100951048()) {
        if (auto* entry = sead::DynamicCast<Unk_71024754c0>(_18)) {
            if (entry->_50)
                entry->_50->m5();
        }
    }
    m12();
}

void Unk_7102477fc0::m6(eui::LayoutEx* layout) {
    _8 = layout;
    if (layout) {
        _20 = layout->mPane->GetParent();
        if (_20)
            _20->RemoveChild(layout->mPane);
    }
}

// NON_MATCHING: pane lookup precedes the position load in the layout path.
void Unk_7102477fc0::m7() {
    if (_10) {
        if (_18 && _18->_40 >= 0 && (_18->_3c & 1))
            _10->_250[_18->_40] = {_18->_34.x / _10->GetScale().x,
                                  _18->_34.y / _10->GetScale().y};
    } else if (_18 && (_18->_3c & 1) && _8) {
        _8->mPane->SetPosition(nn::util::Float3{_18->_34.x, _18->_34.y, 0.0f});
    }
}

void Unk_7102477fc0::m8() {
    if (_10) {
        if (_18) {
            const s32 index = _18->_40;
            if (index >= 0) {
                if (_18->_3c & 1) {
                    _10->_230[index] = 255;
                    _2c = true;
                    if (_18->_3c & 0x100) {
                        _10->_230[index] = 0;
                        _18->_3c &= ~0x100;
                    }
                } else {
                    _10->_230[index] = 0;
                    _2c = false;
                }
            }
        } else {
            _2c = false;
        }
        if (_18 && (_18->_3c & 1)) {
            auto* pane = _10;
            if (pane) {
                const s32 index = _18->_40;
                if (index >= 0)
                    pane->_240[index] = m14();
            }
        }
        return;
    }
    if (!_8)
        return;
    if (_18 && (_18->_3c & 1)) {
        _8->sub_7100BDDE7C(false, 1, true);
        if (_18->_3c & 0x100) {
            _8->mPane->Hide();
            _18->_3c &= ~0x100;
        }
    } else {
        _8->startAnimCloseImpl_(false, true);
    }
}

// NON_MATCHING: pane lookup precedes the position load in the layout path.
void Unk_7102477fc0::m10() {
    if (_10) {
        if (_18 && _18->_40 >= 0 && (_18->_3c & 0x4001) == 0x4001)
            _10->_250[_18->_40] = {_18->_34.x / _10->GetScale().x,
                                  _18->_34.y / _10->GetScale().y};
    } else if (_18 && (_18->_3c & 0x4001) == 0x4001 && _8) {
        _8->mPane->SetPosition(nn::util::Float3{_18->_34.x, _18->_34.y, 0.0f});
    }
}

void Unk_7102477fc0::m9() {
    if (_10 || !_18 || !(_18->_3c & 1) || !_8)
        return;
    auto* pane = _8->mPane;
    if (pane->GetParent())
        return;
    if (_20)
        _20->AppendChild(pane);
}

// 0x710098cb98
// NON_MATCHING: block layout and the shared visible-store tail differ.
void Unk_7102477fc0::sub_710098CB98(bool force) {
    if (!_10)
        return;
    if (!_18) {
        if (force)
            _2c = false;
        return;
    }
    const s32 index = _18->_40;
    if (index < 0)
        return;
    const u32 flags = _18->_3c;
    if (force) {
        u8& alpha = _10->_230[index];
        if (flags & 1) {
            alpha = 255;
            _2c = true;
            if (_18->_3c & 0x100) {
                _10->_230[index] = 0;
                _18->_3c &= ~0x100;
            }
            return;
        }
        alpha = 0;
    } else {
        if (flags & 1) {
            if ((flags & 0x30) != 0x20) {
                if ((flags & 0x30) != 0x30 && (flags & 3) != 3)
                    return;
                u8& alpha = _10->_230[index];
                alpha = 255;
                _2c = true;
                if (_18->_3c & 0x100) {
                    _10->_230[index] = 0;
                    _18->_3c &= ~0x100;
                }
                return;
            }
        } else if ((flags & 3) != 2) {
            return;
        }
        _10->_230[index] = 0;
    }
    _2c = false;
}

// 0x710098cd5c
// NON_MATCHING: the flag tests are emitted in a different order (the original keeps the source order 0x30, 3, 0x4000
// via mvn and tests 0x20 before 0x30 in the layout path).
void Unk_7102477fc0::m11() {
    if (_10) {
        sub_710098CB98(false);
        if (_18 && (_18->_3c & 1) &&
            ((_18->_3c & 0x30) == 0x30 || (_18->_3c & 3) == 3 || (_18->_3c & 0x4000))) {
            auto* pane = _10;
            if (pane) {
                const s32 index = _18->_40;
                if (index >= 0)
                    pane->_240[index] = m14();
            }
        }
        return;
    }
    if (!_18 || !_8)
        return;
    const u32 flags = _18->_3c;
    if (!(flags & 1)) {
        if ((flags & 3) == 2)
            _8->startAnimCloseImpl_(false, true);
        return;
    }
    if ((flags & 0x30) == 0x20) {
        _8->startAnimCloseImpl_(false, false);
        return;
    }
    s32 mode;
    if ((flags & 0x30) == 0x30)
        mode = 0;
    else if ((flags & 3) == 3)
        mode = 1;
    else
        return;
    _8->sub_7100BDDE7C(false, mode, true);
    if (_18->_3c & 0x100) {
        _8->mPane->Hide();
        _18->_3c &= ~0x100;
    }
}

void Unk_7102477fc0::m12() {
    if (!_18 || ((_18->_3c & 0x41) != 0x40 && (_18->_3c & 5) != 4))
        return;
    if (auto* entry = UiSubsys1::instance()->findListEntry(_18))
        UiSubsys1::instance()->freeListEntry(entry);
    _18->m22();
}

void Unk_7102477fc0::m13() {
    if (_10 || !_18 || (_18->_3c & 3) != 3 || !_8)
        return;
    auto* pane = _8->mPane;
    if (pane->GetParent())
        return;
    if (_20)
        _20->AppendChild(pane);
}

s32 Unk_7102477fc0::m14() const {
    return 0;
}

void Unk_7102477fc0::sub_710098CF9C() {
    if (_8 && _8->mPane->GetParent() && _20)
        _20->RemoveChild(_8->mPane);
}

Unk_71024783b0::~Unk_71024783b0() {
    _30 = {0.0f, 0.0f};
}

void Unk_71024783b0::m4() {
    m9();
    m7();
    m8();
}

void Unk_71024783b0::m5() {
    m13();
    m10();
    m11();
    m12();
}

void Unk_71024783b0::m7() {
    if (_18 && (_18->_3c & 1) && _8)
        _8->mPane->SetPosition(nn::util::Float3{_18->_34.x + _30.x, _18->_34.y + _30.y, 0.0f});
}

// NON_MATCHING: the two singleton tests merge their layout reload paths differently.
void Unk_71024783b0::m8() {
    if (!_8)
        return;
    if (!_18 || !(_18->_3c & 1)) {
        _8->startAnimCloseImpl_(false, true);
        return;
    }
    if (!UiSubsys1::instance()->is848Zero() && !UiSubsys1::instance()->is898Zero())
        _8->sub_7100BDDE7C(false, 1, true);
    else
        _8->startAnimCloseImpl_(false, true);
    sub_710098D2B0();
}

void Unk_71024783b0::m9() {
    if (!_18 || !(_18->_3c & 1) || UiSubsys1::instance()->is848Zero() ||
        UiSubsys1::instance()->is898Zero() || !_8)
        return;
    auto* pane = _8->mPane;
    if (!pane->GetParent() && _20)
        _20->AppendChild(pane);
}

void Unk_71024783b0::m10() {
    if (_18 && (_18->_3c & 0x4001) == 0x4001 && _8)
        _8->mPane->SetPosition(nn::util::Float3{_18->_34.x + _30.x, _18->_34.y + _30.y, 0.0f});
}

void Unk_71024783b0::m13() {
    if (!_18 || (_18->_3c & 3) != 3 || !_8)
        return;
    auto* pane = _8->mPane;
    if (!pane->GetParent() && _20)
        _20->AppendChild(pane);
}

void Unk_71024783b0::sub_710098D2B0() {
    if (auto* entry = sead::DynamicCast<Unk_71024754c0>(_18)) {
        eui::MessageString message;
        getLocationMarker(entry->_58->_8, &message);
        setWidgetString(_8, "T_Name_00", message);
    }
}

Unk_71025d9170::~Unk_71025d9170() {
    _30 = nullptr;
    _38 = nullptr;
    _40 = nullptr;
}

void Unk_71025d9170::m8() {
    Unk_7102477fc0::m8();
}

void Unk_71025d9170::m11() {
    Unk_7102477fc0::m11();
}

void Unk_71025d9170::m15() {}

void Unk_71025d9170::m16() {}

Unk_7102478428::~Unk_7102478428() = default;

// NON_MATCHING: frame selection uses conditional selects instead of native branches.
void Unk_7102478428::m8() {
    Unk_7102477fc0::m8();
    if (!_18 || !(_18->_3c & 1))
        return;
    if (auto* entry = sead::DynamicCast<Unk_71024755d8>(_18)) {
        if (_40)
            _40->Stop((entry->_3c & 0x80000) ? 2.0f : (entry->_3c & 0x20000) ? 1.0f : 0.0f);
    }
}

// NON_MATCHING: combined flag tests and frame selection are if-converted.
void Unk_7102478428::m11() {
    Unk_7102477fc0::m11();
    if (!(_18->_3c & 1) ||
        (!(_18->_3c & 0x4000) && (_18->_3c & 3) != 3 && (_18->_3c & 0x30) != 0x30))
        return;
    if (auto* entry = sead::DynamicCast<Unk_71024755d8>(_18)) {
        if (_40)
            _40->Stop((entry->_3c & 0x80000) ? 2.0f : (entry->_3c & 0x20000) ? 1.0f : 0.0f);
    }
}

Unk_7102478ec8::~Unk_7102478ec8() = default;

void Unk_7102478ec8::m8() {
    Unk_7102477fc0::m8();
}

void Unk_7102478ec8::m11() {
    Unk_7102477fc0::m11();
}

Unk_71024784c0::~Unk_71024784c0() = default;

// 0x710098d7c4
void Unk_71024784c0::m8() {
    Unk_7102477fc0::m8();
    if (!_18 || !(_18->_3c & 1))
        return;
    if (auto* entry = sead::DynamicCast<Unk_71024756f0>(_18)) {
        if (auto* animator = _40) {
            if (entry->_3c & 0x80000)
                animator->Stop(2.0f);
            else if (entry->_3c & 0x20000)
                animator->Stop(1.0f);
            else
                animator->Stop(0.0f);
        }
    }
}

// 0x710098d898
// NON_MATCHING: the flag tests are if-converted into a ccmp chain here.
void Unk_71024784c0::m11() {
    Unk_7102477fc0::m11();
    if ((_18->_3c & 1) && ((_18->_3c & 0x4000) || (_18->_3c & 3) == 3 || (_18->_3c & 0x30) == 0x30)) {
        if (auto* entry = sead::DynamicCast<Unk_71024756f0>(_18)) {
            if (auto* animator = _40) {
                if (entry->_3c & 0x80000)
                    animator->Stop(2.0f);
                else if (entry->_3c & 0x20000)
                    animator->Stop(1.0f);
                else
                    animator->Stop(0.0f);
            }
        }
    }
}

Unk_7102478558::~Unk_7102478558() = default;

// 0x710098d988
void Unk_7102478558::m8() {
    Unk_7102477fc0::m8();
    if (!_18 || !(_18->_3c & 1))
        return;
    if (auto* entry = sead::DynamicCast<Unk_7102475808>(_18)) {
        if (auto* animator = _40) {
            if (entry->_3c & 0x200)
                animator->Stop(2.0f);
            else
                animator->Stop(0.0f);
        }
    }
}

// 0x710098da48
// NON_MATCHING: the flag tests are if-converted into a ccmp chain here.
void Unk_7102478558::m11() {
    Unk_7102477fc0::m11();
    if ((_18->_3c & 1) && ((_18->_3c & 0x4000) || (_18->_3c & 3) == 3 || (_18->_3c & 0x30) == 0x30)) {
        if (auto* entry = sead::DynamicCast<Unk_7102475808>(_18)) {
            if (auto* animator = _40) {
                if (entry->_3c & 0x200)
                    animator->Stop(2.0f);
                else
                    animator->Stop(0.0f);
            }
        }
    }
}

Unk_71024785f0::~Unk_71024785f0() = default;

// 0x710098db24
void Unk_71024785f0::m8() {
    Unk_7102477fc0::m8();
    if (!_18 || !(_18->_3c & 1))
        return;
    if (auto* entry = sead::DynamicCast<Unk_7102475920>(_18)) {
        if (auto* animator = _40) {
            if (entry->_3c & 0x20000)
                animator->Stop(2.0f);
            else
                animator->Stop(0.0f);
        }
    }
}

// 0x710098dbe4
// NON_MATCHING: the flag tests are if-converted into a ccmp chain here.
void Unk_71024785f0::m11() {
    Unk_7102477fc0::m11();
    if ((_18->_3c & 1) && ((_18->_3c & 0x4000) || (_18->_3c & 3) == 3 || (_18->_3c & 0x30) == 0x30)) {
        if (auto* entry = sead::DynamicCast<Unk_7102475920>(_18)) {
            if (auto* animator = _40) {
                if (entry->_3c & 0x20000)
                    animator->Stop(2.0f);
                else
                    animator->Stop(0.0f);
            }
        }
    }
}

Unk_7102478688::~Unk_7102478688() = default;

// 0x710098dcc0
void Unk_7102478688::m8() {
    Unk_7102477fc0::m8();
    if (!_18 || !(_18->_3c & 1))
        return;
    if (auto* entry = sead::DynamicCast<Unk_7102475a38>(_18)) {
        if (auto* animator = _40) {
            if (entry->_3c & 0x80000)
                animator->Stop(2.0f);
            else if (entry->_3c & 0x20000)
                animator->Stop(1.0f);
            else
                animator->Stop(0.0f);
        }
    }
}

// 0x710098dd94
// NON_MATCHING: the flag tests are if-converted into a ccmp chain here.
void Unk_7102478688::m11() {
    Unk_7102477fc0::m11();
    if ((_18->_3c & 1) && ((_18->_3c & 0x4000) || (_18->_3c & 3) == 3 || (_18->_3c & 0x30) == 0x30)) {
        if (auto* entry = sead::DynamicCast<Unk_7102475a38>(_18)) {
            if (auto* animator = _40) {
                if (entry->_3c & 0x80000)
                    animator->Stop(2.0f);
                else if (entry->_3c & 0x20000)
                    animator->Stop(1.0f);
                else
                    animator->Stop(0.0f);
            }
        }
    }
}

Unk_7102478720::~Unk_7102478720() = default;

// 0x710098de84
void Unk_7102478720::m8() {
    Unk_7102477fc0::m8();
    if (!_18 || !(_18->_3c & 1))
        return;
    if (auto* entry = sead::DynamicCast<Unk_7102475a38>(_18)) {
        if (auto* animator = _40) {
            if (entry->_3c & 0x80000)
                animator->Stop(2.0f);
            else if (entry->_3c & 0x20000)
                animator->Stop(1.0f);
            else
                animator->Stop(0.0f);
        }
    }
}

// 0x710098df58
// NON_MATCHING: the flag tests are if-converted into a ccmp chain here.
void Unk_7102478720::m11() {
    Unk_7102477fc0::m11();
    if ((_18->_3c & 1) && ((_18->_3c & 0x4000) || (_18->_3c & 3) == 3 || (_18->_3c & 0x30) == 0x30)) {
        if (auto* entry = sead::DynamicCast<Unk_7102475a38>(_18)) {
            if (auto* animator = _40) {
                if (entry->_3c & 0x80000)
                    animator->Stop(2.0f);
                else if (entry->_3c & 0x20000)
                    animator->Stop(1.0f);
                else
                    animator->Stop(0.0f);
            }
        }
    }
}

Unk_71024787b8::~Unk_71024787b8() = default;

// 0x710098e048
void Unk_71024787b8::m8() {
    Unk_7102477fc0::m8();
    if (!_18 || !(_18->_3c & 1))
        return;
    if (auto* entry = sead::DynamicCast<Unk_7102475a38>(_18)) {
        if (auto* animator = _40) {
            if (entry->_3c & 0x80000)
                animator->Stop(2.0f);
            else if (entry->_3c & 0x20000)
                animator->Stop(1.0f);
            else
                animator->Stop(0.0f);
        }
    }
}

// 0x710098e11c
// NON_MATCHING: the flag tests are if-converted into a ccmp chain here.
void Unk_71024787b8::m11() {
    Unk_7102477fc0::m11();
    if ((_18->_3c & 1) && ((_18->_3c & 0x4000) || (_18->_3c & 3) == 3 || (_18->_3c & 0x30) == 0x30)) {
        if (auto* entry = sead::DynamicCast<Unk_7102475a38>(_18)) {
            if (auto* animator = _40) {
                if (entry->_3c & 0x80000)
                    animator->Stop(2.0f);
                else if (entry->_3c & 0x20000)
                    animator->Stop(1.0f);
                else
                    animator->Stop(0.0f);
            }
        }
    }
}

Unk_7102478850::~Unk_7102478850() = default;

// 0x710098e20c
void Unk_7102478850::m8() {
    Unk_7102477fc0::m8();
    if (!_18 || !(_18->_3c & 1))
        return;
    if (auto* entry = sead::DynamicCast<Unk_7102475a38>(_18)) {
        if (auto* animator = _40) {
            if (entry->_3c & 0x80000)
                animator->Stop(2.0f);
            else if (entry->_3c & 0x20000)
                animator->Stop(1.0f);
            else
                animator->Stop(0.0f);
        }
    }
}

// 0x710098e2e0
// NON_MATCHING: the flag tests are if-converted into a ccmp chain here.
void Unk_7102478850::m11() {
    Unk_7102477fc0::m11();
    if ((_18->_3c & 1) && ((_18->_3c & 0x4000) || (_18->_3c & 3) == 3 || (_18->_3c & 0x30) == 0x30)) {
        if (auto* entry = sead::DynamicCast<Unk_7102475a38>(_18)) {
            if (auto* animator = _40) {
                if (entry->_3c & 0x80000)
                    animator->Stop(2.0f);
                else if (entry->_3c & 0x20000)
                    animator->Stop(1.0f);
                else
                    animator->Stop(0.0f);
            }
        }
    }
}

Unk_71024788e8::~Unk_71024788e8() = default;

// 0x710098e3d0
void Unk_71024788e8::m8() {
    Unk_7102477fc0::m8();
    if (!_18 || !(_18->_3c & 1))
        return;
    if (auto* entry = sead::DynamicCast<Unk_7102475b50>(_18)) {
        if (auto* animator = _40) {
            if (entry->_3c & 0x20000)
                animator->Stop(2.0f);
            else
                animator->Stop(0.0f);
        }
    }
}

// 0x710098e490
// NON_MATCHING: the flag tests are if-converted into a ccmp chain here.
void Unk_71024788e8::m11() {
    Unk_7102477fc0::m11();
    if ((_18->_3c & 1) && ((_18->_3c & 0x4000) || (_18->_3c & 3) == 3 || (_18->_3c & 0x30) == 0x30)) {
        if (auto* entry = sead::DynamicCast<Unk_7102475b50>(_18)) {
            if (auto* animator = _40) {
                if (entry->_3c & 0x20000)
                    animator->Stop(2.0f);
                else
                    animator->Stop(0.0f);
            }
        }
    }
}

Unk_7102478980::~Unk_7102478980() = default;

void Unk_7102478980::m12() {
    if (!_10 || _2c || !_18 || !_18->_8 || _18->_40 < 0 || _10->_230[_18->_40] != 0)
        return;
    if (auto* entry = UiSubsys1::instance()->findListEntry(_18))
        UiSubsys1::instance()->freeListEntry(entry);
    _18->m24(false);
    _18->m22();
}

Unk_7102478d98::~Unk_7102478d98() = default;

// 0x710098f7ec
void Unk_7102478d98::m12() {
    if (!_10 || _2c || !_18 || !_18->_8)
        return;
    const s32 index = _18->_40;
    if (index < 0 || _10->_230[index] != 0)
        return;
    if (auto* entry = sead::DynamicCast<Unk_7102476738>(_18)) {
        if (auto* found = UiSubsys1::instance()->sub_7100958FCC(entry))
            UiSubsys1::instance()->sub_710095900C(found);
    }
    _18->m24(false);
    _18->m22();
}

// NON_MATCHING: native spills an enum conversion; the entry kind is still declared as an integer.
s32 Unk_7102478d98::m14() const {
    return _18->_1c - 27;
}

Unk_7102478a18::~Unk_7102478a18() {
    _48 = nullptr;
}

Unk_7102478ab0::~Unk_7102478ab0() {
    _48 = nullptr;
}

Unk_7102478b48::~Unk_7102478b48() {
    _48 = nullptr;
}

// 0x710098e6c0
void Unk_7102478ab0::m11() {
    Unk_7102477fc0::m11();
    if (!_18 || !(_18->_3c & 1))
        return;
    auto* entry = sead::DynamicCast<Unk_7102475e68>(_18);
    if (!entry)
        return;
    if (entry->_7c == 0)
        _48->Stop(0.0f);
    else if (entry->_7c == 1)
        _48->Stop(1.0f);
}

// NON_MATCHING: the animator receiver loads before the predicate call, and frame selection uses conditional selects.
void Unk_7102478a18::m11() {
    Unk_7102477fc0::m11();
    if (!_18 || !(_18->_3c & 1) || !HorseMgr::instance())
        return;
    auto& link = HorseMgr::instance()->mOwnedHorse;
    if (!link.hasProc())
        return;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    _48->Stop(uking::act::sub_7100E6ED04(accessor) ? 1.0f : 0.0f);
}

// NON_MATCHING: the animator receiver loads before the predicate call, and frame selection uses conditional selects.
void Unk_7102478b48::m11() {
    Unk_7102477fc0::m11();
    if (!_18 || !(_18->_3c & 1) || !WolfLinkMgr::instance())
        return;
    _48->Stop(WolfLinkMgr::instance()->sub_7100682CB4() ? 1.0f : 0.0f);
}

Unk_7102478be0::~Unk_7102478be0() {
    _30 = nullptr;
}

void Unk_7102478be0::m8() {
    Unk_7102477fc0::m8();
    if (_18 && (_18->_3c & 1)) {
        setMapMarkerAncientText();
        sub_710098EAB8();
    }
}

Unk_7102478e30::~Unk_7102478e30() {
    _48 = nullptr;
    _50 = nullptr;
}

// NON_MATCHING: native spills an enum conversion; the entry kind is still declared as an integer.
void Unk_7102478e30::m8() {
    Unk_7102477fc0::m8();
    if (_18 && (_18->_3c & 1) && _48)
        _48->Stop(_18->_1c - 37);
}

Unk_7102478c68::~Unk_7102478c68() = default;

void Unk_7102478c68::m6(eui::LayoutEx* layout) {
    if (layout) {
        _48 = layout->mPane->FindPaneByName("N_PlayerRotate_00", true);
        _50 = layout->mPane->FindPaneByName("P_Light_00", true);
    }
    Unk_7102477fc0::m6(layout);
}

Unk_7102478d00::~Unk_7102478d00() {
    _48 = nullptr;
}

void Unk_7102478d00::m12() {
    if (_18 && ((_18->_3c & 0x41) == 0x40 || (_18->_3c & 5) == 4)) {
        if (auto* entry = sead::DynamicCast<Unk_7102476640>(_18)) {
            if (auto* item = UiSubsys1::instance()->sub_71009580A4(entry))
                UiSubsys1::instance()->sub_71009580E4(item);
        }
        _18->m22();
    }
}

void Unk_7102478d00::m13() {
    if (_18 && _8) {
        auto* pane = _8->mPane;
        if (!pane->GetParent() && _20)
            _20->AppendChild(pane);
    }
}

Unk_7102479050::~Unk_7102479050() = default;

Unk_71024790e8::~Unk_71024790e8() = default;

Unk_7102479180::~Unk_7102479180() = default;

Unk_7102479218::~Unk_7102479218() = default;

Unk_71024792b0::~Unk_71024792b0() = default;

Unk_7102479348::~Unk_7102479348() = default;

Unk_71024793e0::~Unk_71024793e0() = default;

Unk_7102479478::~Unk_7102479478() = default;

Unk_7102479510::~Unk_7102479510() = default;

}  // namespace uking::ui

Unk_71024795a8::~Unk_71024795a8() = default;

Unk_7102479640::~Unk_7102479640() = default;

Unk_71024796d8::~Unk_71024796d8() = default;

Unk_7102479770::~Unk_7102479770() = default;
