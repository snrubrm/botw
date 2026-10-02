#include "Game/AI/AI/aiEnemyCalledAppear.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

EnemyCalledAppear::EnemyCalledAppear(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyCalledAppear::~EnemyCalledAppear() = default;

bool EnemyCalledAppear::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyCalledAppear::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* awareness = mActor->getAwareness()) {
        awareness->sub_7100D7EBE0(1.5f);
        awareness->enable();
    }
    m34();
}

void EnemyCalledAppear::m34() {
    changeChild("出現");
}

void EnemyCalledAppear::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (!m35())
            setFinished();
    } else {
        child->isChangeable();
    }

    auto* actor = mActor;
    if (auto* awareness = actor->getAwareness()) {
        Unk_7102451678 filter;
        if (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
            sub_71005D8DE8(actor, entry->mLink, &entry->_58, nullptr);
            actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
        }
    }
}

void EnemyCalledAppear::leave_() {
    if (auto* awareness = mActor->getAwareness()) {
        awareness->sub_7100D7EBE0(1.0f);
        awareness->disable();
    }
}

void EnemyCalledAppear::loadParams_() {}

bool EnemyCalledAppear::m35() {
    return false;
}

}  // namespace uking::ai
