#include "Game/UI/euiTagProcessor.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Resource/resHandle.h"
#include "Game/gameGraphics.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "Game/gameSaveSystem.h"
#include "Game/gameRoot1.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUnkTiny.h"
#include "Game/UI/uiShopMgr.h"
#include "Game/UI/uiTagProcessor.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameScene.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include <nn/os.h>

namespace uking::ui {

bool ScreenAppAlbum::sub_71009D3DA0() const {
    return _3630 && _3630->mFrame != 0.0f;
}

bool ScreenAppAlbum::sub_71009D3DC0() const {
    // called through a pointer in the original (not devirtualised)
    return mStateMachine.getState()->getId() == (&sUnk_71025dc3c0)->getId();
}


// 0x7100a41558
void ScreenRupee::sub_7100A41558() {
    _3610 = true;
    if (mState == 0 || mState == 3)
        sub_7100A410D8(1);
}

// 0x7100a20dd0
bool ScreenMainShortCut::sub_7100A20DD0() {
    // called through a pointer in the original (not devirtualised)
    if (mStateMachine.getState()->getId() == (&sUnk_71025ef170)->getId())
        return false;
    // called through a pointer in the original (not devirtualised)
    return mStateMachine.getState()->getId() != (&sUnk_71025ef290)->getId();
}

// 0x71009fd674
bool ScreenAppTool::sub_71009FD674() {
    // called through a pointer in the original (not devirtualised)
    return mStateMachine.getState()->getId() == (&sUnk_71025ec670)->getId();
}

// 0x7100a32d98
void ScreenPauseMenuRecipe::m101() {
    if (_3698->requestedLoad())
        _3698->requestUnload2();
    if (_36a0->requestedLoad())
        _36a0->requestUnload2();
    if (_36a8->requestedLoad())
        _36a8->requestUnload2();
    if (_36b0->requestedLoad())
        _36b0->requestUnload2();
    if (_36b8->requestedLoad())
        _36b8->requestUnload2();
    _292 |= 0x20;
}

// 0x7100a16164
void ScreenMainScreen3D::m87() {
    _3f34 = -1;
}

// 0x7100a28688
void ScreenOPtext::m154(s32 index) {
    static const f32 frames[3] = {0.0f, 1.0f, 2.0f};
    if (static_cast<u32>(index) > 2 || !_3610)
        return;
    const f32 frame = frames[index];
    _3618 = frame;
    _3610->Stop(frame);
}

// 0x7100a4ac24 / 0x7100a4ac40
void ScreenShopBG::m98() {
    Graphics::instance()->sub_7100F35FA4(true, false);
}

void ScreenShopBG::m101() {
    Graphics::instance()->sub_7100F35FA4(false, false);
}

// 0x7100a4b0a8
void ScreenShopBtnList15::m94() {
    _3610.sub_7100A816D8();
}

// 0x7100a52310
void ScreenShopInfo::m94() {
    _3698.sub_7100A816D8();
}

// 0x7100a5231c
void ScreenShopInfo::m101() {
    if (_3690 && _3690->_91)
        _3690->startAnimCloseImpl_(false, true);
}

// 0x7100a52db0
void ScreenShopInfo::sub_7100A52DB0(u32 mode, ShopInfoTagData* data) {
    if (_3620 == nullptr)
        return;
    _3620->Stop(mode);
    if (mode != 1) {
        if (mode != 0)
            return;
        if (_3650 == nullptr)
            return;
        eui::MessageString msg;
        sub_7100AA2E08(data, &msg);
        _3650->sub_7100BD9CDC(msg, 0);
        _3650->sub_7100BD9B5C();
        return;
    }
    sub_7100A52E60(data, 0, -1);
}

// 0x7100a081e8
void ScreenDoCommand::m100() {
    _3660 = -1;
}

// 0x7100a20230
void ScreenMainShortCut::m84() {
    if (isClosed())
        open(1);
    if (_36e0)
        _36e0->StopAtMin();
}

// 0x7100a205f0
void ScreenMainShortCut::m98() {
    _3790->sub_710093DAE8(2);
}

// 0x7100a38018
void ScreenPauseMenu::m101() {
    if (_3674)
        sub_7100A38028();
}

// 0x7100a383f4
void ScreenPauseMenu::m106(eui::AnimButton* button) {
    if (static_cast<u32>(button->mTag - 9) <= 59)
        sub_7100A3840C(button);
}

// 0x7100a07cf4
void ScreenDoCommand::sub_7100A07CF4() {
    if (mState == 0 || mState == 3)
        return;
    _3664 = _365c;
    Screen::close(-1);
}

// 0x7100a07d18
void ScreenDoCommand::sub_7100A07D18() {
    _3658 = -1;
    _365c = -1;
}

// 0x71009dd7a8
void ScreenAppHome::sub_71009DD7A8() {
    const s32 saved = _3808;
    sub_71009DCF18(12);
    _3808 = saved;
}

// 0x71009dd7ec
void ScreenAppHome::sub_71009DD7EC(bool a1) {
    if (a1)
        sub_71009DCF18(9);
    else
        sub_71009DCF18(8);
}

// 0x71009dd800
void ScreenAppHome::sub_71009DD800(bool a1) {
    if (a1)
        sub_71009DCF18(10);
    else
        sub_71009DCF18(11);
}

// 0x71009dd838
bool ScreenAppHome::sub_71009DD838(f32 a1) const {
    return _3818.sub_7100938294(a1);
}

// 0x71009ff43c
void ScreenAppTool::m107(eui::AnimButton*) {
    _3610 = 1;
}

// 0x71009ff6a8
void ScreenAppTool::m155() {
    if (sUnk_71025ec548)
        mStateMachine.changeState(&sUnk_71025ec610);
}

// 0x71009ffd30
void ScreenAppTool::m163() {
    if (_3744 == 1 && _3620 && _3620->mFrame == static_cast<f32>(_3620->GetFrameSize())) {
        _3744 = 3;
        mStateMachine.changeState(&sUnk_71025ec670);
    }
}

// 0x71009ffdb0
void ScreenAppTool::m166() {
    if (!Unk_71025d69f0::instance()->_36)
        _3610 = 1;
}

// 0x71009ffdd4
void ScreenAppTool::m167() {
    if (Unk_71025d69f0::instance()->_36 && sUnk_71025ec549) {
        _3610 = 1;
        mStateMachine.changeState(&sUnk_71025ec5b0);
    }
}

// 0x7100a31be0
void ScreenPauseMenuInfo::sub_7100A31BE0() {
    if (_3904 == 1)
        _3904 = 2;
    if (_391c == 1)
        _391c = 2;
}

// 0x7100a1ab14
void ScreenMainScreen::sub_7100A1AB14(s64 a1, f32 value) {
    sub_7100A1A518(a1, true);
    _3720 = value;
}

// 0x7100a1ab84
void ScreenMainScreen::sub_7100A1AB84(s32 a1) {
    if (_3648)
        _3648->sub_710098AE8C(a1);
}

// 0x7100a1abc8
void ScreenMainScreen::sub_7100A1ABC8(s32 value) {
    if (_3620 && _36b0) {
        _36bc = value;
        _36b8 = 1;
    }
}

// 0x7100a1abe8
bool ScreenMainScreen::sub_7100A1ABE8() const {
    return _36b8 != 0;
}

// 0x7100a1abf8
void ScreenMainScreen::sub_7100A1ABF8() {
    if (_3620 && _36b0) {
        _36b8 = 1;
        _36bc = 0;
    }
}

// 0x7100a1ab58
void ScreenMainScreen::sub_7100A1AB58(s32 a1) {
    if (_3658)
        _3658->_150 = a1;
}

// 0x7100a1ab74
void ScreenMainScreen::showInfoOverlayWithString(s32 type, const sead::SafeString& text) {
    if (_3648)
        _3648->sub_710098A93C(type, text);
}

// 0x7100a1a4e4
void ScreenMainScreen::sub_7100A1A4E4(s64 a1) {
    sub_7100A1A518(a1, false);
    if (!sub_7100AA8F10())
        _3720 = -99.0f;
}

// 0x7100a1e1e0
bool ScreenMainScreen::sub_7100A1E1E0() {
    if (!_3ca8)
        return false;
    return !_3ca8->isAnimOpenEnd(false);
}

// 0x7100a1e44c
f32 ScreenMainScreen::sub_7100A1E44C() {
    return 1.0f;
}

}  // namespace uking::ui

