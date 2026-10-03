#include "Game/AI/AI/aiMessageReceiveCheckBasic.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

MessageReceiveCheckBasic::MessageReceiveCheckBasic(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MessageReceiveCheckBasic::~MessageReceiveCheckBasic() = default;

bool MessageReceiveCheckBasic::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MessageReceiveCheckBasic::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71004A4D84();
    mFlags.set(Flag::Changeable);
}

void MessageReceiveCheckBasic::sub_71004A4D84() {
    m36();
    changeChild("オフ");
}

void MessageReceiveCheckBasic::calc_() {
    if (isCurrentChild("オフ")) {
        if (m34()) {
            m36();
            changeChild("オン");
        }
    } else if (isCurrentChild("オン") && m35()) {
        m36();
        changeChild("オフ");
    }
}

void MessageReceiveCheckBasic::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MessageReceiveCheckBasic::loadParams_() {}

bool MessageReceiveCheckBasic::m34() {
    return _38;
}

bool MessageReceiveCheckBasic::m35() {
    auto* child = getCurrentChild();
    return child->isFinished() || child->isFailed();
}

void MessageReceiveCheckBasic::m36() {
    _38 = false;
}

bool MessageReceiveCheckBasic::handleMessage_(const ksys::Message& message) {
    if (message.getType() == 0x8000004) {
        _38 = true;
        return true;
    }
    return false;
}

}  // namespace uking::ai
