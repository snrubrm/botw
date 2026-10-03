#include "Game/AI/Action/actionFireWood.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

FireWood::FireWood(const InitArg& arg) : FireWoodBase(arg) {}

FireWood::~FireWood() = default;

bool FireWood::init_(sead::Heap* heap) {
    return FireWoodBase::init_(heap);
}

void FireWood::enter_(ksys::act::ai::InlineParamPack* params) {
    FireWoodBase::enter_(params);
}

void FireWood::leave_() {
    FireWoodBase::leave_();
}

void FireWood::loadParams_() {
    FireWoodBase::loadParams_();
    mActor->getRootAi()->getAITreeVariable2(&mIsDrop_a, "IsDrop");
}

void FireWood::calc_() {
    FireWoodBase::calc_();
    if (_40) {
        auto* manager = ksys::evt::Manager::instance();
        if (manager && !manager->_1d2b8 && !(manager->_1d2f4 & 0x100)) {
            _40 = false;
            if (auto* damage_mgr = mActor->getDamageMgr())
                damage_mgr->mField_34 = 0;
        }
    }
}

}  // namespace uking::action
