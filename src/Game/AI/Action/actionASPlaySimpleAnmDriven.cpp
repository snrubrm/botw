#include "Game/AI/Action/actionASPlaySimpleAnmDriven.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ASPlaySimpleAnmDriven::ASPlaySimpleAnmDriven(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ASPlaySimpleAnmDriven::~ASPlaySimpleAnmDriven() = default;

bool ASPlaySimpleAnmDriven::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ASPlaySimpleAnmDriven::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    auto* model = actor->getModel();
    f32 start_frame = -1.0f;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor))
        start_frame = enemy->_e82 & 0x400 ? 0.0f : -1.0f;
    playAS(mASName_s.cstr(), *mIsIgnoreSame_s, 0, 0, start_frame);
    if (as_list && model)
        as_list->sub_710115BAF8("Root");
    if (*mIsChangeable_s)
        mFlags.set(Flag::Changeable);
}

void ASPlaySimpleAnmDriven::leave_() {
    ksys::act::ai::Action::leave_();
}

void ASPlaySimpleAnmDriven::loadParams_() {
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mResetTransBoneOnLeave_s, "ResetTransBoneOnLeave");
    getStaticParam(&mASName_s, "ASName");
}

void ASPlaySimpleAnmDriven::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
