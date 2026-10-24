#include "Game/UI/uiScreens.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiUtils.h"
#include <math/seadVector.h>

namespace uking::ui {

// 0x71009af944
Unk_710247a028::Unk_710247a028(eui::LayoutEx* layout)
    : ScreenChildEx(layout), _130(-1), _134(), mButtons(), _c78() {
    _c78.fill(-1);
}

// 0x71009afcf4
void Unk_710247a028::m24(sead::Heap* heap) {
    _cc8.sub_7100A814D8(heap, 0, mButtons.size(), "uiPage20_00PAScreen");
}

// 0x71009afe58
void Unk_710247a028::m25() {
    _cc8.sub_7100A816D8();
}

// 0x71009afe60
void Unk_710247a028::m21() {
    for (s32 i = 0; i < mButtons.size(); ++i)
        _cc8.unload(i);
}

// 0x71009b01b4
sead::Vector2f Unk_710247a028::sub_71009B01B4() const {
    const auto& position = mLayout->mPane->GetPosition();
    return {position.x, position.y};
}

// 0x71009b01c4
void Unk_710247a028::sub_71009B01C4(f32 x) {
    auto* pane = mLayout->mPane;
    nn::util::Float3 position = pane->GetPosition();
    position.x = x;
    position.z = 0.0f;
    pane->SetPosition(position);
}

// 0x71009aff68
void Unk_710247a028::sub_71009AFF68() {
    _130 = -1;
}

// 0x71009b01e4
void Unk_710247a028::sub_71009B01E4(f32 dx) {
    auto* pane = mLayout->mPane;
    nn::util::Float3 position = pane->GetPosition();
    position.x += dx;
    position.z = 0.0f;
    pane->SetPosition(position);
}

// 0x71009b020c
void Unk_710247a028::sub_71009B020C(bool visible) {
    mLayout->mPane->SetVisible(visible);
}

// 0x71009b014c
void Unk_710247a028::sub_71009B014C(s32 index, s32 value) {
    sub_71009AFF74(index, value);
    mButtons[index].sub_710098993C(true, false);
}

// 0x71009b0190
void Unk_710247a028::sub_71009B0190(s32 index, bool a2) {
    if (a2)
        mButtons[index].sub_710098923C();
    else
        mButtons[index].sub_71009892B0();
}

// 0x71009aff74
void Unk_710247a028::sub_71009AFF74(s32 index, s32 value) {
    auto* mgr = PauseMenuDataMgr::instance();
    if (!mgr)
        return;
    const PouchItem* item = mgr->__auto8(_130, value);
    if (!item || !item->isInInventory()) {
        sub_71009B00E0(index);
        return;
    }
    _c78[index] = value;
    mButtons[index].sub_710098931C(item);
    mButtons[index].sub_710098993C(false, false);
    if (sub_7100AA45CC(item->getName())) {
        _cc8.unload(index);
        return;
    }
    sead::FixedSafeString<128> path;
    sub_7100AA3EA0(item, &path);
    _cc8.sub_7100A81B1C(path, index);
}

// 0x71009b0348
void Unk_710247a028::sub_71009B0348() {
    auto* mgr = PauseMenuDataMgr::instance();
    if (!mgr)
        return;
    if (sub_7100A82D08(_130) == PouchCategory::Bow && sub_7100AA7BAC(nullptr)) {
        for (s32 i = 0; i < mButtons.size(); ++i) {
            if (_c78[i] == -1)
                continue;
            const PouchItem* item = mgr->__auto8(_130, _c78[i]);
            if (!item)
                continue;
            const auto type = item->getType();
            const bool equipped = type == PouchItemType::Arrow || type == PouchItemType::KeyItem ?
                                      false :
                                      item->isEquipped();
            mButtons[i].sub_7100989888(equipped, true);
        }
    } else {
        for (s32 i = 0; i < mButtons.size(); ++i) {
            if (_c78[i] == -1)
                continue;
            const PouchItem* item = mgr->__auto8(_130, _c78[i]);
            if (!item)
                continue;
            const bool equipped =
                item->getType() == PouchItemType::KeyItem ? false : item->isEquipped();
            mButtons[i].sub_7100989888(equipped, true);
        }
    }
}

// 0x71009b00e0
void Unk_710247a028::sub_71009B00E0(s32 index) {
    _c78[index] = -1;
    mButtons[index].sub_71009896D8();
    mButtons[index].sub_710098993C(true, false);
    _cc8.unload(index);
}

// 0x71009b0224
void Unk_710247a028::sub_71009B0224(bool enabled) {
    if (_130 == -1)
        return;
    for (auto& button : mButtons.mBuffer)
        button.sub_7100989968(enabled);
}

// 0x71009b0468
s32 Unk_710247a028::sub_71009B0468(s32 index) const {
    if (index < _134 || index >= _134 + 20)
        return -1;
    return index - _134;
}

// 0x71009b0484
s32 Unk_710247a028::sub_71009B0484(s32 index) const {
    if (index < _134 || index >= _134 + 20)
        return -1;
    return _c78[index - _134];
}

// 0x71009b04bc
void Unk_710247a028::sub_71009B04BC(s32 index, bool flag) {
    mButtons[index].sub_710098993C(flag, false);
}

// 0x71009b04e0
void Unk_710247a028::sub_71009B04E0(s32 index, bool flag) {
    mButtons[index].sub_7100989888(flag, true);
}


}  // namespace uking::ui
