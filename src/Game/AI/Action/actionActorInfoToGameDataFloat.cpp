#include "Game/AI/Action/actionActorInfoToGameDataFloat.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

ActorInfoToGameDataFloat::ActorInfoToGameDataFloat(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ActorInfoToGameDataFloat::~ActorInfoToGameDataFloat() = default;

bool ActorInfoToGameDataFloat::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ActorInfoToGameDataFloat::oneShot_() {
    auto* gdt = ksys::gdt::Manager::instance();
    if (!gdt) {
        setFailed();
        mFlags.set(Flag::Changeable);
        return false;
    }

    ksys::act::BaseProcMgr::ProcIteratorContext context(
        *ksys::act::BaseProcMgr::instance(),
        ksys::act::BaseProcMgr::ProcFilter::Sleeping | ksys::act::BaseProcMgr::ProcFilter::Initializing |
            ksys::act::BaseProcMgr::ProcFilter::SkipAccessCheck);
    while (auto* proc = context.next()) {
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc)) {
            if (mActorName_d == proc->getName()) {
                f32 value = 0.0f;
                if (mParameterName_d.include("DepthInWater"))
                    value = actor->getDepthInWater();
                gdt->setF32(value, mGameDataFloatToName_d);
            }
        }
    }
    return true;
}

void ActorInfoToGameDataFloat::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mGameDataFloatToName_d, "GameDataFloatToName");
    getDynamicParam(&mParameterName_d, "ParameterName");
}

}  // namespace uking::action
