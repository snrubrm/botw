#include "Game/AI/Action/actionCreateAndReplaceAssassin.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

CreateAndReplaceAssassin::CreateAndReplaceAssassin(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CreateAndReplaceAssassin::~CreateAndReplaceAssassin() = default;

bool CreateAndReplaceAssassin::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CreateAndReplaceAssassin::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CreateAndReplaceAssassin::leave_() {
    ksys::act::ai::Action::leave_();
}

void CreateAndReplaceAssassin::loadParams_() {
    getDynamicParam(&mOffset_d, "Offset");
}

void CreateAndReplaceAssassin::calc_() {
    ksys::act::ai::Action::calc_();
}

bool CreateAndReplaceAssassin::hasPreDeleteCb() {
    return true;
}

void CreateAndReplaceAssassin::onPreDelete() {
    if (_30)
        return;
    if (_28)
        _28->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

}  // namespace uking::action
