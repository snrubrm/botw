#include "Game/AI/AI/aiEnemyChemicalSelect.h"
#include "Game/AI/aiUnk_71006F5B14.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyChemicalSelect::EnemyChemicalSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
EnemyChemicalSelect::~EnemyChemicalSelect() {
    ;
}

bool EnemyChemicalSelect::init_(sead::Heap* heap) {
    if (mChmObjName_s.isEmpty())
        _50 = mActor->getChemicalStuff();
    else
        _50 = mActor->sub_71011D8A54(mChmObjName_s);
    return true;
}

void EnemyChemicalSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    const auto element = sub_71006F5694(mActor);
    if (*mIsCheckActive_s && !sub_71006F594C(element, _50)) {
        changeChild("ノーマル", params);
        return;
    }

    switch (element.value()) {
    case Unk_71006F5DB0::Fire:
        changeChild("ファイア", params);
        break;
    case Unk_71006F5DB0::Electric:
        changeChild("エレキ", params);
        break;
    case Unk_71006F5DB0::Ice:
        changeChild("アイス", params);
        break;
    default:
        changeChild("ノーマル", params);
        break;
    }
}

void EnemyChemicalSelect::calc_() {}

bool EnemyChemicalSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool EnemyChemicalSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

void EnemyChemicalSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyChemicalSelect::loadParams_() {
    getStaticParam(&mIsCheckActive_s, "IsCheckActive");
    getStaticParam(&mChmObjName_s, "ChmObjName");
}

}  // namespace uking::ai
