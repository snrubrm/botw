#include "Game/AI/AI/aiDieSelectChemicalPlus.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

DieSelectChemicalPlus::DieSelectChemicalPlus(const InitArg& arg) : DieSelect(arg) {}

DieSelectChemicalPlus::~DieSelectChemicalPlus() = default;

bool DieSelectChemicalPlus::init_(sead::Heap* heap) {
    return DieSelect::init_(heap);
}

void DieSelectChemicalPlus::enter_(ksys::act::ai::InlineParamPack* params) {
    DieSelect::enter_(params);
}

void DieSelectChemicalPlus::calc_() {
    DieSelect::calc_();
}

void DieSelectChemicalPlus::leave_() {
    DieSelect::leave_();
}

void DieSelectChemicalPlus::loadParams_() {
    DieSelect::loadParams_();
}

void DieSelectChemicalPlus::m34(s32 a2, s32 a3, bool a4, bool a5) {
    switch (a3) {
    case -1:
    case 0:
    case 1:
    case 2:
    case 5:
    case 0x1d:
    case 0x1e:
    case 0x1f:
        switch (a2) {
        case 9:
        case 0x13: {
            *mActor->getLife() = 0;
            auto* damage_mgr = sub_710072BA90(mActor);
            if (damage_mgr && damage_mgr->checkDamageFlags(12))
                changeChild("焼特効死");
            else
                changeChild("焼死");
            return;
        }
        case 10: {
            *mActor->getLife() = 0;
            auto* damage_mgr = sub_710072BA90(mActor);
            if (damage_mgr && damage_mgr->checkDamageFlags(12))
                changeChild("凍特効死");
            else
                changeChild("凍死");
            return;
        }
        case 11:
            *mActor->getLife() = 0;
            changeChild("感電死");
            return;
        }
        break;
    case 3: {
        *mActor->getLife() = 0;
        auto* damage_mgr = sub_710072BA90(mActor);
        if (damage_mgr && damage_mgr->checkDamageFlags(12))
            changeChild("凍特効死");
        else
            changeChild("凍死");
        return;
    }
    case 4:
        *mActor->getLife() = 0;
        changeChild("感電死");
        return;
    case 0x12: {
        *mActor->getLife() = 0;
        auto* damage_mgr = sub_710072BA90(mActor);
        if (damage_mgr && damage_mgr->checkDamageFlags(12))
            changeChild("焼特効死");
        else
            changeChild("焼死");
        return;
    }
    }
    DieSelect::m34(a2, a3, a4, a5);
}

}  // namespace uking::ai
