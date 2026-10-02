#include "Game/AI/AI/aiPreyChemicalDeadReaction.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

PreyChemicalDeadReaction::PreyChemicalDeadReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyChemicalDeadReaction::~PreyChemicalDeadReaction() = default;

bool PreyChemicalDeadReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: block placement (the original moves the 焼死/死亡 tail calls up)
void PreyChemicalDeadReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* mgr = sub_710072BA90(mActor)) {
        switch (mgr->getField54()) {
        case -1:
        case 0:
        case 1:
        case 2:
        case 5:
        case 29:
        case 30:
        case 31: {
            const s32 type = mgr->getField50();
            if (type == 11) {
                ksys::act::ai::InlineParamPack child_params;
                child_params.addBool(false, "IsEnableThrowOffAttack", -1);
                changeChild("感電死", &child_params);
                return;
            }
            if (type == 10) {
                ksys::act::ai::InlineParamPack child_params;
                child_params.addBool(false, "IsEnableThrowOffAttack", -1);
                changeChild("凍死", &child_params);
                return;
            }
            if (type == 9) {
                changeChild("焼死");
                return;
            }
            break;
        }
        case 3: {
            ksys::act::ai::InlineParamPack child_params;
            child_params.addBool(false, "IsEnableThrowOffAttack", -1);
            changeChild("凍死", &child_params);
            return;
        }
        case 4: {
            ksys::act::ai::InlineParamPack child_params;
            child_params.addBool(false, "IsEnableThrowOffAttack", -1);
            changeChild("感電死", &child_params);
            return;
        }
        case 18:
            changeChild("焼死");
            return;
        default:
            break;
        }
    }
    changeChild("死亡");
}

void PreyChemicalDeadReaction::calc_() {}

void PreyChemicalDeadReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PreyChemicalDeadReaction::loadParams_() {}

}  // namespace uking::ai
