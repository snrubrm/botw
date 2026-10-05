#include "Game/AI/AI/aiArmorSearchKorokRoot.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

ArmorSearchKorokRoot::ArmorSearchKorokRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ArmorSearchKorokRoot::~ArmorSearchKorokRoot() = default;

bool ArmorSearchKorokRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ArmorSearchKorokRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = false;
    _49 = false;
    _4c = 0.0f;
    _50 = sead::Vector3f::zero;
    changeChild("未発見");
}

void ArmorSearchKorokRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ArmorSearchKorokRoot::calc_() {
    if (ui::isPauseMenuScreenNotClosed())
        return;
    if (_4c >= *mSearchRefreshFrame_s) {
        _48 = false;
        _4c = 0.0f;
        if (!ksys::evt::Manager::instance()->hasActiveEvent())
            sub_710030FCEC();
    } else {
        _4c += ksys::VFR::instance()->getDeltaTime() * 30.0f;
    }
    if (isCurrentChild("発見")) {
        if (!_48 && mActor->getASList()->x_7(0, 0, &ksys::as::ASList::Unk2::sub_7101162FE8)) {
            if (_49)
                _49 = false;
            else
                changeChild("未発見");
        }
    } else if (_48 && mActor->getASList()->x_7(0, 0, &ksys::as::ASList::Unk2::sub_7101162F2C)) {
        changeChild("発見");
    }
}

void ArmorSearchKorokRoot::loadParams_() {
    getStaticParam(&mSearchKorokDis_s, "SearchKorokDis");
    getStaticParam(&mSearchRefreshFrame_s, "SearchRefreshFrame");
}

}  // namespace uking::ai
