#include "Game/AI/AI/aiChuchuDieSelect.h"
#include "Game/AI/aiUnk_71006F5B14.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::ai {

ChuchuDieSelect::ChuchuDieSelect(const InitArg& arg) : DieSelectChemicalPlus(arg) {}

ChuchuDieSelect::~ChuchuDieSelect() = default;

bool ChuchuDieSelect::init_(sead::Heap* heap) {
    return DieSelectChemicalPlus::init_(heap);
}

void ChuchuDieSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    DieSelectChemicalPlus::enter_(params);
}

void ChuchuDieSelect::calc_() {
    DieSelectChemicalPlus::calc_();
}

void ChuchuDieSelect::leave_() {
    DieSelectChemicalPlus::leave_();
}

void ChuchuDieSelect::loadParams_() {
    DieSelectChemicalPlus::loadParams_();
}

void ChuchuDieSelect::m34(s32 a2, s32 a3, bool a4, bool a5) {
    if (sub_71006F61F0(mActor)) {
        auto* mgr = mActor->getDamageMgr();
        if (mgr) {
            if (mgr->checkDamageFlags(12) || mgr->getField54() == 34 || mgr->getField54() == 32) {
                DieSelectChemicalPlus::m34(a2, a3, a4, a5);
                return;
            }
        }
        *mActor->getLife() = 0;
        if (auto* chemical = mActor->getChemicalStuff())
            chemical->_c &= ~0x10000;
        changeChild("ケミカル放射");
        return;
    }
    DieSelectChemicalPlus::m34(a2, a3, a4, a5);
}

}  // namespace uking::ai
