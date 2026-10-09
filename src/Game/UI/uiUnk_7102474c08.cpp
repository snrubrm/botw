#include "Game/UI/uiUnkTiny.h"
#include "Game/AI/aiUnk_7100736460.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ui {

Unk_7102474c08::Unk_7102474c08() = default;

// 0x7100935f90
Unk_7102474c08::~Unk_7102474c08() = default;

// 0x7100935f98
void Unk_7102474c08::sub_7100935F98(sead::Heap* heap, eui::LayoutEx* layout) {
    if (!layout)
        return;
    mGauge = new (heap, 8) Unk_7102474be8;
    mGauge->sub_7100934B94(layout, false);
    mGauge->set95c(true);
    _10 = Unk_71025d6578::instance();
    layout->startAnimCloseImpl_(false, true);
    _1c.init(0.3f);
}

// NON_MATCHING: state-load reuse and switch/branch scheduling differ.
// 0x7100936034
void Unk_7102474c08::sub_7100936034(f32 step) {
    if (!_10 || !mGauge)
        return;
    if (_10->_38 & 0x2000) {
        sub_7100936254(step, false);
        return;
    }
    if (mGauge->_8->_91 == 0 || mGauge->_8->_91 == 3)
        return;
    bool track = true;
    if (_18) {
        if (_10->_3c == 0)
            return;
        if ((_10->_3c == 10 || _10->_3c == 13) && !(_10->_38 & 0x800)) {
            if (_10->_38 & 0x20) {
                _19 = 1;
            } else if (_19 == 2) {
                if (_1c.updateAndCheckEnded()) {
                    _19 = 0;
                    track = false;
                }
            } else if (_19 == 1 && mGauge->_944 == mGauge->_948) {
                _19 = 2;
                _1c.reset();
            }
        } else if (_19 != 0) {
            _19 = 0;
            track = false;
        }
    }
    sub_71009364AC(true);
    sub_7100936590(track);
    if (_10->_38 & 6)
        mGauge->playAnimator918();
    sub_710093666C();
    if (!_18) {
        if (_10->_38 & 0x100) {
            mGauge->playAnimator910();
        } else if (!(_10->_38 & 0x80) && mGauge->isAnimator910Playing()) {
            mGauge->stopAnimator910(0.0f);
        }
    }
    if (mGauge)
        mGauge->sub_710093515C(step);
    if (_18) {
        switch (_10->_3c) {
        case 5:
        case 9:
        case 11:
            _10->_48 = true;
            break;
        case 7:
            if (!mGauge || mGauge->_944 == mGauge->_948)
                _10->_48 = true;
            break;
        case 8:
            if (!mGauge->_95d && !mGauge->_95e)
                _10->_48 = true;
            break;
        case 10:
            if ((!mGauge || mGauge->_944 == mGauge->_948) && !_19)
                _10->_48 = true;
            break;
        }
    }
}

// NON_MATCHING: the gauge receiver is cached across the quarter-heart lookup.
// 0x7100936254
void Unk_7102474c08::sub_7100936254(f32 step, bool first) {
    if (!mGauge || !_10)
        return;
    _19 = false;
    sub_71009364AC(false);
    mGauge->sub_71009358CC(sead::Mathi::min(sub_7100949CE8(_10->_30), 30), false);
    if (_10->_38 & 6)
        mGauge->playAnimator918();
    else
        mGauge->stopAnimator918();
    if (!_18) {
        if (_10->_38 & 0x100) {
            mGauge->playAnimator910();
        } else if (!(_10->_38 & 0x80) && mGauge->isAnimator910Playing()) {
            mGauge->stopAnimator910(0.0f);
        }
    }
    if (!(_10->_38 & 1)) {
        mGauge->stopAnimator8e0();
    } else if (first) {
        f32 frame = 0.0f;
        if (_18) {
            auto* screen = sead::DynamicCast<ScreenPauseMenuInfo>(
                eui::ScreenMgr::instance()->getScreen(ScreenId::PauseMenuInfo));
            if (screen)
                frame = screen->sub_7100A31C64();
        } else {
            auto* screen = sead::DynamicCast<ScreenMainScreen>(
                eui::ScreenMgr::instance()->getScreen(ScreenId::MainScreen));
            if (screen)
                frame = screen->sub_7100A1AB68();
        }
        mGauge->playAnimator8e0FromFrame(frame);
    } else {
        sub_710093666C();
    }
    if (mGauge)
        mGauge->sub_710093515C(step);
}

