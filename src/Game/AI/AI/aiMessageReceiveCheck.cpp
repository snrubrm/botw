#include "Game/AI/AI/aiMessageReceiveCheck.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

MessageReceiveCheck::MessageReceiveCheck(const InitArg& arg) : MessageReceiveCheckBasic(arg) {}

MessageReceiveCheck::~MessageReceiveCheck() = default;

bool MessageReceiveCheck::init_(sead::Heap* heap) {
    return MessageReceiveCheckBasic::init_(heap);
}

// NON_MATCHING: register assignment (the original computes the lock address before `this + 0x80`)
void MessageReceiveCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!handlePendingChildChange()) {
        auto* actor = mActor;
        _80._18.y(actor);
        sub_71005E02E0(actor, &_80, nullptr);
        sub_71004A4D84();
    }
    mFlags.set(Flag::Changeable);
}


void MessageReceiveCheck::calc_() {
    MessageReceiveCheckBasic::calc_();
}

void MessageReceiveCheck::leave_() {
    MessageReceiveCheckBasic::leave_();
}

bool MessageReceiveCheck::m34() {
    switch (*mMsgType_s) {
    case 0:
        return _48._30;
    case 1:
        return _38;
    default:
        return false;
    }
}

void MessageReceiveCheck::m36() {
    _48.x();
    _38 = false;
}

bool MessageReceiveCheck::handleMessage_(const ksys::Message* message) {
    switch (*mMsgType_s) {
    case 0:
        return _48.m2(*message);
    case 1:
        if (message->getType() == 0x8000004) {
            _38 = true;
            return true;
        }
        return false;
    default:
        return false;
    }
}

void MessageReceiveCheck::handlePendingChildChange_() {
    changeChild(mPendingChildIdx);
}

void MessageReceiveCheck::loadParams_() {
    MessageReceiveCheckBasic::loadParams_();
    getStaticParam(&mMsgType_s, "MsgType");
}

}  // namespace uking::ai
