#include "Game/AI/AI/aiFldObjDlcHeroMapRelief.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::ai {

FldObjDlcHeroMapRelief::FldObjDlcHeroMapRelief(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
FldObjDlcHeroMapRelief::~FldObjDlcHeroMapRelief() {
    ;
}

bool FldObjDlcHeroMapRelief::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FldObjDlcHeroMapRelief::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void FldObjDlcHeroMapRelief::calc_() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (!gdm)
        return;

    bool is_open = false;
    bool is_clear = false;
    if (!mOpenFlag_m.isEmpty())
        gdm->getParam().get().getBool(&is_open, mOpenFlag_m);
    if (!mClearFlag_m.isEmpty())
        gdm->getParam().get().getBool(&is_clear, mClearFlag_m);

    if (is_clear)
        changeChild("クリア");
    else if (is_open)
        changeChild("オープン");
    else
        changeChild("クローズ");
}

void FldObjDlcHeroMapRelief::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FldObjDlcHeroMapRelief::loadParams_() {
    getMapUnitParam(&mOpenFlag_m, "OpenFlag");
    getMapUnitParam(&mClearFlag_m, "ClearFlag");
}

}  // namespace uking::ai
