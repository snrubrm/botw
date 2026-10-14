#include "Game/Actor/Player/Action/actionPlayerDestinationTurnRefActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUniqueNameSearch.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Event/evtUnk_7100dc816c.h"
#include "KingSystem/Map/mapObject.h"
#include <prim/seadDelegate.h>

namespace ksys::act {
// 0x7100ee25f0 (declared only): findLinkReferenceObj for a link (acquires the actor first).
map::Object* findLinkReferenceObj(BaseProcLink* link, const sead::SafeString& unit_config_name,
                                  const sead::SafeString& a3, int* idx);
}  // namespace ksys::act

// 0x7100ee7168: writes the map object's transform (rotation and translation).
bool sub_7100EE7168(const ksys::map::Object* obj, sead::Matrix34f* out);

namespace uking::action {

PlayerDestinationTurnRefActor::PlayerDestinationTurnRefActor(const InitArg& arg)
    : PlayerAction(arg) {
    _38.reset();
}

PlayerDestinationTurnRefActor::~PlayerDestinationTurnRefActor() = default;

void PlayerDestinationTurnRefActor::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    m33();
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    sub_71007E95E0();
    sead::Matrix34f mtx;
    sub_71007E974C(&mtx);
    const f32 x = mtx.m[0][3];
    const f32 z = mtx.m[2][3];
    _30 = ksys::util::Unk_7101EC6BAC(
        sead::Mathf::atan2Idx(x - static_cast<ksys::act::Player*>(mActor)->_1770.x,
                              z - static_cast<ksys::act::Player*>(mActor)->_1770.z));
    if (static_cast<ksys::act::Player*>(mActor)->isRidingHorse())
        setFinished();
}

void PlayerDestinationTurnRefActor::leave_() {}

void PlayerDestinationTurnRefActor::loadParams_() {
    getDynamicParam(&mUniqName_d, "UniqName");
}

void PlayerDestinationTurnRefActor::calc_() {
    if (static_cast<ksys::act::Player*>(mActor)->sub_7100857014(-1.0f, &_30, -1, -1) && m34())
        setFinished();
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

// NON_MATCHING: stack slot allocation places the delegate before the search and accessor records.
void PlayerDestinationTurnRefActor::sub_71007E95E0() {
    _38.reset();
    _48.reset();
    _38 = ksys::evt::sub_7100DC85D4(mActor);
    if (!_38.hasProc())
        return;
    _58 = 0;
    if (auto* obj = ksys::act::findLinkReferenceObj(&_38, "", mUniqName_d, &_58)) {
        ksys::act::ActorLinkConstDataAccess accessor;
        obj->getActorWithAccessor(accessor);
        if (accessor.hasProc())
            accessor.linkAcquire(&_48);
    } else if (!mUniqName_d.isEmpty()) {
        if (auto* mgr = ksys::act::BaseProcMgr::instance()) {
            ksys::act::ActorUniqueNameSearch search(mUniqName_d);
            sead::Delegate1<ksys::act::ActorUniqueNameSearch, ksys::act::BaseProc*> callback(
                &search, &ksys::act::ActorUniqueNameSearch::sub_7100EDCC10);
            mgr->forEachProc(callback, ksys::act::BaseProcMgr::ProcFilters(0xd));
            if (search.mLink.hasProc())
                _48 = search.mLink;
        }
    }
}

void PlayerDestinationTurnRefActor::sub_71007E974C(sead::Matrix34f* out) {
    if (_48.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_48, &accessor);
        *out = accessor.getActorMtx();
    } else {
        int idx = _58;
        if (auto* obj = ksys::act::findLinkReferenceObj(&_38, "", mUniqName_d, &idx))
            sub_7100EE7168(obj, out);
    }
}

bool PlayerDestinationTurnRefActor::isChangeable() const {
    return false;
}

void PlayerDestinationTurnRefActor::m33() {
    if (mActor->getASList()->x_1(0, 0) != "DemoWait")
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DemoWait", true, -1.0f);
}

bool PlayerDestinationTurnRefActor::m34() {
    return true;
}

bool PlayerDestinationTurnRefActor::m35() {
    return true;
}

}  // namespace uking::action
