#include "Game/AI/Action/actionVanish.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actDropData.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

Vanish::Vanish(const InitArg& arg) : TimeredASPlay(arg) {}

Vanish::~Vanish() = default;

bool Vanish::init_(sead::Heap* heap) {
    return TimeredASPlay::init_(heap);
}

void Vanish::enter_(ksys::act::ai::InlineParamPack* params) {
    TimeredASPlay::enter_(params);
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e90 = 1;
    if (mActor->getDropData() && *mNoDrop_s) {
        if (auto* drop_data = sead::DynamicCast<ksys::act::DropData>(mActor->getDropData()))
            drop_data->_c |= 1;
    }
    if (*mDieType_s >= 0) {
        if (auto* info = mActor->m135()) {
            info->_4 = sub_71005E2B28(*mDieType_s);
            if (info->_4 == 3) {
                if (auto* xlink = mActor->getXLink())
                    xlink->sub_7101230E18();
            }
        }
    }
}

void Vanish::leave_() {
    TimeredASPlay::leave_();
}

void Vanish::loadParams_() {
    TimeredASPlay::loadParams_();
    getStaticParam(&mDieType_s, "DieType");
    getStaticParam(&mNoDrop_s, "NoDrop");
}

void Vanish::calc_() {
    TimeredASPlay::calc_();
}

}  // namespace uking::action
