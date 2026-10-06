#include "Game/AI/Query/queryCheckTypeOfWildHorseAssociated.h"
#include <evfl/Query.h>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actHorseBase.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::query {

CheckTypeOfWildHorseAssociated::CheckTypeOfWildHorseAssociated(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckTypeOfWildHorseAssociated::~CheckTypeOfWildHorseAssociated() = default;

int CheckTypeOfWildHorseAssociated::doQuery() {
    auto* link = &HorseMgr::instance()->_30;
    if (!link->hasProc() || HorseMgr::instance()->sub_7100E85334(*link))
        return 7;

    int result;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    const sead::Vector3f horse_pos = accessor.getActorMtx().getTranslation();
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const f32 dx = pos.x - horse_pos.x;
    const f32 dz = pos.z - horse_pos.z;
    if (sead::Mathf::sqrt(dx * dx + dz * dz) < 50.0f) {
        if (act::sub_7100E6DC50(accessor)) {
            const HorseMgr::RiddenAnimalType type(act::sub_7100E6ECC4(accessor));
            switch (type) {
            case HorseMgr::RiddenAnimalType::_3:
                result = 2;
                break;
            case HorseMgr::RiddenAnimalType::_4:
                result = 1;
                break;
            case HorseMgr::RiddenAnimalType::_5:
                result = 4;
                break;
            case HorseMgr::RiddenAnimalType::_6:
                result = 3;
                break;
            case HorseMgr::RiddenAnimalType::_7:
            case HorseMgr::RiddenAnimalType::_8:
                result = 0;
                break;
            case HorseMgr::RiddenAnimalType::_9:
                result = 5;
                break;
            default:
                result = 0;
                break;
            }
        } else {
            result = 6;
        }
    } else {
        result = 7;
    }
    return result;
}

void CheckTypeOfWildHorseAssociated::loadParams(const evfl::QueryArg& arg) {}

void CheckTypeOfWildHorseAssociated::loadParams() {}

}  // namespace uking::query
