#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiMessageString.h"
#include "Game/UI/uiUtils.h"
#include <nn/ui2d/Pane.h>

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

void Unk_7102477fc0::m9() {
    if (_10 || !_18 || !(_18->_3c & 1) || !_8)
        return;
    auto* pane = _8->mPane;
    if (pane->GetParent())
        return;
    if (_20)
        _20->AppendChild(pane);
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

bool Unk_7102477fc0::m14() const {
    return false;
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

}  // namespace uking::ui
