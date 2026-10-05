#include "Game/AI/Behavior/behaviorOctarockHideHPGage.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_7102450d10.h"

namespace uking::behavior {

OctarockHideHPGage::OctarockHideHPGage(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

OctarockHideHPGage::~OctarockHideHPGage() = default;

bool OctarockHideHPGage::m6(sead::Heap* heap) {
    return true;
}

void OctarockHideHPGage::m8() {}

void OctarockHideHPGage::m7() {
    auto* unit = sead::DynamicCast<Unk_7102450d10>(
        *static_cast<Unk_71025afb58**>(mOctarockFormChangeUnit_a));
    if (unit && unit->sub_7100714454()) {
        if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
            enemy->_e90 = 1;
    } else {
        if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
            enemy->_e90 = 0;
    }
}

void OctarockHideHPGage::loadParams() {
    getAITreeVariable(&mOctarockFormChangeUnit_a, "OctarockFormChangeUnit");
}

void OctarockHideHPGage::m9() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e90 = 0;
}

}  // namespace uking::behavior
