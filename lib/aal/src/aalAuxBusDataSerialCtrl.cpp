#include "aal/aalAuxBusDataSerialCtrl.h"

#include <prim/seadScopedLock.h>

namespace aal {

void AuxBusDataCtrl::drawInformation(sead::DrawContext*, sead::TextWriter*) const {}

AuxBusDataSerialCtrl::AuxBusDataSerialCtrl() : mStopFader(1.0f) {
    mStopFader.moveTo(1.0f, 0.0f);
}

AuxBusDataSerialCtrl::~AuxBusDataSerialCtrl() {
    execOnBusDisconnect();
    if (mChild)
        mChild->execOnBusDisconnect();
    mHasPendingChild = false;
    mPendingChild = nullptr;
    mChild = nullptr;
}

void AuxBusDataSerialCtrl::calc() {
    AuxBusDataCtrl* child;
    {
        sead::ScopedLock<sead::Mutex> lock(&mChildMutex);
        child = mChild;
    }

    if (child) {
        if (child->getState() == 4) {
            if (mIsConnected) {
                sead::ScopedLock<sead::Mutex> lock(&mChildMutex);
                mHasPendingChild = true;
                mPendingChild = nullptr;
            } else {
                if (mChild)
                    mChild->execOnBusDisconnect();
                mHasPendingChild = false;
                mPendingChild = nullptr;
                mChild = nullptr;
            }
        }
        child->calc();
    }
    mStopFader.calc();
}

void AuxBusDataSerialCtrl::stop(f32 time) {
    mState = 3;
    mStopFader.moveTo(0.0f, time);
}

bool AuxBusDataSerialCtrl::execOnBusConnect() {
    mIsConnected = true;
    if (mChild)
        return mChild->execOnBusConnect();
    mStopFader.moveTo(1.0f, 0.0f);
    mState = 2;
    return true;
}

void AuxBusDataSerialCtrl::execOnBusDisconnect() {
    if (mChild)
        mChild->execOnBusDisconnect();
    mIsConnected = false;
    mState = 0;
}

}  // namespace aal