namespace uking::ui {

// Voice/emotion names for the dialog voice tags (0x710250b268 in the original; indexed by the
// tag byte mapped into 0..5).
static const char* sVoiceNames[6] = {"Normal", "Pleasure", "Anger", "Sorrow", "Surprise", "Thinking"};

// TU-global voice state (0x710261ef90 in the original; initialised by the 0x71010b60d0 static
// initializer: id 0x8004ef, the tick, zero, then the per-emotion voice ids at +0x28).
struct Unk_710261EF90 {
    u64 _0 = 0x8004ef;
    u64 _8 = nn::os::GetSystemTick().value;
    u64 _10 = 0;
    u8 _18[0x28 - 0x18]{};
    s32 _28[6] = {2, 9, 0xc, 0xa, 0x12, 0xe};
};
static Unk_710261EF90 sUnk_710261EF90;

// 0x71010b5b60
bool ScreenMessageDialog::isEnableControl() const {
    return true;
}

// 0x71010b343c
bool ScreenMessageDialog::sub_71010B343C() {
    switch (_350) {
    case 6:
    case 7:
    case 10:
        return true;
    default:
        return false;
    }
}

// 0x71010b34b4
void ScreenMessageDialog::sub_71010B34B4(bool choice_mode, s32 stock) {
    if (choice_mode) {
        _738 = stock;
        _73c = 1;
    } else {
        _738 = -1;
        _73c = -1;
    }
}

// 0x71010b34a0
void ScreenMessageDialog::sub_71010B34A0(bool a1) {
    _773 = a1 ? 1 : 2;
}

// 0x71010b3294 (CSV unnamed): scan the text for a continuation marker; record the kind in _774.
// NON_MATCHING: the original has a third (dead) tag-marker arm that loads from a null pointer;
// only the 0xe/0xf arms are reachable (the (head|1) pre-check proves it), so the else is omitted
// (q defaults to null). Also differs in the 0xe arm's registers and branch layout.
void ScreenMessageDialog::sub_71010B3294() {
    s32 result;
    if (_720 == nullptr || !_728.hasProc()) {
        result = 0;
    } else {
        _768 = 0xffff;
        _76d = 0;
        if (_778->_5d) {
            result = 2;
        } else {
            result = 0;
            if ((s32)_3a0.getLength() >= 1) {
                const char16* end = _3a0.getString() + (s32)_3a0.getLength();
                const char16* p = _3a0.getString();
                while (true) {
                    const char16 head = *p;
                    if ((head | 1) != 0xf) {
                        if (head > 0x2025) {
                            if (head == 0x2026) {
                                result = 1;
                                break;
                            }
                            if (head == 0x3000) {
                                result = 1;
                                break;
                            }
                            if (head != 0x30fb || p + 4 >= end || p[1] != 0x30fb ||
                                p[2] != 0x30fb) {
                                ksys::act::sActorDebugFlagsMaybe.set(2);
                                break;
                            }
                            result = 1;
                            break;
                        }
                        if (head == 0xa) {
                            result = 1;
                            break;
                        }
                        if (head == 0x20) {
                            result = 1;
                            break;
                        }
                        if (head != 0x2e || p + 4 >= end || p[1] != 0x2e || p[2] != 0x2e) {
                            ksys::act::sActorDebugFlagsMaybe.set(2);
                            break;
                        }
                        result = 1;
                        break;
                    }
                    const char16* q = nullptr;
                    if (head == 0xf) {
                        q = p;
                        p += 3;
                    } else if (head == 0xe) {
                        q = p;
                        p = reinterpret_cast<const char16*>(reinterpret_cast<const u8*>(p) + p[3] +
                                                           8);
                    }
                    const u16 type = q[1];
                    if (type > 1) {
                        if (type == 2) {
                            ksys::act::sActorDebugFlagsMaybe.set(2);
                            break;
                        }
                        if (type == 5) {
                            result = 1;
                            break;
                        }
                        if (type == 0xc9) {
                            ksys::act::sActorDebugFlagsMaybe.set(2);
                            break;
                        }
                    } else if (type == 1) {
                        if (q[2] == 0) {
                            result = 1;
                            break;
                        }
                    }
                    if (p >= end) {
                        ksys::act::sActorDebugFlagsMaybe.set(2);
                        break;
                    }
                }
            } else {
                ksys::act::sActorDebugFlagsMaybe.set(2);
            }
        }
    }
    _774 = result;
}

// 0x71010b34d0
const char* ScreenMessageDialog::getLayoutName_() const {
    return !_76a ? "Message_00" : "MessageSp_00";
}

// 0x71010b3468: TagInfo adapter into ksys::eft::sub_710105DF88.
void sub_71010B3468(const sead::MessageSet<char16>::TagInfo* tag, ksys::act::Actor* actor, bool flag) {
    ksys::eft::sub_710105DF88(actor, reinterpret_cast<const char*>(tag->getParam()), ~flag & 1,
                              flag & 1);
}

// 0x71010b3484: TagInfo adapter into ksys::eft::sub_710105DFA4.
void sub_71010B3484(const sead::MessageSet<char16>::TagInfo* tag, ksys::act::Actor* actor, bool flag) {
    ksys::eft::sub_710105DFA4(actor, tag->getParam()[0], ~flag & 1, flag & 1);
}

// 0x71010b3188 (CSV unnamed): voice/emotion tag dispatch.
// NON_MATCHING: the nonzero-voice path computes the out value (orr+add) and the call arg
// (add #0xfe) separately while ours shares one sub (GVN merges them); the inverted-flag arg is
// mvn+and here vs the original's early eor+and (a single-use `bool nb = !b;` temp reproduces the
// eor but sinks it to the call — logged as Borderline). Register names cascade from there.
void sub_71010B3188(const sead::MessageSet<char16>::TagInfo* tag, ksys::act::Actor* actor, bool a,
                    s16* out, bool b) {
    u8 v8 = tag->getParam()[0];
    u8 mapped = v8 > 5 ? v8 - 6 : v8;
    if (!b) {
        sead::SafeStringBase<char> voice(sVoiceNames[mapped < 6 ? mapped : 0]);
        sub_7100EE6B88(actor, voice, v8 > 5);
    }
    if (a) {
        u8 v9 = tag->getParam()[1];
        if (v9 == 1)
            return;
        u32 arg;
        if (v9 == 0) {
            if (v8 < 6)
                return;
            arg = sUnk_710261EF90._28[mapped < 6 ? mapped : 0];
            if (out != nullptr) {
                *out = (s16)(s8)arg;
                return;
            }
        } else {
            if (out != nullptr) {
                *out = (u16)(v9 - 2);
                return;
            }
            arg = v9 - 2;
        }
        ksys::eft::sub_710105DFA4(actor, arg, !b & 1, b & 1);
    }
}

// 0x71010b306c (CSV unnamed): set the dialog's actor.
void ScreenMessageDialog::sub_71010B306C(ksys::act::Actor* actor) {
    _720 = actor;
    _728.acquire(actor, false);
}

// 0x71010b307c (CSV unnamed): scan the text for a voice tag, apply the emotion to the actor.
// NON_MATCHING: the original has a third (dead) tag-marker arm that loads from a null pointer;
// only the 0xe/0xf arms are reachable (the (head|1) pre-check proves it), so it is omitted here.
// Also differs in q's register, one extra and-x on the voice index, and the tail schedule.
void ScreenMessageDialog::sub_71010B307C() {
    if (_720 == nullptr || !_728.hasProc())
        return;
    const char16* p = _3a0.getString();
    const char16* q;
    do {
        char16 head = *p;
        if ((head | 1) != 0xf)
            return;
        if (head == 0xe) {
            q = p;
            p = reinterpret_cast<const char16*>(reinterpret_cast<const u8*>(p) + p[3] + 8);
        } else if (head == 0xf) {
            q = p;
            p += 3;
        } else {
            return;
        }
        if (q[1] != 0) {
            if (q[1] != 3)
                return;
            if (q[2] != 1)
                return;
            u8 eb = reinterpret_cast<const u8*>(q)[8];
            u8 m = eb > 5 ? eb - 6 : eb;
            sead::SafeStringBase<char> voice(sVoiceNames[m < 6 ? m : 0]);
            sub_7100EE6B88(_720, voice, eb > 5);
            return;
        }
    } while (q[2] - 1u < 3);
}

// 0x710109e94c
void ScreenDemoMessage::sub_710109E94C() {
    if (_548 != -1)
        close(-1);
}

// 0x710109e96c
void ScreenDemoMessage::sub_710109E96C() {
    _548 = -1;
}

// 0x710109e978
void ScreenDemoMessage::sub_710109E978() {
    _558 = true;
}

// 0x710109e9d4 (CSV unnamed; slot 27)
eui::TagProcessor* ScreenDemoMessage::doCreateTagProcessor_(sead::Heap* heap) {
    auto* processor = ScreenBase::doCreateTagProcessor_(heap);
    processor->setRubyEnabled(true);
    return processor;
}

// 0x710109e984 (slot 93)
void ScreenDemoMessage::m93(sead::Heap*) {
    _550 = mLayout->tryCreateAnimatorAutoWithWarning("Pos", true);
    if (_550)
        _550->Stop(0.0f);
}

// 0x710109e9f0 (slot 94)
void ScreenDemoMessage::m94() {
    if (_558) {
        _548 = 0;
        if (_300.getString()) {
            bool has_next_page = false;
            mLayout->setMessageStringForEachIdWithPage("T_Message_00", _300, &has_next_page, 0, true,
                                                       nullptr);
            x_2();
            _548 = has_next_page ? _548 + 1 : -1;
        }
        _558 = false;
    }
}

// 0x710109ea70 (slot 98)
void ScreenDemoMessage::m98() {
    if (_300.getString()) {
        bool has_next_page = false;
        mLayout->setMessageStringForEachIdWithPage("T_Message_00", _300, &has_next_page, _548, true,
                                                   nullptr);
        x_2();
        _548 = has_next_page ? _548 + 1 : -1;
    }
    if (_550)
        _550->Stop(_559 ? 1.0f : 0.0f);
}

// 0x710109eb08 (slot 101)
void ScreenDemoMessage::m101() {
    if (_548 != -1)
        open(1);
}

// 0x71010a87f0
// NON_MATCHING: the original keeps the "type 18 while 19 is current" case as its own branch that jumps to the shared
// store; clang makes it a select
bool ScreenMessageTips::sub_71010A87F0(s32 type) {
    if ((type | 1) != 19)
        return false;

    if (type == 18 && _3a8 == 19)
        type = 19;
    if (_3a8 == type)
        _3ac = type;
    else
        type = _3ac;
    return type != 29;
}

// 0x7100a00e74
void ScreenChangeController::m93(sead::Heap*) {
    _3610 = mLayout->createAnimatorAuto("Type", false);
}

// 0x7100a00ea8
void ScreenChangeController::m94() {
    if (isOpened())
        close(-4);
}

// 0x7100a041b4
void ScreenDemoStart::m93(sead::Heap*) {
    _3610 = mLayout->createAnimatorAuto("Decide", false);
}

// 0x7100a25d7c
bool sub_7100A25D7C(s32 kind) {
    switch (kind) {
    case 0:
        return ksys::gdt::getFlag_GuideP_ChallengePoint(false);
    case 1:
        return ksys::gdt::getFlag_GuideP_VisitMark(false);
    default:
        return true;
    }
}

// 0x7100a0e7fc
void ScreenKeyNum::open(s32 option) {
    if (mState != 1 && mState != 2 && ksys::StageInfo::sIsDungeon) {
        if (ksys::gdt::getSmallKeyNum(GameScene::getCurrentMapName(), false) < 1)
            return;
        if (sub_7100A98038(mId))
            return;
        Screen::open(option);
    }
}

// 0x7100a0e8a4
void ScreenKeyNum::m84() {
    _3610 = ksys::StageInfo::sIsDungeon ? ksys::gdt::getSmallKeyNum(GameScene::getCurrentMapName(), false) : 0;
    sub_7100AA930C(mLayout, "T_KeyNum_00", _3610, 0, 0);
}

// 0x7100a0e870
void ScreenKeyNum::m93(sead::Heap*) {
    _3618 = mLayout->createAnimatorAuto("Flash", false);
}

// 0x71009fb988
void ScreenAppSystemWindowNoBtn::m93(sead::Heap*) {
    _3610 = mLayout->createAnimatorAuto("FadeOut", false);
}

// 0x7100a321e8
void ScreenPauseMenuMantan::m93(sead::Heap*) {
    eui::ButtonGroup* group = mButtonGroup;
    for (eui::ListNode* node = group->mButtons.next; node != &group->mButtons; node = node->next)
        static_cast<eui::ButtonBase*>(eui::ControlBase::fromNode(node))->mFlags |= 0x20;
    mButtonGroup->_38 &= ~2;
}

// 0x7100a2c1ac
void ScreenPauseMenuEiketsu::m93(sead::Heap*) {
    eui::ButtonGroup* group = mButtonGroup;
    for (eui::ListNode* node = group->mButtons.next; node != &group->mButtons; node = node->next)
        static_cast<eui::ButtonBase*>(eui::ControlBase::fromNode(node))->mFlags |= 0x20;
    mButtonGroup->_38 &= ~2;
}

// 0x7100a2be98
void ScreenPauseMenuBG::m93(sead::Heap*) {
    mLayout->startAnimCloseImpl_(false, true);
}

// 0x7100a2bec8
void ScreenPauseMenuBG::m94() {
    if (_3610)
        x_2();
}

// 0x7100a0dfc8
void ScreenHomeMenuCapture::m93(sead::Heap*) {
    _3610 = sub_7100BEAFB0("Pa_LoadingIcon_00");
    if (_3610)
        _3610->startAnimCloseImpl_(false, true);
}

// 0x7100a0e00c
void ScreenHomeMenuCapture::m94() {
    if (!_3610)
        return;
    if (_3618) {
        if (_3610->_91 == 0)
            _3610->sub_7100BDDE7C(false, 0, true);
    } else if (_3610->_91 == 2) {
        _3610->startAnimCloseImpl_(false, false);
    }
}

// 0x7100a4de00
void ScreenShopBtnList5::m94() {
    x_2();
}

// 0x7100a4ca64
void ScreenShopBtnList20::m102(eui::AnimButton*) {
    _3868 = 0;
}

// 0x7100a502e4
void ScreenShopHorse::m99() {
    _36bc = 0;
}

// 0x7100a5061c
void ScreenShopHorse::m106(eui::AnimButton* button) {
    ksys::gdt::setFlag_Horse_SelectedIndex(button->mTag - 83, false);
    ksys::gdt::setFlag_Horse_IsSelected(true, false);
}

// 0x7100a2c28c
void ScreenPauseMenuEiketsu::m101() {
    _292 |= 0x20;
}

// 0x71009fc9e0
void ScreenAppSystemWindow::m101() {
    _3610 = 10;
}

// 0x7100a2807c
void ScreenMiniGame::m100() {
    _3650 = 0;
}

// 0x71009fc9ec
void ScreenAppSystemWindow::m106(eui::AnimButton* button) {
    if (!button->IsPlayDisableAnim())
        mButtonGroup->_38 &= ~2;
}

// 0x7100a060ac
void ScreenDLCWindow::m106(eui::AnimButton* button) {
    mButtonGroup->_38 &= ~2;
    if (button->mTag == 89)
        invokeSoundLink2Event_("mc_WindowClose");
}

// 0x7100a205fc
void ScreenMainShortCut::m99() {
    if (sub_7100AA948C())
        mStateMachine.changeState(&sUnk_71025ef170);
    else
        mStateMachine.changeState(&sUnk_71025ef290);
}

// 0x7100a0e054
void ScreenHomeMenuCapture::m98() {
    x_2();
    _3618 = 0;
    if (_3610)
        _3610->startAnimCloseImpl_(false, true);
}

// 0x7100a60678
void ScreenSystemWindowNoBtn::m93(sead::Heap*) {
    _3610 = mLayout->createAnimatorAuto("FadeOut", false);
    _3618 = mLayout->createAnimatorAuto("Type", false);
}

// 0x7100a286bc
void ScreenOPtext::m93(sead::Heap*) {
    _3610 = mLayout->createAnimatorAuto("Type", true);
    if (_3610)
        _3610->Stop(_3618);
}

// 0x7100a4a9c4
void ScreenSeekPadMenuBG::m93(sead::Heap*) {
    mLayout->startAnimCloseImpl_(false, true);
    _3610 = mLayout->tryCreateAnimatorAuto("Type", false);
    if (_3610)
        _3610->StopAtMax();
}

// 0x7100a4a8a8
void ScreenSeekPadMenuBG::sub_7100A4A8A8() {
    if (mLayout->_91 == 3 || mLayout->_91 == 0)
        mLayout->sub_7100BDDE7C(false, 1, true);
    if (auto* root = Root1::instance()) {
        const bool value = root->_30;
        _3618 = value;
        if (value)
            root->sub_7100899CA4(Root1::FlagIdx::_0, 1);
    }
}

// 0x7100a4a91c
void ScreenSeekPadMenuBG::sub_7100A4A91C() {
    if (u32(mLayout->_91 - 1) <= 1)
        mLayout->startAnimCloseImpl_(false, true);
    if (_3618) {
        if (auto* root = Root1::instance())
            root->sub_7100899CA4(Root1::FlagIdx::_0, 2);
    }
}

// 0x7100a4dd8c
void ScreenShopBtnList5::m93(sead::Heap*) {
    _3618 = mLayout->createAnimatorAuto("Type", true);
    if (_3618)
        _3618->StopAtMin();
    _3620 = mLayout->createAnimatorAuto("HaveNumOff", true);
    if (_3620)
        _3620->StopAtMin();
}

// 0x7100a00948
void ScreenChallengeWin::m93(sead::Heap*) {
    _3610 = sub_7100BEAFB0("Pa_ChallengeWin_00");
    if (!_3610)
        return;
    _3868 = _3610->tryCreateAnimatorAuto("Check", false);
    if (_3868)
        _3868->StopAtMin();
    _3870 = _3610->createAnimatorAuto("GuideOff", false);
    if (_3870)
        _3870->StopAtMin();
}

// 0x7100a00440
void ScreenBootUp::m94() {
    if (isOpened()) {
        if (mLayout->mPane)
            mLayout->mPane->SetVisible(false);
        close(-4);
    }
}

// 0x7100a40c58
void ScreenReadyGo::m94() {
    eui::Animator* animator = mLayout->mOpenAnimator;
    if (animator && animator->mFrame == static_cast<f32>(animator->GetFrameSize()))
        close(-4);
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

// 0x71009fb9bc
void ScreenAppSystemWindowNoBtn::m94() {
    if ((_291 & 2) || isOpened() ||
        (_3610 && _3610->mFrame == static_cast<f32>(_3610->GetFrameSize())))
        _292 |= 0x20;
}

// 0x7100a606c4
void ScreenSystemWindowNoBtn::m94() {
    if ((_291 & 2) || isOpened() ||
        (_3610 && _3610->mFrame == static_cast<f32>(_3610->GetFrameSize())))
        _292 |= 0x20;
}

// 0x7100a60650
void ScreenSystemWindowNoBtn::sub_7100A60650() {
    if (!_3610 || _3610->mRate != 0)
        return;
    _3610->PlayAuto(1.0f);
}

// 0x7100a0b63c
void ScreenHardModeTextDLC::m98() {
    eui::MessageString message;
    getMessage("LayoutMsg/SystemWindow_01", "T_DummyText_00", &message);
    setWidgetString(mLayout, "T_DummyText_00", message);
}

// 0x7100a322bc
void ScreenPauseMenuMantan::m98() {
    setReservedBoxCursorNode(findBoxCursorNodeByTag(137));
}

// 0x7100a69b28
void ScreenTitle::sub_7100A69B28() {
    _363c = -1;
    if (isE3DemoMode())
        _3680 = 0x200;
    mButtonGroup->_38 |= 2;
}

// 0x7100a69aec
void ScreenTitle::sub_7100A69AEC() {
    _3610->PlayAuto(1.0f);
    _363c = -1;
    _3680 = -1;
}

// 0x7100a69b6c
bool ScreenTitle::sub_7100A69B6C() {
    return _3610->mFrame == static_cast<f32>(_3610->GetFrameSize());
}

// 0x7100a1fa64
void ScreenMainShortCut::sub_7100A1FA64(s32 value) {
    _38c8 = value;
    _38cc = 0;
}

// 0x7100a1fabc
void ScreenMainShortCut::sub_7100A1FABC() {
    _38c8 = -1;
    _38cc = 1;
}

// 0x7100a1fa74
bool ScreenMainShortCut::sub_7100A1FA74() {
    if (_38c8 == -1)
        return false;
    return _37a0->mFrame == static_cast<f32>(_37a0->GetFrameSize());
}

// 0x7100a21908
bool ScreenMainShortCut::sub_7100A21908() {
    return _37a0 && _37a0->mFrame == 0;
}

// 0x7100a22074
void ScreenMainShortCut::m160() {
    _3720 = -1;
    if (_3790)
        _3790->sub_710093F594(false);
}

// 0x7100a2192c
// NON_MATCHING: the original forms the address of the byte at 0x3700 (`add x8, x19, x8; ldrb w8, [x8]`) instead of
// the register-offset load
void ScreenMainShortCut::m155() {
    sub_7100A20AD4();
    sub_7100A20CBC();
    getPlayerActor(nullptr);
    sub_7100A2063C();
    auto* player = static_cast<ksys::act::PlayerBase*>(getPlayerActor(nullptr));
    if (player && player->_c48.isOnBit(28) && _3700.isOnBit(2))
        sub_7100A209E4();
    if (_38cc == 0) {
        mStateMachine.changeState(&sUnk_71025ef1d0);
    } else if (!sub_7100AA948C()) {
        mStateMachine.changeState(&sUnk_71025ef290);
    }
}

// 0x7100a22094
void ScreenMainShortCut::m163() {
    switch (_38cc) {
    case 1:
        _3798->PlayAuto(-1.0f);
        _37a0->PlayAuto(-1.0f);
        mStateMachine.changeState(&sUnk_71025ef170);
        break;
    case 0:
        mStateMachine.changeState(&sUnk_71025ef1d0);
        break;
    }
}

// 0x7100a22134
void ScreenMainShortCut::m167() {
    if (sub_7100AA948C())
        mStateMachine.changeState(&sUnk_71025ef170);
}

// 0x710109db58
void ScreenBoxCursorTV::m93(sead::Heap*) {
    if (eui::LayoutEx* layout = sub_7100BEAFB0("Pa_Cursor_00")) {
        _300 = layout->tryCreateAnimatorAuto("Type", true);
        if (_300)
            _300->StopAtMin();
    }
}

// 0x7100a4b344
void ScreenShopBtnList15::m100() {
    if (eui::LayoutEx* layout = sub_7100BEAFB0("Pa_GuideA_00")) {
        if (layout->_91 == 1 || layout->_91 == 2)
            layout->startAnimCloseImpl_(false, false);
    }
    if (eui::LayoutEx* layout = sub_7100BEAFB0("Pa_GuideB_00")) {
        if (layout->_91 == 1 || layout->_91 == 2)
            layout->startAnimCloseImpl_(false, false);
    }
}

// 0x7100a4df4c
void ScreenShopBtnList5::m100() {
    if (eui::LayoutEx* layout = sub_7100BEAFB0("Pa_GuideA_00")) {
        if (layout->_91 == 1 || layout->_91 == 2)
            layout->startAnimCloseImpl_(false, false);
    }
    if (eui::LayoutEx* layout = sub_7100BEAFB0("Pa_GuideB_00")) {
        if (layout->_91 == 1 || layout->_91 == 2)
            layout->startAnimCloseImpl_(false, false);
    }
    if (_3628)
        invokeSoundLink2Event_("mc_Close");
}

// 0x7100a4de04
void ScreenShopBtnList5::m98() {
    _3628 = 0;
    if (eui::LayoutEx* layout = sub_7100BEAFB0("Pa_GuideA_00")) {
        if (layout->_91 == 3 || layout->_91 == 0)
            layout->sub_7100BDDE7C(false, 0, true);
    }
    if (eui::LayoutEx* layout = sub_7100BEAFB0("Pa_GuideB_00")) {
        if (layout->_91 == 3 || layout->_91 == 0)
            layout->sub_7100BDDE7C(false, 0, true);
    }
    UiShopMgr::instance()->sub_710098411C(_3610->_30c);
    UiShopMgr::instance()->_b4 = true;
}

namespace {
// inline-only in the original; name is a guess (the m107 slots of ShopBtnList15 / ShopBtnList20 / PauseMenu repeat it)
inline void clearDecideWindowAlpha(eui::AnimButton* button) {
    if (!button)
        return;
    nn::ui2d::Pane* pane = button->mLayout->mPane->FindPaneByName("W_Decide_00", true);
    if (!pane)
        return;
    const s32 count = pane->GetMaterialCount();
    for (s32 i = 0; i < count; ++i)
        sub_7100AA1CB8(pane->GetMaterial(i), 0);
}
}  // namespace

// 0x7100a56d08
void ScreenSousaGuide::sub_7100A56D08() {
    if (_3610 == -1)
        return;
    _3610 = -1;
    _3618.sub_71009348D0(true);
}

// 0x7100a4b10c
void ScreenShopBtnList15::sub_7100A4B10C(s32 index) {
    moveBoxCursorByTag_(static_cast<u32>(index) < 15 ? index + 122 : 122);
}

// 0x7100a4b468
void ScreenShopBtnList15::m106(eui::AnimButton*) {
    UiShopMgr::instance()->sub_71009843AC(nullptr);
}

// 0x7100a4b47c
void ScreenShopBtnList15::m107(eui::AnimButton* button) {
    clearDecideWindowAlpha(button);
}

// 0x7100a4ca6c
void ScreenShopBtnList20::m107(eui::AnimButton* button) {
    if (UiShopMgr::instance()->_cd)
        clearDecideWindowAlpha(button);
    else
        _3868 = button;
}

// 0x7100a388ec
void ScreenPauseMenu::m107(eui::AnimButton* button) {
    if (u32(button->mTag - 9) <= 0x3b && _3618 == 15)
        clearDecideWindowAlpha(button);
}

// 0x7100a6bc80
void ScreenWolfLinkHeartGauge::m93(sead::Heap* heap) {
    eui::LayoutEx* layout = sub_7100BEAFB0("Pa_HeartGauge_00");
    if (!layout)
        return;
    _3610 = new (heap, 8) Unk_7102474be8;
    if (_3610) {
        _3610->sub_7100934B94(layout, true);
        _3610->set95c(true);
    }
}

// 0x7100a16d24
void ScreenMainScreenMS::m93(sead::Heap* heap) {
    _3610 = mLayout->createAnimatorAuto("BlurIn", true);
    _3618 = mLayout->createAnimatorAuto("CenterHeart", true);
    eui::LayoutEx* layout = sub_7100BEAFB0("Pa_HeartGauge_00");
    if (!layout)
        return;
    _3620 = new (heap, 8) Unk_7102474be8;
    if (_3620) {
        _3620->sub_7100934B94(layout, true);
        _3620->set95c(true);
        _3620->set958(0.0f);
    }
    _3628 = findPane_("Pa_HeartGauge_00");
}

// 0x7100a16828
void ScreenMainScreenHeartIchigekiDLC::m93(sead::Heap* heap) {
    _3610 = mLayout->createAnimatorAuto("CenterHeart", true);
    eui::LayoutEx* layout = sub_7100BEAFB0("Pa_HeartGauge_00");
    if (!layout)
        return;
    _3618 = new (heap, 8) Unk_7102474be8;
    if (_3618) {
        _3618->sub_7100934B94(layout, false);
        _3618->set95c(true);
        _3618->set958(0.0f);
    }
    _3620 = findPane_("Pa_HeartGauge_00");
    sub_7100A168F0();
}

// 0x7100a17010
void ScreenMainScreenMS::m100() {
    _3620->set944(_3620->get948());
    _3620->sub_710093515C(getAnimationStep_());
}

// 0x7100a16aec
void ScreenMainScreenHeartIchigekiDLC::m100() {
    _3618->set944(_3618->get948());
    _3618->sub_710093515C(getAnimationStep_());
}

// 0x7100a16adc
void ScreenMainScreenHeartIchigekiDLC::sub_7100A16ADC() {
    if (_3618)
        _3618->playAnimator8e0();
}

// 0x7100a6bcf8
void ScreenWolfLinkHeartGauge::m94() {
    if (!_3610)
        return;
    auto* info = Unk_71025d6578::instance();
    _3610->set948(sub_7100949D18(info->_68));
    if (info->_70 & 6)
        _3610->playAnimator918();
    if ((info->_70 & 1) && !_3610->isAnimator8e0Playing())
        _3610->playAnimator8e0();
    _3610->sub_710093515C(getAnimationStep_());
}

// 0x7100a6be1c
void ScreenWolfLinkHeartGauge::sub_7100A6BE1C() {
    if (_3610)
        _3610->sub_71009359E8();
}

// 0x71010a8840
void ScreenMessageTips::m93(sead::Heap*) {
    _318.sub_71010A7CA4(sub_7100BEAFB0("Pa_Tips_00"));
    _318.sub_71010A7EDC(sub_7100BEAFB0("Pa_TipsAmiibo_00"), mLayout->createAnimatorAuto("Type", false));
    _300 = sub_7100BEAFB0("Pa_ABtn_00");
    if (_300)
        _308 = _300->tryCreateAnimatorAutoWithWarning("DecideOut", true);
}

// 0x71010a8aa0
void ScreenMessageTips::m98() {
    if (_300) {
        if (_308)
            _308->StopAtMin();
        _300->startAnimCloseImpl_(false, true);
    }
    _310 = false;
}

// 0x71010a8af0
void ScreenMessageTips::m100() {
    _3a8 = 29;
}

// 0x7100a22124
void ScreenMainShortCut::m166() {
    m80(false);
}

// 0x7100a45fc0
bool ScreenSaveTransferWindow::sub_7100A45FC0() {
    return SaveSystem::instance()->sub_7100914D48();
}

// 0x7100a43294
void ScreenSaveTransferWindow::m106(eui::AnimButton* button) {
    const s32 tag = button->mTag;
    if (u32(tag - 0x8b) <= 2)
        _366c = tag;
    _3630->setFlag10(false);
    _3638->setFlag10(false);
    _3640->setFlag10(false);
}

// 0x7100a4357c
void ScreenSaveTransferWindow::m154() {
    _3670 = mStateMachine.getState();
    _366c = -1;
    s32 old_index = _3668;
    _3668 = 1;
    if (old_index == -1) {
        sub_7100A428D0();
        return;
    }
    _3618->StopAtMax();
    _3620->PlayAuto(1.0f);
    _3630->setFlag10(false);
    _3638->setFlag10(false);
    _3640->setFlag10(false);
}

// 0x7100a43924
void ScreenSaveTransferWindow::m178() {
    _3670 = mStateMachine.getState();
    _366c = -1;
    s32 old_index = _3668;
    _3668 = 1;
    if (old_index == -1) {
        sub_7100A428D0();
        return;
    }
    _3618->StopAtMax();
    _3620->PlayAuto(1.0f);
    _3630->setFlag10(false);
    _3638->setFlag10(false);
    _3640->setFlag10(false);
}

// 0x7100a43a10
void ScreenSaveTransferWindow::m182() {
    _3670 = mStateMachine.getState();
    _366c = -1;
    s32 old_index = _3668;
    _3668 = 2;
    if (old_index == -1) {
        sub_7100A428D0();
        return;
    }
    _3618->StopAtMax();
    _3620->PlayAuto(1.0f);
    _3630->setFlag10(false);
    _3638->setFlag10(false);
    _3640->setFlag10(false);
}

// 0x7100a45da0
void ScreenSaveTransferWindow::sub_7100A45DA0() {
    _366c = -1;
    s32 old_index = _3668;
    _3668 = 0;
    if (old_index == -1) {
        sub_7100A428D0();
        return;
    }
    _3618->StopAtMax();
    _3620->PlayAuto(1.0f);
    _3630->setFlag10(false);
    _3638->setFlag10(false);
    _3640->setFlag10(false);
}

// 0x7100a46124
void ScreenSaveTransferWindow::sub_7100A46124() {
    _366c = -1;
    s32 old_index = _3668;
    _3668 = 1;
    if (old_index == -1) {
        sub_7100A428D0();
        return;
    }
    _3618->StopAtMax();
    _3620->PlayAuto(1.0f);
    _3630->setFlag10(false);
    _3638->setFlag10(false);
    _3640->setFlag10(false);
}

// 0x7100a46268
void ScreenSaveTransferWindow::sub_7100A46268() {
    _366c = -1;
    s32 old_index = _3668;
    _3668 = 4;
    if (old_index == -1) {
        sub_7100A428D0();
        return;
    }
    _3618->StopAtMax();
    _3620->PlayAuto(1.0f);
    _3630->setFlag10(false);
    _3638->setFlag10(false);
    _3640->setFlag10(false);
}

// 0x7100a45fd0
void ScreenSaveTransferWindow::sub_7100A45FD0() {
    if ((SaveSystem::instance()->_3c | 1) != 7)
        mStateMachine.changeState(&sUnk_71025f2de0);
}

// 0x7100a46004
void ScreenSaveTransferWindow::sub_7100A46004() {
    _366c = -1;
    s32 old_index = _3668;
    _3668 = 0;
    if (old_index == -1) {
        sub_7100A428D0();
        return;
    }
    _3618->StopAtMax();
    _3620->PlayAuto(1.0f);
    _3630->setFlag10(false);
    _3638->setFlag10(false);
    _3640->setFlag10(false);
}

// 0x7100a44544
void ScreenSaveTransferWindow::sub_7100A44544() {
    _366c = -1;
    s32 old_index = _3668;
    _3668 = 1;
    if (old_index == -1) {
        sub_7100A428D0();
        return;
    }
    _3618->StopAtMax();
    _3620->PlayAuto(1.0f);
    _3630->setFlag10(false);
    _3638->setFlag10(false);
    _3640->setFlag10(false);
}

// 0x7100a44458
void ScreenSaveTransferWindow::sub_7100A44458() {
    _3670 = mStateMachine.getState();
    _366c = -1;
    s32 old_index = _3668;
    _3668 = 1;
    if (old_index == -1) {
        sub_7100A428D0();
        return;
    }
    _3618->StopAtMax();
    _3620->PlayAuto(1.0f);
    _3630->setFlag10(false);
    _3638->setFlag10(false);
    _3640->setFlag10(false);
}

// 0x7100a44878
void ScreenSaveTransferWindow::sub_7100A44878() {
    _3670 = mStateMachine.getState();
    _366c = -1;
    s32 old_index = _3668;
    _3668 = 1;
    if (old_index == -1) {
        sub_7100A428D0();
        return;
    }
    _3618->StopAtMax();
    _3620->PlayAuto(1.0f);
    _3630->setFlag10(false);
    _3638->setFlag10(false);
    _3640->setFlag10(false);
}

// 0x7100a45080
void ScreenSaveTransferWindow::sub_7100A45080() {
    _3670 = mStateMachine.getState();
    _366c = -1;
    s32 old_index = _3668;
    _3668 = 1;
    if (old_index == -1) {
        sub_7100A428D0();
        return;
    }
    _3618->StopAtMax();
    _3620->PlayAuto(1.0f);
    _3630->setFlag10(false);
    _3638->setFlag10(false);
    _3640->setFlag10(false);
}

// 0x7100a43690
void ScreenSaveTransferWindow::m158() {
    _366c = -1;
    s32 old_index = _3668;
    _3668 = 1;
    if (old_index == -1) {
        sub_7100A428D0();
        return;
    }
    _3618->StopAtMax();
    _3620->PlayAuto(1.0f);
    _3630->setFlag10(false);
    _3638->setFlag10(false);
    _3640->setFlag10(false);
}

// 0x7100a44394
void ScreenSaveTransferWindow::m210() {
    _366c = -1;
    s32 old_index = _3668;
    _3668 = 0;
    if (old_index == -1) {
        sub_7100A428D0();
        return;
    }
    _3618->StopAtMax();
    _3620->PlayAuto(1.0f);
    _3630->setFlag10(false);
    _3638->setFlag10(false);
    _3640->setFlag10(false);
}

// 0x7100a43734
void ScreenSaveTransferWindow::m159() {
    switch (_366c) {
    case 0x8d:
        mStateMachine.changeState(&sUnk_71025f2000);
        break;
    case 0x8c:
        mStateMachine.changeState(&sUnk_71025f2d80);
        break;
    }
}

// 0x71009d0ee4
void ScreenAmiiboWindow::m98() {
    _3610 = 4;
    x_2();
    registerController_();
    mButtonGroup->_38 &= ~2;
}

// 0x71009d0f2c
void ScreenAmiiboWindow::m99() {
    if (_3689) {
        if (_3668)
            _3668->DownOff(false);
    } else if (_3688) {
        if (_3660)
            _3660->DownOff(false);
    } else {
        mButtonGroup->_38 |= 2;
    }
}

// 0x71009d0f78
void ScreenAmiiboWindow::m100() {
    if (_368a && (ksys::gdt::getFlag_AmiiboItemOnOff(false) & 1) != _368b)
        SaveSystem::instance()->sub_71009145F8();
}

// 0x71009d0fd4
void ScreenAmiiboWindow::m101() {
    _3614 = 3;
    _368a = 0;
    _3668 = nullptr;
    _3660 = nullptr;
    sub_7100AA8784();
}

// 0x71009d0ff0
void ScreenAmiiboWindow::m106(eui::AnimButton* button) {
    if (_3658 == button) {
        if (_3678)
            _3678->PlayAuto(1.0f);
        if (_3650)
            _3650->setFlag10(false);
        if (_3658)
            _3658->setFlag10(false);
        _3688 = 0;
        _3689 = 0;
    } else {
        mButtonGroup->_38 &= ~2;
    }
}

// 0x71009d107c
void ScreenAmiiboWindow::m107(eui::AnimButton* button) {
    if (_3640 == button || _3648 == button) {
        _3610 = 2;
    } else if (_3650 == button) {
        _3610 = 1;
    } else if (_3658 == button) {
        switch (_3614) {
        case 1:
            ksys::gdt::setFlag_AmiiboItemOnOff(true);
            break;
        case 2:
            ksys::gdt::setFlag_AmiiboItemOnOff(false);
            break;
        }
    }
    if (_3658 != button)
        close(-1);
}

// 0x7100a02ca0
void ScreenControllerWindow::m99() {
    if (_3851) {
        close(-1);
    } else if (!_3850) {
        mButtonGroup->_38 |= 2;
        if (_3618)
            _3618->sub_710093F594(true);
    }
}

// 0x7100a02cec
void ScreenControllerWindow::m100() {
    mButtonGroup->_38 &= ~2;
    if (_3618)
        _3618->sub_710093F594(false);
}

s32 ScreenDLCWindow::sResult = 2;

// 0x7100a05f94
s32 ScreenDLCWindow::sub_7100A05F94() {
    const s32 result = sResult;
    sResult = 2;
    return result;
}

// 0x7100a060e0
void ScreenDLCWindow::m107(eui::AnimButton* button) {
    if (button->IsPlayDisableAnim()) {
        mButtonGroup->_38 |= 2;
        return;
    }
    switch (button->mTag) {
    case 89:
        sResult = 1;
        break;
    case 90:
        sResult = 0;
        break;
    }
    if (sResult)
        close(-1);
}

s32 ScreenPauseMenuMantan::sResult = 5;

// 0x7100a3219c
s32 ScreenPauseMenuMantan::takeResult() {
    const s32 result = sResult;
    sResult = 5;
    return result;
}

// 0x7100a32310
void ScreenPauseMenuMantan::m107(eui::AnimButton* button) {
    switch (button->mTag) {
    case 138:
        sResult = _3610;
        break;
    case 137:
        sResult = 4;
        break;
    }
    close(-1);
}

// 0x7100a25638
void ScreenMessageGet::m99() {
    if (sub_7100A9760C()) {
        sub_7100A9732C();
        return;
    }
    if (sub_7100A97198()) {
        sub_7100A96EB8();
        return;
    }
    if (sub_7100A97DDC(0)) {
        sub_7100A97860(0);
        return;
    }
    if (sub_7100A97DDC(1)) {
        sub_7100A97860(1);
        return;
    }
    if (sub_7100A97DDC(2)) {
        sub_7100A97860(2);
        return;
    }
    if (sub_7100A97DDC(3)) {
        sub_7100A97860(3);
        return;
    }
    if (_3640) {
        _3640->sub_7100BDDE7C(false, 0, true);
        _3650 = 1;
    }
}

// 0x7100a32228
void ScreenPauseMenuMantan::m94() {
    if ((mButtonGroup->_38 & 2) && (_292 & 0x40) && sub_71010AA9D0() && mUIController &&
        mUIController->isTrig(2)) {
        sub_71010AA894();
        if (auto* button = mButtonGroup->FindButtonByTag(137))
            button->Down();
        else
            close(-1);
    }
}

// 0x7100a2c1ec
void ScreenPauseMenuEiketsu::m94() {
    if ((mButtonGroup->_38 & 2) && (_292 & 0x40) && sub_71010AA9D0() && mUIController &&
        mUIController->isTrig(2)) {
        if (auto* button = sub_7100A480B4("Pa_Btn_00"))
            button->Down();
    }
}

// 0x71009fc930
void ScreenAppSystemWindow::m100() {
    if (auto* home = sead::DynamicCast<ScreenAppHome>(eui::ScreenMgr::instance()->getScreen(ScreenId::AppHome)))
        home->sub_71009DE1C8();
}

// 0x71009fc77c
void ScreenAppSystemWindow::m94() {
    if ((mButtonGroup->_38 & 2) && isOpened() && (_292 & 0x40) && sub_71010AA9D0() && mUIController &&
        mUIController->isTrig(2)) {
        sub_71010AA894();
        if (_3638)
            _3638->DownOff(false);
        else
            close(-1);
    }
}

// 0x71009e9f10
bool ScreenAppMap::sub_71009E9F10() {
    return _3610 ? _3610->sub_71009A9438() : false;
}

// 0x71009e9f20
bool ScreenAppMap::sub_71009E9F20() {
    if (_3ad1)
        return !sub_71009E9F48();
    return false;
}

}  // namespace uking::ui

namespace uking::ui {

// NON_MATCHING: the recovered intrusive-list loop folds the node-to-entry offset; the original retains it.
bool ScreenMainScreen3D::sub_7100A11D34(s32 id) {
    if (!(_292 & 2))
        return false;
    for (const auto& entry : mEntries) {
        if (entry.mId == id)
            return true;
    }
    return false;
}

void ScreenAppHome::sub_71009DD7D4() { sub_71009DCF18(6); }
void ScreenAppHome::sub_71009DD7DC() { sub_71009DCF18(5); }
void ScreenAppHome::sub_71009DD7E4() { sub_71009DCF18(7); }
void ScreenAppHome::sub_71009DD814() { sub_71009DCF18(0); }

// 0x71009dd81c
bool ScreenAppHome::sub_71009DD81C() const {
    return _3610._30 && (_3610._30->mFlags & 1);
}

// 0x71009ddfb8
void ScreenAppHome::m99() {
    if (_3811)
        sub_7100AA86EC(1, false);
}

// 0x71009dc77c
void ScreenAppHome::sub_71009DC77C(s32 index, Unk_PaneTransform* value) {
    if (u32(index) <= 3)
        _38a0[index]._10 = value;
}

// 0x7100a432fc
void ScreenSaveTransferWindow::m107(eui::AnimButton*) {
    if (mStateMachine.getState()->getId() == (&sUnk_71025f2d80)->getId())
        _3678 |= 1 << Flag(Flag::_1);
}

// 0x7100a43ac0
void ScreenSaveTransferWindow::m183() {
    switch (_366c) {
    case 0x8b:
        mStateMachine.changeState(&sUnk_71025f2240);
        break;
    case 0x8c:
        mStateMachine.changeState(&sUnk_71025f2d20);
        break;
    case 0x8d:
        if ((1 << Flag(Flag::_4)) & _3678) {
            mStateMachine.changeState(&sUnk_71025f23c0);
        } else {
            _3678 |= 1 << Flag(Flag::_5);
            mStateMachine.changeState(&sUnk_71025f2300);
        }
        break;
    }
}

// 0x7100a44508
void ScreenSaveTransferWindow::m215() {
    switch (_366c) {
    case 0x8d:
        mStateMachine.changeState(&sUnk_71025f2540);
        break;
    case 0x8c:
        mStateMachine.changeState(&sUnk_71025f2d80);
        break;
    }
}

// 0x7100a445e8
void ScreenSaveTransferWindow::m219() {
    switch (_366c) {
    case 0x8d:
        mStateMachine.changeState(&sUnk_71025f25a0);
        break;
    case 0x8c:
        mStateMachine.changeState(&sUnk_71025f2d80);
        break;
    }
}

// 0x7100a44928
void ScreenSaveTransferWindow::m235() {
    switch (_366c) {
    case 0x8d:
        mStateMachine.changeState(&sUnk_71025f2720);
        break;
    case 0x8c:
        mStateMachine.changeState(&sUnk_71025f2d20);
        break;
    }
}

// 0x7100a45130
void ScreenSaveTransferWindow::m259() {
    switch (_366c) {
    case 0x8d:
        mStateMachine.changeState(&sUnk_71025f2960);
        break;
    case 0x8c:
        mStateMachine.changeState(&sUnk_71025f2d20);
        break;
    }
}

// 0x7100a44ddc
void ScreenSaveTransferWindow::m250() {
    _366c = -1;
    s32 old_index = _3668;
    _37a0 = 0;
    _3668 = 5;
    if (old_index == -1) {
        sub_7100A428D0();
        return;
    }
    _3618->StopAtMax();
    _3620->PlayAuto(1.0f);
    _3630->setFlag10(false);
    _3638->setFlag10(false);
    _3640->setFlag10(false);
}

// 0x7100a45b6c
void ScreenSaveTransferWindow::m279() {
    if (SaveSystem::instance()->loadDone())
        mStateMachine.changeState(&sUnk_71025f2b40);
}

// 0x7100a45bb8
void ScreenSaveTransferWindow::m282() {
    _379c = 0;
    SaveSystem::instance()->sub_7100914D48();
}

// 0x7100a45e40
void ScreenSaveTransferWindow::m287() {
    if (_366c == 0x8b) {
        _3678 |= 1 << Flag(Flag::_2);
        mStateMachine.changeState(&sUnk_71025f2d80);
    }
}

// 0x7100a45f80
// NON_MATCHING: the original tests `_3760 == 0` then `== 4` with cmp / ccmp; clang folds the two tests into a different compare order
void ScreenSaveTransferWindow::m291() {
    if (_3760 == 0 || _3760 == 4)
        mStateMachine.changeState(&sUnk_71025f2de0);
    else if (_3760 == 3)
        mStateMachine.changeState(&sUnk_71025f2c60);
}

// 0x7100a46234
void ScreenSaveTransferWindow::m310() {
    _3678 |= 1 << Flag(Flag::_1);
}

}  // namespace uking::ui
