#include "Game/UI/uiUnkTiny.h"
#include "Game/UI/euiLayoutEx.h"

namespace uking::ui {

Unk_7102474c08::Unk_7102474c08() = default;

// 0x7100935f90
Unk_7102474c08::~Unk_7102474c08() = default;

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
