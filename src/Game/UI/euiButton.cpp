#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"

namespace eui {

// 0x7100bd7168
ButtonBase::ButtonBase() = default;

// inline-only in the original; name is a guess (see the header)
void ButtonBase::linkToGroup() {
    if (mNode.isLinked())
        return;
    ButtonGroup* group = mLayout->mScreen->mButtonGroup;
    group->mPending.linkNext(&mNode);
}

// inline-only in the original; name is a guess (see the header)
void ButtonBase::pushRequest(Request request) {
    bool found = false;
    for (s32 i = 0; i < mQueueCount; ++i) {
        if (mQueue[i] == request) {
            mQueueCount = i + 1;
            found = true;
            break;
        }
    }
    if (!found && mQueueCount < 4) {
        mQueue[mQueueCount] = request;
        mQueueCount = mQueueCount + 1;
    }
    linkToGroup();
}

// inline-only in the original; name is a guess (see the header)
void ButtonBase::popRequest() {
    if (mQueueCount < 1)
        return;
    for (s32 i = 0; i < mQueueCount - 1; ++i)
        mQueue[i] = mQueue[i + 1];
    mQueueCount = mQueueCount - 1;
}

// inline-only in the original; name is a guess (see the header)
void ButtonBase::processRequests() {
    if (mQueueCount == 0)
        return;
    bool handled;
    switch (mQueue[0]) {
    case kRequestOn:
        handled = ProcessOn();
        break;
    case kRequestOff:
        handled = ProcessOff();
        break;
    case kRequestDown:
        handled = ProcessDown();
        break;
    case kRequestCancel:
        handled = ProcessCancel();
        break;
    default:
        return;
    }
    if (handled)
        popRequest();
}

// 0x7100bd7428
void ButtonBase::Update(f32) {
    processRequests();
    switch (mState) {
    case kStartOn:
        if (UpdateOn()) {
            FinishOn();
            processRequests();
        }
        break;
    case kStartOff:
        if (UpdateOff()) {
            FinishOff();
            processRequests();
        }
        break;
    case kStartDown:
        if (UpdateDown()) {
            FinishDown();
            processRequests();
        }
        break;
    case kCancel:
        if (UpdateCancel()) {
            FinishCancel();
            processRequests();
        }
        break;
    default:
        break;
    }
}

// 0x7100bd71b4
void ButtonBase::On() {
    if ((mFlags & 0x11) != 0x11)
        return;
    pushRequest(kRequestOn);
}

// 0x7100bd7240
void ButtonBase::Off() {
    if (!(mFlags & 2))
        return;
    pushRequest(kRequestOff);
}

// 0x7100bd72cc
void ButtonBase::Down() {
    if ((mFlags & 0x14) != 0x14)
        return;
    pushRequest(kRequestDown);
}

// 0x7100bd7360
void ButtonBase::Cancel() {
    if (!(mFlags & 8))
        return;
    pushRequest(kRequestCancel);
}

// 0x7100bd73ec
void ButtonBase::ForceOff() {
    mQueueCount = 0;
    setState(kOff);
}

// 0x7100bd7400
void ButtonBase::ForceOn() {
    mQueueCount = 0;
    setState(kOn);
}

// 0x7100bd7414
void ButtonBase::ForceDown() {
    mQueueCount = 0;
    setState(kDown);
}

// 0x7100bd77f0
void ButtonBase::setFlag10(bool on) {
    mFlags = on ? (mFlags | 0x10) : (mFlags & ~0x10);
}

// 0x7100bd7810
bool ButtonBase::ProcessOn() {
    bool handled = true;
    switch (mState) {
    case kOff:
    case kStartOff:
        StartOn();
        changeState(kStartOn);
        handled = true;
        break;
    case kStartDown:
    case kCancel:
        handled = false;
        break;
    default:
        break;
    }
    return handled;
}

// 0x7100bd7884
bool ButtonBase::ProcessOff() {
    bool handled = true;
    switch (mState) {
    case kStartOn:
    case kOn:
    case kDown:
        StartOff();
        changeState(kStartOff);
        handled = true;
        break;
    case kStartDown:
        handled = false;
        break;
    default:
        break;
    }
    return handled;
}

// 0x7100bd78f8
bool ButtonBase::ProcessDown() {
    switch (mState) {
    case kOff:
    case kStartOff:
        StartOn();
        changeState(kStartOn);
        return false;
    case kStartOn:
    case kCancel:
        return false;
    case kOn:
        StartDown();
        changeState(kStartDown);
        return true;
    default:
        return true;
    }
}

// 0x7100bd798c
bool ButtonBase::ProcessCancel() {
    switch (mState) {
    case kOff:
        return true;
    case kStartOn:
        return true;
    case kStartOff:
        return true;
    case kOn:
        return true;
    case kStartDown:
        return false;
    case kDown:
        StartCancel();
        changeState(kCancel);
        return true;
    case kCancel:
        return true;
    default:
        return true;
    }
}

// 0x7100bd7a1c
void ButtonBase::FinishOn() {
    changeState(kOn);
}

// 0x7100bd7a2c
void ButtonBase::FinishOff() {
    changeState(kOff);
}

// 0x7100bd7a3c
void ButtonBase::FinishDown() {
    changeState(kDown);
}

// 0x7100bd7a4c
void ButtonBase::FinishCancel() {
    changeState(kOff);
}

// 0x7100bd7a5c
void ButtonBase::changeState(State state) {
    mState = state;
}

// 0x7100bd7a64
void ButtonBase::setState(State state) {
    mState = state;
}

// 0x7100bd7a6c
bool ButtonBase::IsDowning() const {
    if ((mState & 0xfe) == kStartDown)
        return true;
    for (s32 i = 0; i < mQueueCount; ++i) {
        if (mQueue[i] == kRequestDown)
            return true;
    }
    return false;
}

}  // namespace eui
