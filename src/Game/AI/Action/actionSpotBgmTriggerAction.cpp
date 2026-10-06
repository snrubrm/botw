#include "Game/AI/Action/actionSpotBgmTriggerAction.h"
#include <xlink2/xlink2SystemSLink.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapMubinIter.h"

namespace uking::action {

SpotBgmTriggerAction::SpotBgmTriggerAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SpotBgmTriggerAction::~SpotBgmTriggerAction() {
    if (_48) {
        _48->_8.sub_710101D9A4();
        delete _48;
        _48 = nullptr;
    }
}

// NON_MATCHING: same instructions; block layout of the shared `return false` exits and the placement of the
// `is_box = 1` constant differ
bool SpotBgmTriggerAction::init_(sead::Heap* heap) {
    if (xlink2::SystemSLink::instance()->isCallEnabled()) {
        const char* shape;
        if (!mActor->getMapObjIter().tryGetParamStringByKey(&shape, "Shape"))
            return false;

        u64 is_box;
        if (sead::SafeString(shape) == "Sphere")
            is_box = 0;
        else if (sead::SafeString(shape) == "Box")
            is_box = 1;
        else
            return false;

        _48 = new (heap, 8) Unk_SpotBgmInstance(true);
        if (!_48)
            return false;
        _48->sub_71010233CC(heap, &mSound_m, is_box, mActor);
        _48->_8.sub_710101D970();
        if (is_box && *mIsStopWithoutReductionY_m)
            _48->sub_71010242F0();
    }
    return true;
}

void SpotBgmTriggerAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_48) {
        if (auto* mgr = sub_710FFD7CC())
            mgr->sub_710FFBBE4(_48);
    }
}

void SpotBgmTriggerAction::leave_() {
    if (_48) {
        if (auto* mgr = sub_710FFD7CC())
            mgr->sub_710FFBCA0(_48);
    }
}

void SpotBgmTriggerAction::loadParams_() {
    getDynamicParam(&mSound_d, "Sound");
    getMapUnitParam(&mIsStopWithoutReductionY_m, "IsStopWithoutReductionY");
    getMapUnitParam(&mSound_m, "Sound");
}

void SpotBgmTriggerAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
