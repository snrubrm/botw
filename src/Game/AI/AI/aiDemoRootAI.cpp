#include "Game/AI/AI/aiDemoRootAI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Resource/Actor/resResourceAIProgram.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Thread/MessageAck.h"

namespace uking::ai {

// 0x7100d630ac (placeholder name; declared only; define in its own TU, not here, or it inlines into
// leave_): releases the event-context list at RootAi + 0x140 (takes that object; void* because the
// nested SomeStruct type is private).
void sub_7100D630AC(void* context);
// 0x7100d6300c (placeholder name; declared only): walks the DemoAiRequest list at the RootAi + 0x140
// context and advances each node (takes the context and the actor).
void sub_7100D6300C(void* context, ksys::act::Actor* actor);

bool DemoRootAI::sub_7100D62394(DemoAiRequest* request) {
    const s32 idx = getChildIdx("Demo_Idling");
    if (idx != 0xffff) {
        ksys::act::ai::InlineParamPack local;
        auto* pack = request == nullptr ? &local : &request->mParams;
        pack->addBool(false, "DisablePhysics", -1);
        changeChild(idx, pack);
    }
    return true;
}

bool DemoRootAI::sub_7100D62D18(const sead::SafeString& name) {
    const s32 idx = getChildIdx(name);
    if (idx == 0xffff)
        return false;
    auto* child = getChild(idx);
    return child ? child->isTriggerAction() : false;
}

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

// NON_MATCHING: the original keeps a `num < 1` guard and a peeled `buffer[0] = nullptr` store with a second
// `num == 1` guard before the unrolled clearing loop (tried: early-return guards, loop from 1, `i <= num - 1`;
// our compiler merges or drops the redundant guards); everything else matches.
bool DemoRootAI::init_(sead::Heap* heap) {
    s32 num = mActor->getRootAi()->getAt();
    if (num <= 0) {
        if (!ksys::act::hasTag(mActor, 0xFD5643B5u))
            return true;
        num = 16;
    }
    if (!_38.tryAllocBuffer(num, heap))
        return false;
    for (s32 i = 0; i < num; ++i)
        _38(i) = nullptr;
    return true;
}

void DemoRootAI::sub_7100D62598() {
    if ((_48 & 4) != 0) {
        const s32 idx = getChildIdx("Demo_VisibleOff");
        if (idx != 0xffff) {
            changeChild(idx, nullptr);
            const s32 count = _38.size();
            if (count >= 1) {
                for (s32 i = 0; i <= count - 1; ++i) {
                    auto& slot = _38[i];
                    auto* action = slot;
                    if (!action)
                        continue;
                    action->leave();
                    action->hasUpdateForPreDeleteCb();
                    action->onPreDelete();
                    delete action;
                    slot = nullptr;
                }
            }
        }
    }
    if ((_48 & 8) != 0) {
        sub_7100D62394(nullptr);
        const s32 count = _38.size();
        if (count >= 1) {
            for (s32 i = 0; i <= count - 1; ++i) {
                auto& slot = _38[i];
                auto* action = slot;
                if (!action)
                    continue;
                action->leave();
                action->hasUpdateForPreDeleteCb();
                action->onPreDelete();
                delete action;
                slot = nullptr;
            }
        }
    }
    auto* root_ai = mActor->getRootAi();
    sub_7100D6300C(root_ai->_140, mActor);
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

// NON_MATCHING: the original keeps a separate `ldrh; orr` in each flag case (they are not sunk into one
// shared `_48 |= value`); logic identical
// NON_MATCHING: the original keeps a separate `ldrh; orr` in each flag case (only the final store is
// shared); ours sinks the load into one shared tail. Jump-table structure and all calls match.
bool DemoRootAI::handleMessage_(const ksys::Message* message) {
    if (!message)
        return false;
    const auto& type = message->getType();
    if (message->getBrokerId() == 0xffffffff) {
        switch (type) {
        case 0x800006:
        case 0x800007:
        case 0x800008:
            return true;
        case 0x800010:
            _48 |= 4;
            break;
        case 0x800011:
            _48 |= 8;
            break;
        case 0x800012:
            _48 |= 1;
            break;
        case 0x800013:
            _48 |= 2;
            break;
        }
    }
    for (auto* child : _38) {
        if (child && child->handleMessage(*message))
            return true;
    }
    return false;
}

bool DemoRootAI::handleAck_(const ksys::MessageAck* ack) {
    if (!ack)
        return false;
    if (ack->getType() == 0x80000c)
        return true;
    for (auto* child : _38) {
        if (child && child->handleAck(*ack))
            return true;
    }
    return false;
}

// NON_MATCHING: the actor temporary at the tail lives in x1 in the original, x8 here
// (register allocation only; the loop, all calls and the tail call match exactly).
void DemoRootAI::leave_() {
    const s32 count = _38.size();
    if (count >= 1) {
        for (s32 i = 0; i <= count - 1; ++i) {
            auto& slot = _38[i];
            auto* action = slot;
            if (!action)
                continue;
            action->leave();
            action->hasUpdateForPreDeleteCb();
            action->onPreDelete();
            delete action;
            slot = nullptr;
        }
    }
    auto* root_ai = mActor->getRootAi();
    sub_7100D630AC(root_ai->_140);
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
