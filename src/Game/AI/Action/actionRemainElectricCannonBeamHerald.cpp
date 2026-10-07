#include "Game/AI/Action/actionRemainElectricCannonBeamHerald.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/GameData/gdtManagerInline.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

// NON_MATCHING: event position/scale stores differ, and the handle validity test is hoisted across the mode branch.
void Unk_71023b30d8::sub_710022C55C(ksys::act::Actor* actor) {
    sead::Vector3f pos = getPlayerPosition();
    pos.y += 1.0f;
    _28.setPosition(pos);
    if (_8c) {
        if (!_78.isActive())
            _78 = ksys::eft::searchAndEmitELink(actor, "LockOnSign");
        if (!_38.sub_7101241B6C()) {
            xlinkSearchAndEmit(actor, "LockOnCore", 2, &_38);
            _58.fadeXLink();
        }
    } else {
        if (!(_78.isActive() && _78.getEvent()->getBitFlag().isOnBit(4)))
            _78.fade();
        if (!_58.sub_7101241B6C()) {
            xlinkSearchAndEmit(actor, "LockOnCore_InBarrier", 2, &_58);
            _38.fadeXLink();
        }
    }
    _78.setPosition(pos);
    _38.mELink.setPosition(pos, _88);
    _38.mSLink.setPosition(pos);
    _58.mELink.setPosition(pos, _88);
    _58.mSLink.setPosition(pos);
}

RemainElectricCannonBeamHerald::RemainElectricCannonBeamHerald(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainElectricCannonBeamHerald::~RemainElectricCannonBeamHerald() = default;

bool RemainElectricCannonBeamHerald::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainElectricCannonBeamHerald::enter_(ksys::act::ai::InlineParamPack* params) {
    _30 = *mHeraldTime_s;
    _38 = ksys::eft::searchAndEmitELink(mActor, "ChargeCore");
    _38.setPosition(mActor->getMtx().getTranslation());
    _48._8c = !*mWillBeProtected_d;
    _48.sub_710022BE20(mActor);
    if (auto* mgr = ksys::gdt::Manager::instance())
        ksys::gdt::getBoolByNameBypassPerm(mgr, &_d8, "IsPlayed_Demo721_0");
    if (!_d8) {
        _e0.initWithName(mActor, "Demo721_0", "Electlic_Attack");
        _e0.loadEvent();
        _30 += 30.0f;
    }
    mFlags.set(Flag::Changeable);
}

void RemainElectricCannonBeamHerald::leave_() {
    _38.fade();
    _48.sub_710022C2D0(mActor);
    if (_e0.mEventFlow)
        _e0.unloadEvent();
}

void RemainElectricCannonBeamHerald::loadParams_() {
    getStaticParam(&mHeraldTime_s, "HeraldTime");
    getDynamicParam(&mWillBeProtected_d, "WillBeProtected");
}

void RemainElectricCannonBeamHerald::calc_() {
    _38.setPosition(mActor->getMtx().getTranslation());
    ksys::Timer::update(&_30, -1.0f);
    if (_30 <= 30.0f && !_d8) {
        _e0.sendMessageToEventMgrActor(mActor);
        _d8 = true;
    }
    if (_30 <= 0.0f)
        setFinished();
    if (auto* player_info = ksys::act::PlayerInfo::instance())
        player_info->getPlayerPos();
    _48._88 = sead::Mathf::min(1.0f, _30 / *mHeraldTime_s);
    _48._8c = !*mWillBeProtected_d;
}

}  // namespace uking::action
