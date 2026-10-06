#include "Game/AI/Action/actionActorInfoToGameDataInt.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

ActorInfoToGameDataInt::ActorInfoToGameDataInt(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ActorInfoToGameDataInt::~ActorInfoToGameDataInt() = default;

bool ActorInfoToGameDataInt::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ActorInfoToGameDataInt::oneShot_() {
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
                s32 value = 0;
                if (mParameterName_d.include("Life")) {
                    auto* life = actor->getLife();
                    value = life ? *life : 1;
                }
                gdt->setS32(value, mGameDataIntToName_d);
            }
        }
    }
    return true;
}

void ActorInfoToGameDataInt::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mGameDataIntToName_d, "GameDataIntToName");
    getDynamicParam(&mParameterName_d, "ParameterName");
}

}  // namespace uking::action
