#include "Game/UI/euiTraceGaugeControl.h"
#include "Game/UI/uiScreenControlCreators.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiAlignPane.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkTiny.h"
#include "Game/UI/uiScreenChildStates.h"
#include <container/seadBuffer.h>
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/gameSaveSystem.h"
#include <gfx/seadGraphics.h>
#include "Game/UI/euiPartsEx.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtEvent.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

// Small leaf screen methods (named after their CSV address).
namespace uking::ui {

PouchCategory sub_7100A82D08(s32 tab);

// NON_MATCHING: the compiler outlines the SafeArray member constructor.
Unk_7100A341D0::Unk_7100A341D0() = default;
// NON_MATCHING: the compiler outlines the SafeArray member destructor.
Unk_7100A341D0::~Unk_7100A341D0() = default;

// NON_MATCHING: the loop induction variable is widened in category comparisons.
void ScreenPauseMenu::sub_7100A379BC(s32 tab) {
    mSelectedCategory = s32(sub_7100A82D08(tab));
    for (s32 i = 0; i < mTabControls.mEntries.size(); ++i) {
        auto& entry = mTabControls.mEntries[i];
        entry.mButton.sub_7100988060(entry.mFirstItemIndex < 0);
        entry.mButton.sub_710098802C(i == mSelectedCategory);
        entry.mPage.sub_7100936A28(sub_7100A82DB8(i));
        if (i == mSelectedCategory)
            entry.mPage.sub_7100936A7C(tab - entry.mFirstItemIndex);
        else
            entry.mPage.sub_7100936AD8();
    }
}

// 0x7100a34a04
void ScreenPauseMenu::sub_7100A34A04() {
    _3bb4 = 1;
}

// 0x7100a38994
void ScreenPauseMenu::adjstBoxCursor(sead::BoundBox2<f32>* box, const eui::BoxCursorNode*) const {
    if (!_3674)
        return;
    if (_3664.isUndef())
        return;
    if (_3664.isInside(box->getMin()) && _3664.isInside(box->getMax()))
        return;
    if (auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::BoxCursorTV))
        screen->close(-4);
}

// 0x71025f1220: first button tag of each of the three pause menu pages (set up by the TU initialiser 0x7100a3324c)
static s32 sUnk_7102493538[] = {9, 29, 49};
static sead::Buffer<s32> sUnk_71025f1220(sUnk_7102493538);

// 0x7100a3a7fc
// NON_MATCHING: the original reaches sUnk_71025f1220 through the TU's merged globals and keeps the page index
// in a separate 64-bit register for the element address
bool ScreenPauseMenu::sub_7100A3A7FC(s32 page, s32 offset) {
    s32 i = 0;
    for (; i < 3; ++i) {
        if (_3a00[i] && _3a00[i]->_130 == page)
            break;
    }
    if (i == 3)
        return false;
    const s32 tag = sUnk_71025f1220[i] + offset;
    if (tag == 0)
        return false;
    if (getStateMachine().getState()->getId() == (&sUnk_71025f0cf0)->getId()) {
        moveBoxCursorByTag_(tag);
        if (auto* button = mButtonGroup->FindButtonByTag(tag))
            button->setFlag10(true);
    } else {
        _3b80 = tag;
    }
    return true;
}

// 0x71009b01b4
sead::Vector2f ScreenPauseMenuUnk3a00::sub_71009B01B4() const {
    const auto& position = mLayout->mPane->GetPosition();
    return {position.x, position.y};
}

// 0x71009b01c4
void ScreenPauseMenuUnk3a00::sub_71009B01C4(f32 x) {
    auto* pane = mLayout->mPane;
    nn::util::Float3 position = pane->GetPosition();
    position.x = x;
    position.z = 0.0f;
    pane->SetPosition(position);
}

// 0x71009aff68
void ScreenPauseMenuUnk3a00::sub_71009AFF68() {
    _130 = -1;
}

// 0x71009b01e4
void ScreenPauseMenuUnk3a00::sub_71009B01E4(f32 dx) {
    auto* pane = mLayout->mPane;
    nn::util::Float3 position = pane->GetPosition();
    position.x += dx;
    position.z = 0.0f;
    pane->SetPosition(position);
}

// 0x71009b020c
void ScreenPauseMenuUnk3a00::sub_71009B020C(bool visible) {
    mLayout->mPane->SetVisible(visible);
}

