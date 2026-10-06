#include "Game/AI/Action/actionNPCChangeBoots.h"
#include "Game/Actor/actModelMaterialUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

NPCChangeBoots::NPCChangeBoots(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCChangeBoots::~NPCChangeBoots() = default;

bool NPCChangeBoots::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCChangeBoots::loadParams_() {
    getDynamicParam(&mBootsNumber_d, "BootsNumber");
}

// NON_MATCHING: register allocation of the four flags (the original keeps is_boot in w23 ... is_lower_141 in w19).
bool NPCChangeBoots::oneShot_() {
    bool is_boot = false;
    bool is_skin_leg = false;
    bool is_lower_049 = false;
    bool is_lower_141 = false;
    switch (*mBootsNumber_d) {
    case 0:
        is_boot = true;
        break;
    case 1:
        is_skin_leg = true;
        break;
    case 2:
        is_lower_049 = true;
        break;
    case 3:
        is_lower_141 = true;
        break;
    }
    if (auto* model = mActor->getModel()) {
        {
            const auto key = model->searchMaterial("Mt_Boot");
            if (key.isValid())
                act::setMaterialVisible(model, key, is_boot);
        }
        {
            const auto key = model->searchMaterial("Mt_Skin_Leg");
            if (key.isValid())
                act::setMaterialVisible(model, key, is_skin_leg);
        }
        {
            const auto key = model->searchMaterial("Mt_Lower_049");
            if (key.isValid())
                act::setMaterialVisible(model, key, is_lower_049);
        }
        {
            const auto key = model->searchMaterial("Mt_Lower_141");
            if (key.isValid())
                act::setMaterialVisible(model, key, is_lower_141);
        }
    }
    return true;
}

}  // namespace uking::action
