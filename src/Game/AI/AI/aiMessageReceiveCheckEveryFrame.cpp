#include "Game/AI/AI/aiMessageReceiveCheckEveryFrame.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

MessageReceiveCheckEveryFrame::MessageReceiveCheckEveryFrame(const InitArg& arg)
    : MessageReceiveCheckBasic(arg) {}

MessageReceiveCheckEveryFrame::~MessageReceiveCheckEveryFrame() = default;

bool MessageReceiveCheckEveryFrame::init_(sead::Heap* heap) {
    return MessageReceiveCheckBasic::init_(heap);
}

void MessageReceiveCheckEveryFrame::enter_(ksys::act::ai::InlineParamPack* params) {
    MessageReceiveCheckBasic::enter_(params);
}

void MessageReceiveCheckEveryFrame::calc_() {
    MessageReceiveCheckBasic::calc_();
    m36();
}

void MessageReceiveCheckEveryFrame::leave_() {
    MessageReceiveCheckBasic::leave_();
}

void MessageReceiveCheckEveryFrame::loadParams_() {
    MessageReceiveCheckBasic::loadParams_();
    getStaticParam(&mMsgType_s, "MsgType");
}

bool MessageReceiveCheckEveryFrame::m35() {
    return !m34();
}

bool MessageReceiveCheckEveryFrame::handleMessage_(const ksys::Message& message) {
    if (*mMsgType_s == 0 && message.getType().value == 0x3000009) {
        _38 = true;
        return true;
    }
    return false;
}

}  // namespace uking::ai
