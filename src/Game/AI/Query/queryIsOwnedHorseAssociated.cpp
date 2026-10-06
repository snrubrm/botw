#include "Game/AI/Query/queryIsOwnedHorseAssociated.h"
#include <evfl/Query.h>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actHorseBase.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::query {

IsOwnedHorseAssociated::IsOwnedHorseAssociated(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsOwnedHorseAssociated::~IsOwnedHorseAssociated() = default;

// NON_MATCHING: the original compares the horse type with 3, 4 and 6 one by one; ours becomes a lookup table over 3-6.
int IsOwnedHorseAssociated::doQuery() {
    auto* mgr = HorseMgr::instance();
    int result = 0;
    bool failed = true;
    if (mgr && (!*mIsRidden || mgr->sub_7100E85334(mgr->_30))) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&mgr->mOwnedHorse, &accessor)) {
            const sead::Vector3f horse_pos = accessor.getActorMtx().getTranslation();
            const sead::Vector3f pos = mActor->getMtx().getTranslation();
            const f32 dx = pos.x - horse_pos.x;
            const f32 dz = pos.z - horse_pos.z;
            if (sead::Mathf::sqrt(dx * dx + dz * dz) < 50.0f) {
                failed = false;
                const HorseMgr::RiddenAnimalType type(act::sub_7100E6ECC4(accessor));
                switch (type) {
                case HorseMgr::RiddenAnimalType::_3:
                    result = 1;
                    break;
                case HorseMgr::RiddenAnimalType::_4:
                    result = 4;
                    break;
                case HorseMgr::RiddenAnimalType::_6:
                    result = 2;
                    break;
                default:
                    result = 0;
                    break;
                }
            }
        }
    }
    if (failed)
        result = 3;
    return result;
}

void IsOwnedHorseAssociated::loadParams(const evfl::QueryArg& arg) {
    loadBool(arg.param_accessor, "IsRidden");
}

void IsOwnedHorseAssociated::loadParams() {
    getDynamicParam(&mIsRidden, "IsRidden");
}

}  // namespace uking::query
