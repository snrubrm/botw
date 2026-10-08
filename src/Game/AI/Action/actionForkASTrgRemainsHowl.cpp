#include "Game/AI/Action/actionForkASTrgRemainsHowl.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelUnit.h>
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"

namespace uking::action {

ForkASTrgRemainsHowl::ForkASTrgRemainsHowl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgRemainsHowl::~ForkASTrgRemainsHowl() = default;

bool ForkASTrgRemainsHowl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgRemainsHowl::sub_7100142EC4(bool on) {
    auto* set = mActor->getRigidBodyByName(ksys::act::getStr_Body().cstr());
    if (!set)
        return;
    auto& bodies = set->getRigidBodies();
    for (s32 i = 0, n = bodies.size(); i < n; ++i) {
        auto* body = bodies[i];
        if (!body)
            continue;
        if (!body->getHkBodyName().include("Spine") && !body->getHkBodyName().include("Head")) {
            if (on)
                body->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
            else
                body->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
        }
    }
}

void ForkASTrgRemainsHowl::sub_7100143068() {
    auto* actor = mActor;
    if (!actor)
        return;
    xlink2::HandleSLink handle;
    ksys::eft::sub_710105DDB8(actor, "RoarSe", &handle);
    if (!handle.isActive())
        return;
    auto* as_list = actor->getASList();
    if (!as_list)
        return;
    auto* model = as_list->_8;
    if (!model)
        return;
    const auto key = model->searchBone("Head");
    if (!key.isValid())
        return;
    sead::Matrix34f mtx;
    model->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(&mtx, key.bone_index);
    if (handle.isActive())
        handle.setPosition(mtx.getTranslation());
}

// NON_MATCHING: accessor address caching and stack placement differ.
void ForkASTrgRemainsHowl::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100142EC4(true);
    ksys::act::acc::PlayerBase player;
    if (player.getPlayerFromPlayerInfo())
        sendMessage(*player.getMessageTransceiverId(), ksys::MessageType(0x080000B2), nullptr);
    mFlags.set(Flag::Changeable);
    sub_7100143068();
    sub_7100143180();
}

// NON_MATCHING: one vtable slot — the original calls ModelUnit slot 0x70, ours resolves
// safeGetBoneWorldMatrix to slot 0x80 (gsysModelUnit.h carries two extra virtuals before it;
// libwork request in lane3-log session 52). Everything else matches.
void ForkASTrgRemainsHowl::sub_7100143180() {
    ksys::act::acc::Camera accessor;
    sub_710092DAE8(&accessor);
    const auto& mtx = mActor->getMtx();
    sead::Vector3f pos;
    pos.x = mtx(0, 3);
    pos.y = mtx(1, 3);
    pos.z = mtx(2, 3);
    auto* model = mActor->getModel();
    const auto& actor_mtx = mActor->getMtx();
    if (model) {
        auto key = model->searchBone("Nose_1");
        if (key.isValid()) {
            sead::Matrix34f bone_mtx;
            model->getUnits()(key.model_unit_index)
                ->mModelUnit->safeGetBoneWorldMatrix(&bone_mtx, key.bone_index);
            pos.x = bone_mtx(0, 3);
            pos.y = bone_mtx(1, 3);
            pos.z = bone_mtx(2, 3);
        }
    }
    accessor.setWaterRemainsData(actor_mtx, pos);
}

void ForkASTrgRemainsHowl::leave_() {
    sub_7100142EC4(false);
}

void ForkASTrgRemainsHowl::loadParams_() {
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getDynamicParam(&mIsTargetLost_d, "IsTargetLost");
}

void ForkASTrgRemainsHowl::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
