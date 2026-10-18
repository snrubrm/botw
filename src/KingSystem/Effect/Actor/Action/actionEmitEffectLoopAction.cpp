#include "KingSystem/Effect/Actor/Action/actionEmitEffectLoopAction.h"
#include "Game/Actor/aiXlinkHandle.h"
#include "KingSystem/Effect/eftEffect.h"
#include <xlink2/xlink2SystemELink.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace ksys::eft {

EmitEffectLoopAction::EmitEffectLoopAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EmitEffectLoopAction::~EmitEffectLoopAction() = default;

bool EmitEffectLoopAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EmitEffectLoopAction::enter_(ksys::act::ai::InlineParamPack* params) {
    doStuff();
}

void EmitEffectLoopAction::leave_() {
    if (!*mNoFade_d)
        uking::xlink::fade(_d0, -1);
}

void EmitEffectLoopAction::loadParams_() {
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
    getDynamicParam(&mOverWrite_d, "OverWrite");
    getDynamicParam(&mNoFade_d, "NoFade");
    getDynamicParam(&mActor_d, "Actor");
    getDynamicParam(&mInstanceName_d, "InstanceName");
    getDynamicParam(&mELinkKey_d, "ELinkKey");
    getDynamicParam(&mOption_d, "Option");
    getDynamicParam(&mCutChangeReset_d, "CutChangeReset");
}

// NON_MATCHING: accessor lifetimes, matrix arithmetic and handle updates differ.
void EmitEffectLoopAction::doStuff() {
    auto* manager = evt::Manager::instance();
    auto* link = manager->getBaseProcLinkFromActiveEvent(
        sead::SafeString(mActor_d.cstr()), sead::SafeString(mInstanceName_d.cstr()));
    if (link) {
        act::ActorLinkConstDataAccess accessor;
        act::acquireActor(link, &accessor);
        if (accessor.sub_7100D0F214()) {
            if (auto* xlink = accessor.sub_7100D0F214()) {
                if (auto* user = xlink->_48) {
                    _d0 = user->searchAndEmit(mELinkKey_d.cstr());
                    if (!_d0.isActive() && !xlink2::SystemELink::instance()->isServerConnecting()) {
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
        act::ActorLinkConstDataAccess accessor;
        evt::Manager::instance()->_1d108->getActorViaAccessor(&accessor);
        if (auto* xlink = accessor.sub_7100D0F214()) {
            if (auto* user = xlink->_48)
                _d0 = user->searchAndEmit(mELinkKey_d.cstr());
        }
    }
}

// NON_MATCHING: saved-handle addressing and create-id load scheduling differ.
void EmitEffectLoopAction::calc_() {
    if (*mCutChangeReset_d && ksys::eft::Effect::instance()->get193e0() == 2) {
        _e0 = _d0;
        doStuff();
        if (ksys::eft::Effect::instance()->get193e0() == 2) {
            _e0.kill();
            _e0.reset();
        }
    }
}

}  // namespace ksys::eft
