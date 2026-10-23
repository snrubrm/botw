#include "KingSystem/ActorSystem/actReaction.h"

namespace ksys::act {

bool Reaction::Unk1::sub_7100EC6DD0(Actor* actor) {
    auto& reactions = mReactions;
    const sead::CoreId core = sead::CoreInfo::getCurrentCoreId();
    return reactions.queue(actor, core);
}

}  // namespace ksys::act
