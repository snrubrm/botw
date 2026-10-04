#include "Game/AI/Action/actionScrapEquip.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ScrapEquip::ScrapEquip(const InitArg& arg) : ActionWithAS(arg) {}

ScrapEquip::~ScrapEquip() = default;

bool ScrapEquip::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void ScrapEquip::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
    playAS("Scrap", false, 0, 0, -1.0f);
}

void ScrapEquip::leave_() {
    ActionWithAS::leave_();
}

void ScrapEquip::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mDropSpd_s, "DropSpd");
}

void ScrapEquip::calc_() {
    ActionWithAS::calc_();
    auto* actor = mActor;
    if (actor->getASList()->x(71, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        const f32 speed = -*mDropSpd_s;
        const auto& mtx = actor->getMtx();
        const sead::Vector3f velocity{mtx.m[0][2] * speed, mtx.m[1][2] * speed, mtx.m[2][2] * speed};
        playerOrEnemyDropWeapon(actor, &velocity, *mWeaponIdx_s, false, false, nullptr, false);
    }
}

}  // namespace uking::action