// 0x71009b0190
void ScreenPauseMenuUnk3a00::sub_71009B0190(s32 index, bool a2) {
    if (a2)
        mButtons[index].sub_710098923C();
    else
        mButtons[index].sub_71009892B0();
}

// 0x71009b00e0
void ScreenPauseMenuUnk3a00::sub_71009B00E0(s32 index) {
    _c78[index] = -1;
    mButtons[index].sub_71009896D8();
    mButtons[index].sub_710098993C(true, false);
    _cc8.unload(index);
}

// 0x71009b0224
void ScreenPauseMenuUnk3a00::sub_71009B0224(bool enabled) {
    if (_130 == -1)
        return;
    for (auto& button : mButtons.mBuffer)
        button.sub_7100989968(enabled);
    for (s32 i = 0; i < mButtons.size(); ++i)
        mButtons[i].sub_7100989968(enabled);
}

// 0x71009b0468
s32 ScreenPauseMenuUnk3a00::sub_71009B0468(s32 index) const {
    if (index < _134 || index >= _134 + 20)
        return -1;
    return index - _134;
    if (_134 <= index && index < _134 + 20)
        return index - _134;
    return -1;
}

// 0x71009b0484
s32 ScreenPauseMenuUnk3a00::sub_71009B0484(s32 index) const {
    if (index < _134 || index >= _134 + 20)
        return -1;
    return _c78[index - _134];
}

// 0x71009b04bc
void ScreenPauseMenuUnk3a00::sub_71009B04BC(s32 index, bool flag) {
    mButtons[index].sub_710098993C(flag, false);
}

// 0x71009b04e0
void ScreenPauseMenuUnk3a00::sub_71009B04E0(s32 index, bool flag) {
    mButtons[index].sub_7100989888(flag, true);
    if (_134 <= index && index < _134 + 20)
        return _c78[index - _134];
    return -1;
}

// 0x71009b0618
ScreenChildEx::ScreenChildEx(eui::LayoutEx* layout) : ScreenChild(layout) {
    _128 = nullptr;
}

ScreenChildEx* ScreenChildEx::sub_71009B064C(s32 group, s32 index) {
    return nn::font::DynamicCast<ScreenChildEx>(_128->getChild(group, index));
}

void ScreenChildEx::m54(sead::Heap* heap) {
    _128 = sead::DynamicCast<ScreenEx>(mLayout->mScreen);
    ScreenChild::m54(heap);
}

// 0x71009b0c24
void Unk_710247a6d8::sub_71009B0C24(eui::TraceGaugeControl* gauge) {
    _150 = gauge;
    if (gauge)
        gauge->_6c = false;
}

// 0x71009b0eec
void Unk_710247a6d8::sub_71009B0EEC(u32 frame) {
    if (_130)
        _130->Stop(f32(frame));
    if (frame != 2)
        _1d8.sub_71009C697C();
}

// 0x71009b1024
// NON_MATCHING: Unk_710247ade8::sub_71009B26A0 is defined in this file and gets inlined
void Unk_710247a6d8::sub_71009B1024() {
    _158.sub_71009B26A0();
}

// 0x71009b10ec
void Unk_710247a6d8::sub_71009B10EC(s32 value) {
    if (_150) {
        f32 ratio = 0.0f;
        sub_7100AA8FCC(&ratio, f32(value), 120.0f);
        _150->setTracingSpeed(ratio);
        _150->set50(ratio);
    }
    _190.sub_71009B2010();
}

// 0x71009c20f0
void Unk_710247ca18::sub_71009C20F0(eui::TraceGaugeControl* gauge) {
    _170 = gauge;
    if (gauge)
        gauge->_6c = false;
}

// 0x71009c28d0
void Unk_710247ca18::sub_71009C28D0() {
    if (_130 && _130->mFrame != 0.0f)
        _130->StopAtMin();
    if (_138)
        _138->Stop(0.0f);
}

// 0x71009b0f3c
void Unk_710247a6d8::sub_71009B0F3C(bool on) {
    if (!_138)
        return;
    if (on)
        _138->StopAtMax();
    else
        _138->StopAtMin();
}

// 0x71009b0f60
void Unk_710247a6d8::sub_71009B0F60(bool on) {
    if (!_140)
        return;
    if (on) {
        _140->StopAtMin();
        return;
    }
    _140->StopAtMax();
    if (_130)
        _130->Stop(0.0f);
    _1d8.sub_71009C697C();
}

