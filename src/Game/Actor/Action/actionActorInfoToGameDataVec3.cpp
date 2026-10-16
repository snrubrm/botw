#include "Game/Actor/Action/actionActorInfoToGameDataVec3.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

ActorInfoToGameDataVec3::ActorInfoToGameDataVec3(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ActorInfoToGameDataVec3::~ActorInfoToGameDataVec3() = default;

bool ActorInfoToGameDataVec3::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original tail-duplicates the parameter / setVec3f block into each unique-name branch.
bool ActorInfoToGameDataVec3::oneShot_() {
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
                sead::Vector3f value = sead::Vector3f::zero;
                if (!mUniqueName_d.isEmpty() && !(mUniqueName_d == "NoUniqueName")) {
                    if (actor->getUniqueName() && !(mUniqueName_d == actor->getUniqueName()))
                        continue;
                }
                if (mParameterName_d.include("Pos"))
                    value = actor->getMtx().getTranslation();
                else if (mParameterName_d.include("Vel"))
                    value = actor->getVelocity();
                gdt->setVec3f(value, mGameDataVec3fToName_d);
            }
        }
    }
    return true;
}

void ActorInfoToGameDataVec3::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mGameDataVec3fToName_d, "GameDataVec3fToName");
    getDynamicParam(&mParameterName_d, "ParameterName");
}

}  // namespace uking::action
