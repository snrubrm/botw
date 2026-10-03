#include "Game/AI/AI/aiDemoRootAI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceAIProgram.h"

namespace uking::ai {

DemoRootAI::DemoRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DemoRootAI::~DemoRootAI() {
    for (auto*& child : _38) {
        if (child) {
            delete child;
            child = nullptr;
        }
    }
    _38.freeBuffer();
}

bool DemoRootAI::initChildren(const ksys::AIDefSet& set, sead::Heap* heap) {
    auto& indices = mActor->getParam()->getRes().mAIProgram->getDemoAiActionIndices();
    if (indices.size() == 0)
        return true;
    return initChildren_(indices.size(), nullptr, indices, heap);
}

bool DemoRootAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DemoRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 &= 4;
    _4a = 0;
    setFinished();
    sub_7100D62598();
}

void DemoRootAI::calc_() {
    sub_7100D62598();
    for (auto* child : _38) {
        if (child)
            child->calc();
    }
    _4a = _48;
    _48 = 0;
}

void DemoRootAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DemoRootAI::loadParams_() {}

void DemoRootAI::getCurrentName(sead::BufferedSafeString* name,
                                ksys::act::ai::ActionBase* last) const {
    name->appendWithFormat("/%s{", getName());
    if (getCurrentChild())
        getCurrentChild()->getCurrentName(name, last);
    name->appendWithFormat(",");
    if (this != last) {
        for (auto* child : _38) {
            if (child)
                child->getCurrentName(name, last);
            name->appendWithFormat(",");
        }
    }
    name->appendWithFormat("}");
}

}  // namespace uking::ai
