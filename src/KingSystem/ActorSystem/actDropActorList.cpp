#include "KingSystem/ActorSystem/actDropMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actBaseProcHeapMgr.h"

namespace ksys::act {

DropActorList::DropActorList() : mHead(nullptr) {}

DropActorList::~DropActorList() {
    sub_710124A704();
}

void DropActorList::sub_710124A704() {
    auto* node = mHead;
    while (node) {
        auto* next = node->next;
        node->~Node();
        node = next;
    }
    mHead = nullptr;
}

bool DropActorList::sub_710124A770() const {
    for (auto* node = mHead; node; node = node->next) {
        if (!node->handle.isProcReady() && !node->handle.hasProcCreationFailed())
            return false;
    }
    return true;
}

void DropActorList::sub_710124A7C0(Actor* actor, bool clear_fade_in) {
    auto* node = mHead;
    while (node) {
        auto* next = node->next;
        if (auto* drop_actor = node->releaseActor()) {
            sead::Matrix34f matrix;
            calculateDropPosition(&matrix, actor, node->_18);
            drop_actor->setMatrix(matrix, nullptr);
            if (clear_fade_in)
                drop_actor->clearFadeInCreate();
        }
        node->~Node();
        node = next;
    }
    mHead = nullptr;
}

void DropActorList::pushFront(Node* node) {
    node->next = mHead;
    mHead = node;
}

DropActorList::Node::Node() : next(nullptr), _18(0) {}

DropActorList::Node::~Node() {
    // The pool keeps the node storage alive; the handle's member destructor runs after freeNode.
    handle.deleteProc();
    DropMgr::instance()->freeNode(this);
}

Actor* DropActorList::Node::releaseActor() {
    if (handle.isProcReady())
        return sead::DynamicCast<Actor>(handle.releaseAndWakeProc());
    if (handle.hasProcCreationFailed())
        handle.deleteProcIfFailed();
    else if (handle.isAllocatedOrFailed())
        handle.deleteProc();
    return nullptr;
}

void DropActorList::Node::createActor(const sead::SafeString& name, InstParamPack* params, s32 mode) {
    ActorCreator::instance()->requestCreateActor(name.cstr(), BaseProcHeapMgr::instance()->getHeap(),
                                                &handle, params, nullptr, 2);
    _18 = mode;
}

}  // namespace ksys::act
