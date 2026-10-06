#include "Game/AI/Query/queryCheckSiteBossDamageAnm.h"
#include <evfl/Query.h>
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::query {

CheckSiteBossDamageAnm::CheckSiteBossDamageAnm(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckSiteBossDamageAnm::~CheckSiteBossDamageAnm() = default;

int CheckSiteBossDamageAnm::doQuery() {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss || !boss->_1558.isOnBit(11))
        return 0;

    auto* list = boss->getASList();
    if (!list)
        return 0;

    if (list->x_1(0, 0).findIndex("Wait") != -1)
        return 1;
    if (list->x_1(0, 0) == "BigDamage_Demo")
        return list->x_5(0, 0, &ksys::as::ASList::Unk2::sub_71011632F8) > 20.0f;
    return 0;
}

void CheckSiteBossDamageAnm::loadParams(const evfl::QueryArg& arg) {}

void CheckSiteBossDamageAnm::loadParams() {}

}  // namespace uking::query