// 0x71009b0818
// NON_MATCHING: the ScreenChildEx constructor above is inlined here; the original calls it
Unk_710247a6d8::Unk_710247a6d8(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

// 0x71009b1a6c
Unk_710247ada8::Unk_710247ada8() = default;

// 0x71009b1a90
Unk_710247ada8::~Unk_710247ada8() {
    if (_30) {
        delete[] _30;
        _30 = nullptr;
        _28 = 0;
    }
}

// 0x71009b24c4
Unk_710247ade8::Unk_710247ade8() = default;

// 0x71009b24e4
Unk_710247ade8::~Unk_710247ade8() = default;

// 0x71009b26a0
void Unk_710247ade8::sub_71009B26A0() {
    if (_10)
        _10->StopAtMin();
}

// 0x71009b5fc8
void ScreenPauseMenuUnk3b98::sub_71009B5FC8(bool active) {
    if (active) {
        // Pointer virtual form retains the original state descriptor getId call.
        if (mStateMachine.getState()->getId() != (&sUnk_710261ee00)->getId())
            return;
        mStateMachine.changeState(&sUnk_71025d98a0);
    } else {
        mStateMachine.changeState(&sUnk_710261ee00);
    }
}

// 0x71009b9f94
bool ScreenPauseMenuUnk3b90::sub_71009B9F94(bool active) {
    if (active) {
        // Pointer virtual form retains the original state descriptor getId call.
        if (mStateMachine.getState()->getId() != (&sUnk_710261ee00)->getId())
            return false;
        mStateMachine.changeState(&sUnk_71025d9e00);
    } else {
        mStateMachine.changeState(&sUnk_710261ee00);
    }
    return true;
}

bool sub_7100AA8DD4();

struct CommandInfo {
    s32 command;
    s32 state;
    sead::SafeString animation;
};

static CommandInfo sUnk_71025ED5B8[] = {
    {66, 2, ""},
    {68, 16, ""},
    {17, 1, ""},
    {38, 10, "mc_DoDefault"},
    {22, 6, ""},
    {21, 7, ""},
    {26, 6, ""},
    {27, 8, ""},
    {28, 24, ""},
    {29, 25, ""},
    {16, 3, "mc_DoDefault"},
    {36, 9, ""},
    {18, 4, "mc_DoDefault"},
    {39, 11, "mc_DoDefault"},
    {11, 12, ""},
    {9, 0, ""},
    {42, 11, "mc_DoDefault"},
    {43, 11, "mc_DoDefault"},
    {25, 8, ""},
    {44, 13, "mc_DoDefault"},
    {45, 14, ""},
    {47, 15, "mc_DoDefault"},
    {48, 15, ""},
    {49, 17, ""},
    {50, 17, ""},
    {51, 4, "mc_DoDefault"},
    {52, 18, "mc_DoDefault"},
    {78, 19, ""},
    {56, 20, "mc_DoDefault"},
    {53, 22, ""},
    {54, 22, ""},
    {55, 22, ""},
    {41, 23, "mc_DoDefault"},
    {57, 24, ""},
    {58, 25, "mc_DoDefault"},
    {14, 26, ""},
    {40, 27, "mc_DoDefault"},
    {79, 28, ""},
    {80, 29, ""},
    {81, 30, ""},
    {82, 31, ""},
    {15, 32, ""},
    {60, 33, ""},
    {59, 34, ""},
    {83, 35, ""},
    {61, 36, "mc_DoDefault"},
    {62, 37, ""},
    {63, 38, ""},
    {24, 39, ""},
    {23, 40, ""},
    {30, 40, ""},
    {19, 41, "mc_DoDefault"},
    {46, 42, ""},
    {84, 43, ""},
    {64, 44, "mc_DoDefault"},
    {65, 45, ""},
    {85, 46, ""},
    {86, 47, "mc_DoDefault"},
};
static sead::Buffer<CommandInfo> sUnk_71025ED468(sUnk_71025ED5B8);

// NON_MATCHING: independent Buffer offsets and table iteration differ.
bool ScreenDoCommand::setCommand(s32 command) {
    if (sub_7100AA8F10() && command != 14)
        return false;
    if (_3658 != -1)
        return false;
    for (const auto& entry : sUnk_71025ED468) {
        if (entry.command == command) {
            if (entry.state == -1)
                return false;
            _3658 = entry.state;
            return true;
        }
    }
    return false;
}


// 0x7100a0772c
void ScreenDoCommand::sub_7100A0772C(s32 a1) {
    _365c = a1;
}

// 0x7100a349f4
bool ScreenPauseMenu::sub_7100A349F4() {
    return _3bb4 == 3;
}

// 0x7100a34a10
bool ScreenPauseMenu::sub_7100A34A10() {
    return _3bb4 != 0;
}

s32 sUnk_710249ad68 = -1;
s32 sUnk_710249ad6c = -1;
s32 sUnk_710249ad70 = -1;
s32 sUnk_710249ad74 = 3;
bool sUnk_71025f5740;
bool sUnk_71025f5741;

// 0x7100a6670c
void ScreenSystemWindow01::sub_7100A6670C() {
    sUnk_710249ad68 = -1;
    sUnk_710249ad6c = -1;
    sUnk_710249ad70 = -1;
    sUnk_71025f5740 = false;
    sUnk_71025f5741 = false;
    sUnk_710249ad74 = 3;
}

// 0x7100a66760
s32 ScreenSystemWindow01::sub_7100A66760() {
    if (isE3DemoMode() && !isRIDDemo())
        return 0;
    if (!sUnk_71025f5740)
        return -1;
    auto* save = SaveSystem::instance();
    if (!save)
        return -1;
    if (sUnk_710249ad6c < 0)
        return -1;
    if (sUnk_710249ad74 != 0)
        return sUnk_710249ad6c;
    return save->isFinishedSavingMaybe() ? sUnk_710249ad6c : -1;
}

// 0x7100a667ec
s32 ScreenSystemWindow01::sub_7100A667EC() {
    if (isE3DemoMode() && !isRIDDemo())
        return 0;
    return sUnk_710249ad70;
}

// 0x7100a67704: waits until every texture controller is loaded
void ScreenSystemWindow01::m89() {
    bool ready = true;
    for (auto& controller : _3748) {
        if (controller.sub_71009CBEAC()) {
            controller.sub_71009CC3A0();
            ready = false;
        }
        ready &= controller.sub_71009CBFA4();
    }
    if (ready)
        _292 |= 0x20;
}

// 0x7100a68010
void ScreenSystemWindow01::m98() {
    sUnk_710249ad68 = -1;
    sUnk_710249ad6c = -1;
    sUnk_71025f5740 = false;
    sUnk_71025f5741 = false;
    _4b61 = false;
    _4b62 = false;
    _4b7c.init(0.0f);
    x_2();
    if (sUnk_710249ad74)
        _4b60 = !sub_7100A6641C();
}

// 0x7100a680a8
void ScreenSystemWindow01::m99() {
    mButtonGroup->_38 |= 2;
    s32 tag;
    if (sUnk_710249ad74) {
        _3610->setFlag10(false);
        _3618->setFlag10(false);
        tag = 0x62;
    } else {
        _3610->setFlag10(true);
        _3618->setFlag10(true);
        tag = 0x60;
    }
    setReservedBoxCursorNode(findBoxCursorNodeByTag(tag));
    mActiveCursorNode = nullptr;
}

// 0x7100a6814c (CSV ScreenSystemWindow01::m100)
void ScreenSystemWindow01::m100() {
    if (_4b5c && u32(sUnk_710249ad74 - 1) <= 1)
        invokeSoundLink2Event_("mc_CloseOnlyLoad");
}

// 0x7100a6637c
void ScreenSystemWindow01::m128() {
    for (auto& controller : _3748)
        controller.sub_71009CC970();
}

// 0x7100a663d8 (CSV ScreenSystemWindow01::m129)
void ScreenSystemWindow01::m129() {
    if (sUnk_710249ad74)
        _4b60 = !sub_7100A6641C();
}

// 0x7100a3f3f4
void ScreenPickUp::setItemAndOpen(const sead::SafeString& item, bool show) {
    open(3);
    if (show)
        sub_7100A3F450(item, 5.0f);
}

// 0x71025f1a28 (initialised by the TU's static initialiser 0x7100a406dc)
static sead::SafeString sPickUpLayoutName = "PickUpWin_00";

// 0x7100a3f768
// NON_MATCHING: the original addresses the string from the TU's merged-static base (+0x148); ours has other
// statics around it (+0x10).
const char* ScreenPickUp::getLayoutName_() const {
    return sPickUpLayoutName.cstr();
}

// 0x7100a3f450
// NON_MATCHING: the original null-checks the found window pointer (the loop exits to the unlock instead of a csel);
// it matches with `if (it->mOrder >= 0) continue; if (PickUpWin* win = it.operator->()) {...} break;`.
void ScreenPickUp::sub_7100A3F450(const sead::SafeString& item, f32 time) {
    mCS.lock();
    PickUpWin* win = nullptr;
    for (auto& entry : mWins) {
        if (entry.mOrder < 0) {
            win = &entry;
            break;
        }
    }
    if (win) {
        for (auto& entry : mWins) {
            if (entry.mOrder >= 0)
                ++entry.mOrder;
        }
        win->mTimer.init(time);
        win->setItem(item);
        if (win->mLayout) {
            nn::ui2d::Pane* pane = win->mLayout->GetPane();
            nn::ui2d::Pane* parent = pane->GetParent();
            parent->RemoveChild(pane);
            parent->AppendChild(pane);
            win->mLayout->GetPane()->SetAlpha(255);
            win->mLayout->sub_7100BDDE7C(false, 0, true);
            if (win->mFlashAnim)
                win->mFlashAnim->PlayAuto(1.0f);
            win->mOrder = 0;
            win->mClosing = false;
        }
    }
    mCS.unlock();
}

// 0x7100a3f5ac
void ScreenPickUp::PickUpWin::setItem(const sead::SafeString& item) {
    mName = item;
    mType = PauseMenuDataMgr::getType(item);
    updateCompareAnim();
    eui::MessageString message;
    sub_7100AA2BDC(mName, &message);
    setWidgetString(mLayout, "T_ItemName_00", message);
    sead::FixedSafeString<128> path;
    sub_7100AA3B50(item, &path, -1);
    requestTexture(path);
}

// 0x7100a3f79c
void ScreenPickUp::m93(sead::Heap* heap) {
    sead::SafeString first_name = "Pa_PickUpWin_00";
    sead::SafeString prefix = "Pa_PickUpWin_";
    if (PickUpWin* win = mWins.emplaceBack()) {
        win->mScreen = this;
        win->mLayout = sub_7100BEAFB0("Pa_PickUpWin_00");
        win->init(heap);
    }
    for (s32 i = 6; i > 0; --i) {
        if (PickUpWin* win = mWins.emplaceBack()) {
            sead::FormatFixedSafeString<32> name("%s%02d", prefix.cstr(), i);
            win->mScreen = this;
            eui::PartsEx* parts = eui::sub_7100945088(sub_7100A48104(first_name, nullptr));
            win->mLayout = sub_7100A47A5C(
                heap, 1, parts ? static_cast<eui::LayoutEx*>(parts->mPartsLayoutLink.layout) : nullptr, name,
                parts, true, true);
            win->init(heap);
        }
    }
}

// 0x7100a3fab4
void ScreenPickUp::PickUpWin::init(sead::Heap* heap) {
    mResHandle = new (heap) ksys::res::Handle;
    mColorAnim = mLayout->tryCreateAnimatorAuto("Color", false);
    if (mColorAnim)
        mColorAnim->StopAtMin();
    mGuideOutAnim = mLayout->tryCreateAnimatorAuto("GuideOut", false);
    if (mGuideOutAnim)
        mGuideOutAnim->StopAtMin();
    mGuideOffAnim = mLayout->tryCreateAnimatorAuto("GuideOff", false);
    if (mGuideOffAnim)
        mGuideOffAnim->StopAtMin();
    mFlashAnim = mLayout->tryCreateAnimatorAuto("Flash", false);
    if (mFlashAnim)
        mFlashAnim->StopAtMin();
    const auto& pos = mLayout->GetPane()->GetPosition();
    mBasePos.x = pos.x;
    mBasePos.y = pos.y;
    mBasePos.z = pos.z;
    mPos = mBasePos;
    mLayout->startAnimCloseImpl_(false, true);
    if (mLayout && mResHandle) {
        if (nn::ui2d::Pane* pane = mLayout->GetPane()->FindPaneByName("P_CaptureItem_00", true)) {
            if (nn::ui2d::Material* material = pane->GetMaterial())
                eui::SetTextureInfoFromTexMap(&mTexInfo, material->GetTexMapArray()[0]);
        }
    }
}

// 0x7100a3fc10
void ScreenPickUp::m94() {
    bool visible = false;
    if (sub_7100AA948C()) {
        visible = true;
        if (sub_7100AA8F10() && ksys::evt::Manager::instance()) {
            auto* event = ksys::evt::Manager::instance()->getActiveEvent();
            if (event && event->mEventName == "Demo049_0")
                visible = false;
        }
    }
    sub_7100AA94C4(mLayout, visible);
    if (sub_7100AA8E5C() || sub_7100AA8F30())
        return;
    mCS.lock();
    for (auto& win : mWins) {
        if (win.mOrder >= 0)
            win.update();
    }
    mCS.unlock();
}

// NON_MATCHING: three spots of scheduling: case 0 keeps &mBasePos in a register across the timer call, case 1 / 2
// load mScreen and &mPos.y after the float constants, and the original computes the alpha before it loads the root
// pane (it matches with a local `const u8 alpha = ...;` before `mLayout->GetPane()->SetAlpha(alpha)`).
// 0x7100a3fd44: moves the window to its place for mOrder (0: shown, 1 / 2: pushed down; later ones slide out
// and fade)
void ScreenPickUp::PickUpWin::update() {
    if (mTextureRequested) {
        if (mResHandle->requestedLoad() && mResHandle->isSuccess() && mResHandle->getResource()) {
            applyTexture();
            mTextureRequested = false;
        } else if (mResHandle->checkLoadStatus() &&
                   mResHandle->getStatus() == ksys::res::Handle::Status::_1) {
            mResHandle->requestUnload2();
            ksys::res::LoadRequest request;
            request.mRequester = "uiPickUpWin_00Screen";
            mResHandle->requestLoad("UI/StockItem/NoImage.bitemico", &request, nullptr);
        }
    }

    if (mLayout && (mLayout->isAnimCloseEnd(false) || mFadedOut) && mClosing) {
        close();
        return;
    }

    switch (mOrder) {
    case 0:
        if (mTimer.updateAndCheckEnded() && mLayout && !mClosing) {
            mLayout->startAnimCloseImpl_(false, false);
            mClosing = true;
        }
        mPos = mBasePos;
        if (mGuideOffAnim && mGuideOffAnim->mFrame == 0.0f && ksys::act::hasTag(mName, ksys::act::tags::Rupee))
            mGuideOffAnim->PlayAuto(1.0f);
        break;
    case 1:
        if (mTimer.updateAndCheckEnded() && mLayout && !mClosing) {
            mLayout->startAnimCloseImpl_(false, false);
            mClosing = true;
        }
        sub_7100AA2350(mScreen, &mPos.y, mBasePos.y + -75.0f, 0.2f, 500.0f, 0.1f);
        if (mGuideOutAnim && mGuideOutAnim->mFrame == 0.0f)
            mGuideOutAnim->PlayAuto(1.0f);
        break;
    case 2:
        if (mTimer.updateAndCheckEnded() && mLayout && !mClosing) {
            mLayout->startAnimCloseImpl_(false, false);
            mClosing = true;
        }
        sub_7100AA2350(mScreen, &mPos.y, mBasePos.y + -150.0f, 0.2f, 500.0f, 0.1f);
        if (mGuideOutAnim && mGuideOutAnim->mFrame == 0.0f)
            mGuideOutAnim->PlayAuto(1.0f);
        break;
    default: {
        mWasInPlace = mInPlace;
        const f32 limit = mBasePos.y + -150.0f;
        sub_7100AA2350(mScreen, &mPos.y, mBasePos.y + -225.0f, 0.2f, 500.0f, 0.1f);
        mInPlace = mPos.y <= limit;
        if (mInPlace) {
            mArrived = !mWasInPlace;
            if (mWasInPlace) {
                if (mTimer.updateAndCheckEnded())
                    mFadedOut = true;
            } else {
                mTimer.init(0.3f);
            }
            if (mLayout)
                mLayout->GetPane()->SetAlpha(s32((1.0f - mTimer.getProgress()) * 255.0f));
        } else {
            mArrived = false;
        }
        if (!mClosing)
            mClosing = true;
        if (mGuideOutAnim && mGuideOutAnim->mFrame == 0.0f)
            mGuideOutAnim->PlayAuto(1.0f);
        break;
    }
    }

    if (mLayout) {
        nn::ui2d::Pane* pane = mLayout->GetPane();
        pane->SetPosition(mPos);
    }
}

// 0x7100a400e0
void ScreenPickUp::m86() {
    mCS.lock();
    for (auto& win : mWins)
        win.close();
    close(-4);
    mCS.unlock();
}

// 0x7100a4014c
void ScreenPickUp::m83() {
    mCS.lock();
    for (auto& win : mWins)
        win.close();
    close(-4);
    mCS.unlock();
}

// 0x7100a401b8
void ScreenPickUp::m91() {
    mCS.lock();
    for (auto& win : mWins)
        win.close();
    close(-4);
    mCS.unlock();
}

// 0x7100a40224
// NON_MATCHING: regalloc only (x8 / x9 swapped for the texture map and &mTexInfo).
void ScreenPickUp::PickUpWin::close() {
    mClosing = false;
    mInPlace = false;
    mWasInPlace = false;
    mArrived = false;
    mFadedOut = false;
    mOrder = -1;
    if (mGuideOutAnim)
        mGuideOutAnim->StopAtMin();
    if (mGuideOffAnim)
        mGuideOffAnim->StopAtMin();
    mLayout->startAnimCloseImpl_(false, true);
    if (mResHandle->requestedLoad() && mResHandle->isSuccess() && mResHandle->getResource()) {
        mResHandle->parseResource(nullptr);
        nn::ui2d::Pane* pane = mLayout->GetPane()->FindPaneByName("P_CaptureItem_00", true);
        if (!pane)
            return;
        nn::ui2d::Material* material = pane->GetMaterial();
        if (!material)
            return;
        sead::Graphics::instance()->lockDrawContext();
        material->GetTexMapArray()[0].ReplaceTextureInfo(&mTexInfo);
        sead::Graphics::instance()->unlockDrawContext();
        mResHandle->requestUnload2();
    }
}

// 0x7100a40360
// NON_MATCHING: regalloc only (x8 / x9 swapped for the texture map and the texture info, as in close()).
void ScreenPickUp::PickUpWin::applyTexture() {
    if (!mLayout || !mResHandle)
        return;
    mResHandle->parseResource(nullptr);
    nn::ui2d::Pane* pane = mLayout->GetPane()->FindPaneByName("P_CaptureItem_00", true);
    if (!pane)
        return;
    nn::ui2d::Material* material = pane->GetMaterial();
    if (!material)
        return;
    auto* resource = mResHandle->getResource();
    if (!resource)
        return;
    auto* texture = sead::DynamicCast<Unk_710247e8c0>(resource);
    sead::Graphics::instance()->lockDrawContext();
    material->GetTexMapArray()[0].ReplaceTextureInfo(&texture->mTexInfo);
    sead::Graphics::instance()->unlockDrawContext();
}

// 0x7100a40328
void ScreenPickUp::m80(bool visible) {
    if (visible)
        sub_7100AA94C4(mLayout, sub_7100AA948C());
    else
        sub_7100AA94C4(mLayout, false);
}

// 0x7100a40470
void ScreenPickUp::PickUpWin::updateCompareAnim() {
    if (!isPouchItemWeapon(mType) || mType == PouchItemType::Arrow) {
        mColorAnim->Stop(0.0f);
        return;
    }
    const PouchItem* equipped = PauseMenuDataMgr::instance()->getEquippedItem(mType);
    if (!equipped || !equipped->isInInventory()) {
        mColorAnim->Stop(0.0f);
        return;
    }
    const PouchItem* item = PauseMenuDataMgr::instance()->getLastAddedItem();
    f32 frame;
    if (item->isInInventory() && item->isEquipped()) {
        frame = 1.0f;
    } else {
        const s32 equipped_value = sub_7100AA7AC8(*equipped);
        const s32 value = item->isInInventory() ? sub_7100AA7AC8(*item) : 0;
        if (equipped_value == value)
            frame = 3.0f;
        else if (equipped_value < value)
            frame = 1.0f;
        else if (equipped_value > value)
            frame = 2.0f;
        else
            frame = 0.0f;
    }
    mColorAnim->Stop(frame);
}

// 0x7100a4055c
void ScreenPickUp::PickUpWin::requestTexture(const sead::SafeString& path) {
    if (mResHandle) {
        if (mResHandle->requestedLoad())
            mResHandle->requestUnload2();
        ksys::res::Handle::Status status{};
        ksys::res::LoadRequest request;
        request.mRequester = "uiPickUpWin_00Screen";
        mResHandle->requestLoad(path, &request, &status);
    }
    mTextureRequested = true;
}

struct RuntimeTip {
    sead::SafeString message;
    sead::SafeString flag;
};

static RuntimeTip sUnk_71025EFC18[] = {
    {"0000", "GuideSPlus_GurdJust"},
    {"0001", "GuideSPlus_KaihiJust"},
    {"0003", "GuideS_HeadShoot"},
    {"0002", "GuideSPlus_Surfing"},
    {"0004", "GuideS_WarningGanbari"},
    {"0005", "GuideS_WarningCold"},
    {"0006", "GuideS_WarningHot"},
    {"0007", "GuideS_StealthAttack"},
    {"0008", "GuideS_WeaponDestruction"},
    {"0009", "GuideS_WeaponThrowAttack"},
    {"0010", "GuideS_WarningBurn"},
    {"0013", "GuideS_ClimbSlip"},
    {"0014", "GuideS_WeaponBurning"},
    {"0015", "GuideSPlus_Squat"},
    {"0017", "GuideS_WolfLead"},
    {"0016", "GuideS_SandSealError"},
    {"0018", "GuideS_Recipe"},
    {"0019", "GuideS_ElectricDamage"},
    {"0020", "GuideS_WarningColdLv2"},
    {"0021", "GuideS_WarningHotLv2"},
    {"0022", "GuideS_WarningBurnLv2"},
    {"0023", "GuideS_RelicControl"},
    {"0024", "GuideS_MotorcycleGasOff"},
};
static sead::Buffer<RuntimeTip> sUnk_71025EFC08(sUnk_71025EFC18);

// NON_MATCHING: the independent Buffer produces different global field offsets.
bool getRuntimeTipFlag(s32 index) {
    if (u32(index) > 22)
        return false;
    return ksys::gdt::getBoolByKey(sUnk_71025EFC08[index].flag, false);
}

// 0x7100a26954
void ScreenMessageTipsRunTime::sub_7100A26954() {
    if (_3658 != -1) {
        if (_3658 != _3660) {
            _3660 = _3658;
            _3664 = _365c;
            _3684 = 0;
        }
        _3658 = -1;
        _365c = false;
    }
    if (_3664 && sub_7100AA8F10())
        return;
    if (!(_292 & 2) || _3684 == -1)
        return;
    if (++_3684 != 15)
        return;
    _3684 = -1;
    _3680 = 0;
    if (sub_7100AA8F10()) {
        _3660 = -1;
    } else {
        sub_7100A26A5C(_3660);
        if (mState == 1 || mState == 2)
            open(2);
        else
            open(1);
    }
    _3664 = false;
}

// NON_MATCHING: the independent Buffer produces different global field offsets.
void ScreenMessageTipsRunTime::sub_7100A268AC(s32 index, s32 force) {
    _3618.lock();
    if (u32(index) <= 22 && _3660 != index &&
        !ksys::gdt::getBoolByKey(sUnk_71025EFC08[index].flag, false) &&
        ((force & 1) || (!sub_7100AA8F10() && !sub_7100AA8DD4()))) {
        _3658 = index;
        _365c = force & 1;
    }
    _3618.unlock();
}

// 0x7100a26be8
void ScreenMessageTipsRunTime::m93(sead::Heap*) {
    _3610 = mLayout->createAnimatorAuto("GuideOn", false);
    _3668.init(6.0f);
}

// 0x7100a26db8
void ScreenMessageTipsRunTime::m101() {
    if (_3684 == -1)
        _3660 = -1;
}


// 0x71009b0b44
eui::AlignPane* sub_71009B0B44(eui::LayoutEx* layout, const char* name) {
    return nn::font::DynamicCast<eui::AlignPane>(layout->mPane->FindPaneByName(name, true));
}

// ScreenPauseMenu creator; native getter/D0 precede its screen constructor.
static const ChildControlCreatorEntry sUnk_71024934b0[] = {
    {"Pa_Save_00", sub_7100A32F3C, 0},
    {"Pa_Quest_00", sub_7100A33038, 0},
    {"Pa_PagePorch_", sub_7100A33134, 1},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_71024934a0(sUnk_71024934b0);
// 0x7100a32f0c
// NON_MATCHING: adjacent owner-TU statics are merged, adding an address offset instruction.
const sead::Buffer<const ChildControlCreatorEntry>* Unk_71024934f8::getEntries() const {
    return &sUnk_71024934a0;
}

// 0x7100a32f3c
ScreenChild* sub_7100A32F3C(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_710247b428(layout_ex);
}

// 0x7100a33134
ScreenChild* sub_7100A33134(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_710247a028(layout_ex);
}

}  // namespace uking::ui
