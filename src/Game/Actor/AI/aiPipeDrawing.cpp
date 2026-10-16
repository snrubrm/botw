#include "Game/Actor/AI/aiPipeDrawing.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"

namespace uking::ai {

PipeDrawing::PipeDrawing(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PipeDrawing::~PipeDrawing() = default;

bool PipeDrawing::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PipeDrawing::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71004F6298();
}

void PipeDrawing::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("待機"))
            setFinished();
        else
            sub_71004F6298();
    } else if (child->isChangeable()) {
        auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
        if (!weapon)
            setFailed();
        if (isCurrentChild("鳴らす")) {
            if (weapon->_af8._0 != 1)
                sub_71004F6298();
        } else if (weapon->_af8._0 == 1) {
            sub_71004F6650();
        }
    }
}

void PipeDrawing::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PipeDrawing::loadParams_() {}

// 0x71004f6298
void PipeDrawing::sub_71004F6298() {
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    ksys::act::ai::InlineParamPack pack;
    if (weapon) {
        pack.addString(weapon->m164(), "NodeName", -1);
        sead::Vector3f rot;
        sead::Vector3f trans;
        weapon->m165(&rot);
        weapon->m166(&trans);
        pack.addVec3(rot, "RotOffset", -1);
        pack.addVec3(trans, "TransOffset", -1);
    } else {
        pack.addString("Root", "NodeName", -1);
        pack.addVec3(sead::Vector3f::zero, "RotOffset", -1);
        pack.addVec3(sead::Vector3f::zero, "TransOffset", -1);
    }
    changeChild("待機", &pack);
}

// 0x71004f6650
void PipeDrawing::sub_71004F6650() {
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    ksys::act::ai::InlineParamPack pack;
    if (weapon) {
        pack.addString(weapon->m164(), "NodeName", -1);
        sead::Vector3f rot;
        sead::Vector3f trans;
        weapon->m165(&rot);
        weapon->m166(&trans);
        pack.addVec3(rot, "RotOffset", -1);
        pack.addVec3(trans, "TransOffset", -1);
    } else {
        pack.addString("Root", "NodeName", -1);
        pack.addVec3(sead::Vector3f::zero, "RotOffset", -1);
        pack.addVec3(sead::Vector3f::zero, "TransOffset", -1);
    }
    changeChild("鳴らす", &pack);
}

}  // namespace uking::ai
