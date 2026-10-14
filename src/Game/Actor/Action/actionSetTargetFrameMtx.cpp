#include "Game/Actor/Action/actionSetTargetFrameMtx.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

SetTargetFrameMtx::SetTargetFrameMtx(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetTargetFrameMtx::~SetTargetFrameMtx() = default;

bool SetTargetFrameMtx::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetTargetFrameMtx::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    auto* model = actor->getModel();
    actor->getMainBody();

    sead::Matrix34f mtx;
    if (*mIsHomeMtx_s)
        actor->getHomeMtx(&mtx);
    else
        mtx = actor->getMtx();

    playAS(mASName_s.cstr(), *mIsIgnoreSame_s, *mTargetIdx_s, *mSeqBankIdx_s, -1.0f);

    if (as_list && model) {
        sead::Matrix34f root_mtx;
        as_list->sub_710115BAF8("Root");
        as_list->sub_710115D4A4(0.0f, &root_mtx, true);
        const sead::Vector3f start = root_mtx.getTranslation();
        as_list->sub_710115D4A4(
            as_list->x_5(*mTargetIdx_s, *mSeqBankIdx_s, &ksys::as::ASList::Unk2::sub_710116323C),
            &root_mtx, true);
        as_list->sub_710115F1D8(0, 0, 1.0f);
        const sead::Vector3f delta = root_mtx.getTranslation() - start;
        mtx.setTranslation(mtx.getTranslation() + delta);
    }

    if (auto* body = actor->getMainBody()) {
        if (body->isAddedToWorld()) {
            actor->setMtx(mtx, false, true);
        } else {
            actor->setMtx(mtx, true, true);
            actor->nullsub_4648();
        }
        body->setLinearVelocity(sead::Vector3f::zero);
        body->setAngularVelocity(sead::Vector3f::zero);
    }

    mFlags.set(Flag::Changeable);
}

void SetTargetFrameMtx::leave_() {
    if (*mResetTransBoneOnLeave_s) {
        if (auto* as_list = mActor->getASList())
            as_list->sub_710115CD0C();
    }
}

void SetTargetFrameMtx::loadParams_() {
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mTargetFrame_s, "TargetFrame");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mResetTransBoneOnLeave_s, "ResetTransBoneOnLeave");
    getStaticParam(&mIsHomeMtx_s, "IsHomeMtx");
    getStaticParam(&mASName_s, "ASName");
}

void SetTargetFrameMtx::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
