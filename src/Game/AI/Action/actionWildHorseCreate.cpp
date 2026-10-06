#include "Game/AI/Action/actionWildHorseCreate.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapPlacementMgr.h"

namespace uking::action {

WildHorseCreate::WildHorseCreate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WildHorseCreate::~WildHorseCreate() = default;

bool WildHorseCreate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WildHorseCreate::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* manager = ksys::map::PlacementMgr::instance();
    if (manager && manager->mPlacementActors) {
        const f32 distance = ksys::map::getActorTraverseDist("GameRomHorse01", 1.0f);
        _58 = distance * distance;
    }
}

void WildHorseCreate::leave_() {
    for (s32 i = _48.size() - 1; i >= 0; --i)
        _48[i].deleteProc();
    for (s32 i = 0; i < _38.size(); ++i) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_38[i], &accessor)) {
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3800017),
                                nullptr, true);
        }
    }
}

void WildHorseCreate::loadParams_() {
    getStaticParam(&mMinCreateNum_s, "MinCreateNum");
    getStaticParam(&mMaxCreateNum_s, "MaxCreateNum");
    getMapUnitParam(&mWildHorseCreateNum_m, "WildHorseCreateNum");
}

void WildHorseCreate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
