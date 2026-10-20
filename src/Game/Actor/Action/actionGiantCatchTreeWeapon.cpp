#include "Game/Actor/Action/actionGiantCatchTreeWeapon.h"
#include "Game/Actor/actGiantEnemy.h"
#include "KingSystem/ActorSystem/actUnk_71024eed28.h"

namespace uking::action {

GiantCatchTreeWeapon::GiantCatchTreeWeapon(const InitArg& arg) : Catch(arg) {}

GiantCatchTreeWeapon::~GiantCatchTreeWeapon() = default;

bool GiantCatchTreeWeapon::init_(sead::Heap* heap) {
    return Catch::init_(heap);
}

void GiantCatchTreeWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    Catch::enter_(params);
}

void GiantCatchTreeWeapon::leave_() {
    if (auto* enemy = sead::DynamicCast<uking::act::GiantEnemy>(mActor)) {
        auto* child = enemy->_1558 ? enemy->_1558->m7() : nullptr;
        if (auto* grab = sead::DynamicCast<ksys::act::Unk_7102359478>(child))
            grab->_98 = 0;
    }
    Catch::leave_();
}

void GiantCatchTreeWeapon::loadParams_() {
    Catch::loadParams_();
    getStaticParam(&mCatchPosOffset_s, "CatchPosOffset");
}

void GiantCatchTreeWeapon::calc_() {
    Catch::calc_();
}

}  // namespace uking::action
