#pragma once

#include "Game/Actor/actEnemy.h"
#include "Game/AI/AI/aiCreateActorWithTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// inline-only in the original; name is a guess. The same inlined sequence (the actor's Enemy
// target list, entry 0 unless the list has no target with a matching flag, else the dummy link)
// repeats in KokkoAngry::enter_ / calc_ / m35 and KokkoAngryTargetSelect::enter_. NON_MATCHING in
// all four: the original keeps `enemy + 0xd70` in a register and addresses entry 0 as `+ 8` of it,
// ours folds it to `enemy + 0xd78` (one extra add / register).
inline ksys::act::BaseProcLink* getKokkoTargetLink(ksys::act::Actor* actor) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        auto& targets = enemy->_d70;
        if (!targets.sub_71002DCCBC(-1))
            return &targets.mEntries[0].link;
    }
    return &ksys::act::sUnk_71026505e0;
}

class KokkoAngry : public CreateActorWithTarget {
    SEAD_RTTI_OVERRIDE(KokkoAngry, CreateActorWithTarget)
public:
    explicit KokkoAngry(const InitArg& arg);
    ~KokkoAngry() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    sead::Vector3f m35() override;
    bool m36() override;
    void m37(ksys::act::BaseProcHandle* handle) override;

protected:
};

}  // namespace uking::ai
