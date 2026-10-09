#include "Game/AI/Action/actionSandwormTackleMove.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

const sead::SafeString& sub_71002CCC20(s32 idx);

// Adjacent target-list helper family used by the two Sandworm tackle actions.
namespace uking::action {

bool Unk_SandwormTackleMoveList::sub_71F6DC(sead::Heap* heap) {
    auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor);
    if (!enemy)
        return false;

    auto* target = new (heap, 8) Unk_SandwormTackleTarget(enemy);
    if (!target)
        return false;
    mTargets.pushBack(target);
    target->_48 = sub_71002CCC20(0);
    if (!target->sub_710073E45C(heap, sead::SafeString::cEmptyString))
        return false;

    auto* target2 = new (heap, 8) Unk_SandwormTackleTarget(enemy);
    if (!target2)
        return false;
    mTargets.pushBack(target2);
    target2->_48 = sub_71002CCC20(1);
    return target2->sub_710073E45C(heap, sead::SafeString::cEmptyString);
}

// Deletes all targets (called from the owners' destructors).
void Unk_SandwormTackleMoveList::sub_71F858() {
    while (mTargets.size() > 0) {
        if (auto* target = mTargets.popBack())
            delete target;
    }
}

void Unk_SandwormTackleMoveList::sub_71FEFC() {
    for (s32 i = 0, n = mTargets.size(); i < n; ++i) {
        auto* target = mTargets.at(i);
        target->_38.reset();
        target->_58 = 0;
    }
}

bool Unk_SandwormTackleMoveList::sub_71FF70(const ksys::MessageAck* ack) {
    for (s32 i = 0, n = mTargets.size(); i < n; ++i) {
        if (mTargets.at(i)->sub_710073E5E0(ack)) {
            if (mTargets(i)->_58 == 2)
                xlinkSearchAndEmit(mActor, "BombEatAngry", 2, nullptr);
            return true;
        }
    }
    return false;
}

bool Unk_SandwormTackleMoveList::sub_71FEB4() const {
    for (s32 i = 0, n = mTargets.size(); i < n; ++i) {
        if (mTargets(i)->_58 == 1)
            return true;
    }
    return false;
}

}  // namespace uking::action
