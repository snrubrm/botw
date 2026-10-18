#include "Game/Actor/Action/actionUKingEmitEffectLoopAction.h"
#include "Game/Actor/aiXlinkHandle.h"
#include "KingSystem/Effect/eftEffect.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

UKingEmitEffectLoopAction::UKingEmitEffectLoopAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

UKingEmitEffectLoopAction::~UKingEmitEffectLoopAction() = default;

bool UKingEmitEffectLoopAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void UKingEmitEffectLoopAction::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71002A36BC();
}

void UKingEmitEffectLoopAction::leave_() {
    if (!*mNoFade_d)
        xlink::fade(_d0, -1);
}

void UKingEmitEffectLoopAction::loadParams_() {
    getDynamicParam(&mScale_d, "Scale");
    getDynamicParam(&mX_d, "X");
    getDynamicParam(&mY_d, "Y");
    getDynamicParam(&mZ_d, "Z");
    getDynamicParam(&mRX_d, "RX");
    getDynamicParam(&mRY_d, "RY");
    getDynamicParam(&mRZ_d, "RZ");
    getDynamicParam(&mR_d, "R");
    getDynamicParam(&mG_d, "G");
    getDynamicParam(&mB_d, "B");
    getDynamicParam(&mA_d, "A");
    getDynamicParam(&mNoFade_d, "NoFade");
    getDynamicParam(&mOverWrite_d, "OverWrite");
    getDynamicParam(&mCutChangeReset_d, "CutChangeReset");
    getDynamicParam(&mActor_d, "Actor");
    getDynamicParam(&mInstanceName_d, "InstanceName");
    getDynamicParam(&mELinkKey_d, "ELinkKey");
    getDynamicParam(&mOption_d, "Option");
}

// NON_MATCHING: option comparisons, stack layout and transform updates differ.
void UKingEmitEffectLoopAction::sub_71002A36BC() {
    if (!mOption_d.isEmpty()) {
        const bool clear_wind = ksys::gdt::getBoolByKey("Clear_RemainsWind");
        const bool clear_water = ksys::gdt::getBoolByKey("Clear_RemainsWater");
        const bool clear_electric = ksys::gdt::getBoolByKey("Clear_RemainsElectric");
        const bool clear_fire = ksys::gdt::getBoolByKey("Clear_RemainsFire");
        if (mOption_d == sead::SafeString("Beam_Wind") && !clear_wind)
            return;
        if (mOption_d == sead::SafeString("Beam_Water") && !clear_water)
            return;
        if (mOption_d == sead::SafeString("Beam_Elect") && !clear_electric)
            return;
        if (mOption_d == sead::SafeString("Beam_Fire") && !clear_fire)
            return;
        const s32 count = s32(clear_wind) + s32(clear_water) + s32(clear_electric) + s32(clear_fire);
        if (mOption_d == sead::SafeString("Beam_1") && count != 1)
            return;
        if (mOption_d == sead::SafeString("Beam_2") && count != 2)
            return;
        if (mOption_d == sead::SafeString("Beam_3") && count != 3)
            return;
        if (mOption_d == sead::SafeString("Beam_4") && count != 4)
            return;
    }
    auto* manager = ksys::evt::Manager::instance();
    auto* link = manager->getBaseProcLinkFromActiveEvent(
        sead::SafeString(mActor_d.cstr()), sead::SafeString(mInstanceName_d.cstr()));
    if (link) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        if (accessor.sub_7100D0F214()) {
            if (auto* xlink = accessor.sub_7100D0F214()) {
                if (auto* user = xlink->_48) {
                    _d0 = user->searchAndEmit(mELinkKey_d.cstr());
                    if (!_d0.isActive()) {
                        const sead::FormatFixedSafeString<128> error(
                            "EFF_ERR[EmitEffectLoopAction::enter_][%s]", mELinkKey_d.cstr());
                    }
                }
            }
        }
        if (*mOverWrite_d) {
            const f32 scale = *mScale_d;
            const sead::Vector3f rotation(*mX_d, *mY_d, *mZ_d);
            const sead::Vector3f translation(*mRX_d, *mRY_d, *mRZ_d);
            sead::Matrix34f matrix;
            matrix.makeSRT(sead::Vector3f(scale, scale, scale), rotation, translation);
            _d0.setMatrix(matrix);
            if (_d0.isActive())
                _d0.setDelayEmitParamColor(sead::Color4f(*mR_d, *mG_d, *mB_d, *mA_d));
        }
    } else if (mActor_d == "GameROMPlayer") {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::evt::Manager::instance()->_1d108->getActorViaAccessor(&accessor);
        if (auto* xlink = accessor.sub_7100D0F214()) {
            if (auto* user = xlink->_48)
                _d0 = user->searchAndEmit(mELinkKey_d.cstr());
        }
    }
}

void UKingEmitEffectLoopAction::calc_() {
    if (*mCutChangeReset_d && ksys::eft::Effect::instance()->get193e0() == 2) {
        xlink::kill(_d0);
        _d0.reset();
        sub_71002A36BC();
    }
}

}  // namespace uking::action
