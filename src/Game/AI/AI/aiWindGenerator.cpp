#include "Game/AI/AI/aiWindGenerator.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

WindGenerator::WindGenerator(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool WindGenerator::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WindGenerator::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (actor->hasPlacementLinkForBasicSig()) {
        if (actor->checkBasicSig())
            m35();
        else
            m34();
    } else {
        m35();
    }
}

void WindGenerator::calc_() {
    auto* actor = mActor;
    auto* child = getCurrentChild();
    if (!actor->hasPlacementLinkForBasicSig())
        return;

    if (isCurrentChild("待機") && child->isChangeable() && actor->checkBasicSig()) {
        m35();
        return;
    }

    if (isCurrentChild("風制御") && child->isFinished())
        m34();
}

void WindGenerator::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WindGenerator::loadParams_() {}

void WindGenerator::m34() {
    changeChild("待機");
}

void WindGenerator::m35() {
    ksys::act::ai::InlineParamPack params;
    changeChild("風制御");
}

bool WindGenerator::handleMessage_(const ksys::Message& message) {
    if (message.getType().value == 0x3000003) {
        if (isCurrentChild("待機"))
            return false;
        m34();
        return true;
    }

    if (message.getType().value == 0x3000004) {
        if (mActor->hasPlacementLinkForBasicSig())
            return false;
        if (!isCurrentChild("待機"))
            return false;
        m35();
        return true;
    }

    return false;
}

}  // namespace uking::ai
