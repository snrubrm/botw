#include "Game/AI/Action/actionCreateAndReplaceAssassin.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

CreateAndReplaceAssassin::CreateAndReplaceAssassin(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CreateAndReplaceAssassin::~CreateAndReplaceAssassin() = default;

bool CreateAndReplaceAssassin::init_(sead::Heap* heap) {
    sub_71000E2DC0();
    return true;
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
    if (isFinished() || isFailed())
        return;
    if (!_28) {
        setFailed();
        return;
    }

    sead::Vector3f pos = *mOffset_d;
    pos.rotate(mActor->getMtx());
    pos += mActor->getMtx().getTranslation();
    sead::Matrix34f mtx = mActor->getMtx();
    mtx.setTranslation(pos);
    _28->setProperties(0, mtx, nullptr, nullptr, nullptr, false, 0, -1);
    _30 = true;
    mActor->deleteEx(ksys::act::Actor::DeleteType::_4, ksys::act::BaseProc::DeleteReason::_0);
    setFinished();
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