// 0x71009364ac
void Unk_7102474c08::sub_71009364AC(bool first) {
    mGauge->set948(sub_7100949D18(_10->_2c));
    if (!first || (_10->_38 & 0x800))
        mGauge->set944(mGauge->_948);
    if (!_19)
        mGauge->set940(sub_7100949CE8(_10->_34));
    if (!_18) {
        if (_10->_38 & 4) {
            mGauge->_95c = true;
        } else if (mGauge->_95c && mGauge->_944 == mGauge->_948) {
            mGauge->_95c = false;
            _10->sub_710094BE30();
        }
        if ((_10->_38 & 0x400) && !mGauge->_95c)
            _10->sub_710094BE30();
    }
}

// 0x7100936590
void Unk_7102474c08::sub_7100936590(bool first) {
    const s32 count = sead::Mathi::min(sub_7100949CE8(_10->_30), 30);
    if (!first) {
        mGauge->sub_71009358CC(count, false);
    } else if (_10->_38 & 8) {
        mGauge->sub_71009358CC(count, true);
        mGauge->set944(mGauge->_948);
        if (_18)
            mGauge->_8->mScreen->invokeSoundLink2Event_("mc_HeartMaxUp");
    } else if (_10->_38 & 0x10) {
        mGauge->sub_71009358CC(count, true);
        if (_18)
            mGauge->_8->mScreen->invokeSoundLink2Event_("mc_HeartMaxDown");
    } else if (_10->_38 & 0x40) {
        mGauge->sub_71009358CC(count, false);
    }
}

// 0x710093666c
void Unk_7102474c08::sub_710093666C() {
    if (mGauge->isAnimator8e0Playing() || !(_10->_38 & 1))
        return;
    mGauge->playAnimator8e0();
    if (_10->_3a) {
        if (!dlc::isPlayingOneHitObliteratorQuest())
            playSound("mc_HeartAlert_S", nullptr);
    } else {
        playSound("mc_HeartAlert_L", nullptr);
        _10->_3a = true;
    }
    if (_18) {
        auto* screen = sead::DynamicCast<ScreenMainScreen>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::MainScreen));
        if (screen)
            screen->sub_7100A1DE08();
    }
}

void Unk_7102474c08::sub_71009367C4(bool first) {
    if (!mGauge)
        return;
    auto* layout = mGauge->_8;
    if (first) {
        if (layout->_91 != 3 && layout->_91 != 0)
            return;
        layout->sub_7100BDDE7C(false, 0, true);
    } else {
        layout->sub_7100BDDE7C(false, 1, true);
    }
    if (!_18)
        mGauge->_95c = false;
}

void Unk_7102474c08::sub_7100936830(bool first) {
    if (!mGauge)
        return;
    auto* layout = mGauge->_8;
    if (first) {
        if (layout->_91 != 1 && layout->_91 != 2)
            return;
        layout->startAnimCloseImpl_(false, false);
    } else {
        layout->startAnimCloseImpl_(false, true);
    }
    mGauge->set944(mGauge->get948());
    mGauge->sub_710093515C(1.0f);
}

bool Unk_7102474c08::sub_71009368A4() const {
    return mGauge && mGauge->_8->_91 == 2;
}

bool Unk_7102474c08::sub_71009368C8() const {
    return mGauge && mGauge->_8->_91 == 0;
}

void Unk_7102474c08::sub_71009368EC(f32 step) {
    if (!mGauge || !mGauge->_95c)
        return;
    mGauge->set944(mGauge->get948());
    mGauge->_95c = false;
    mGauge->sub_710093515C(step);
}

void Unk_7102474c08::sub_710093694C() {
    if (mGauge)
        mGauge->sub_71009359E8();
}

f32 Unk_7102474c08::sub_710093695C() const {
    return mGauge ? mGauge->getAnimator8e0Frame() : 0.0f;
}

}  // namespace uking::ui
