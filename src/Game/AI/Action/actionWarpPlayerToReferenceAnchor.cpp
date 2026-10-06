#include "Game/AI/Action/actionWarpPlayerToReferenceAnchor.h"
#include "Game/gameResetter.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementMgr.h"

namespace uking::action {

WarpPlayerToReferenceAnchor::WarpPlayerToReferenceAnchor(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

WarpPlayerToReferenceAnchor::~WarpPlayerToReferenceAnchor() = default;

bool WarpPlayerToReferenceAnchor::init_(sead::Heap* heap) {
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    if (player.hasProc())
        _1c.set(player.getField418());
    else
        _1c.set(1.0f, 1.0f, 1.0f);
    return true;
}

// NON_MATCHING: the original copies the object translation into the PlacementMgr as one 8-byte plus one 4-byte move
// (a memcpy-style copy; Vector3f::operator= copies element-wise) and orders the z load of the local copy differently.
void WarpPlayerToReferenceAnchor::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!Resetter::instance() || !mActor) {
        setFailed();
        return;
    }
    auto* object = ksys::act::findLinkReferenceObj(mActor, "DestinationAnchor", "", nullptr);
    if (!object) {
        setFailed();
        return;
    }
    const sead::Vector3f rotation(0.0f, object->getRotate().y * 57.295776f, 0.0f);
    const sead::Vector3f position = object->getTranslate();
    if (Resetter::instance()->sub_71007D25A4(nullptr, 1, &position, &rotation, &_1c, "", false)) {
        auto* mgr = ksys::map::PlacementMgr::instance();
        mgr->_27c = object->getTranslate();
        mgr->_288 = 1;
    } else {
        setFailed();
    }
}

void WarpPlayerToReferenceAnchor::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpPlayerToReferenceAnchor::loadParams_() {}

void WarpPlayerToReferenceAnchor::calc_() {
    if (isFinished() || isFailed())
        return;
    if (auto* resetter = Resetter::instance()) {
        if (resetter->finishedReset())
            setFinished();
    } else {
        setFailed();
    }
}

}  // namespace uking::action
