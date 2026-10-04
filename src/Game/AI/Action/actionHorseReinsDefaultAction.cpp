#include "Game/AI/Action/actionHorseReinsDefaultAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actHorseObject.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

HorseReinsDefaultAction::HorseReinsDefaultAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void HorseReinsDefaultAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* reins = sead::DynamicCast<act::HorseReins>(mActor)) {
        if (auto* horse = reins->sub_7100E7BA64()) {
            if (reins->getModel())
                _20.mReinsRoot.search(reins->getModel(), "Reins_Root");
            if (horse->getModel())
                _20.mBit.search(horse->getModel(), "Bit");
        }
    }
    mActor->sub_71011DA824(&_20);
    _20.mFlags = 0x10;
}

void HorseReinsDefaultAction::leave_() {
    mActor->sub_71011DA834(&_20);
    for (s32 i = 0; i < 20; ++i)
        _20.getEntry(i).reset();
}

void HorseReinsDefaultAction::loadParams_() {}

// NON_MATCHING: control flow / bind arguments identical; the original stores the constant bind matrices with merged
// 64-bit stores and hoists only the left-hand constants (same shape problem as HorseManeGrabbedAction::calc_), and
// allocates `this` / the actor in the other callee-saved registers
void HorseReinsDefaultAction::calc_() {
    auto* reins = sead::DynamicCast<act::HorseReins>(mActor);
    if (!reins) {
        setFailed();
        return;
    }
    auto* horse = reins->sub_7100E7BA64();
    auto* rider = sead::DynamicCast<ksys::act::Actor>(reins->_850.getProc(nullptr, nullptr));
    auto& flags = _20.mFlags;
    if (horse && horse->getModel()) {
        if ((flags & 0x11) != 1) {
            _20.getEntry(0).set(horse, "Root", reins, "", &sead::Matrix34f::ident, true);
            _20.bindAll(horse, reins, {s32(_20.mCount < 4 ? _20.mCount : 4), _20.mEntries}, true);
            flags |= 1;
        }
    } else if (flags & 0x11) {
        _20.mEntries[0].reset();
        for (s32 i = 4; i < 20; ++i)
            _20.getEntry(i).reset();
        flags &= ~1;
    }

    if (rider && rider->getModel()) {
        if ((flags & 0x12) != 2)
            flags |= 2;

        // left hand (flag 4): bound to the rider's hand while the reins are held in it, else to the horse
        if ((flags & 0x14) != 4 && reins->_868.isOn(1)) {
            _20.getEntry(1).set(rider, "Weapon_L", reins, "Reins_5_L", &sead::Matrix34f::ident,
                                false);
            flags |= 4;
        } else if ((flags & 0x14) && !reins->_868.isOn(1)) {
            if (horse) {
                sead::Matrix34f mtx;
                mtx.makeRT({0.0f, 0.0f, 0.0f}, {0.44f, 0.15f, -0.25f});
                _20.getEntry(1).set(horse, "Spine_2", reins, "Reins_5_L", &mtx, false);
            } else {
                _20.getEntry(1).reset();
            }
            flags &= ~4;
        }

        // right hand (flag 8)
        if ((flags & 0x18) != 8 && reins->_868.isOn(2)) {
            _20.getEntry(2).set(rider, "Weapon_R", reins, "Reins_5_R", &sead::Matrix34f::ident,
                                false);
            flags |= 8;
        } else if ((flags & 0x18) && !reins->_868.isOn(2)) {
            if (horse) {
                sead::Matrix34f mtx;
                mtx.makeRT({-sead::Mathf::pi(), 0.0f, 0.0f}, {0.44f, 0.15f, 0.25f});
                _20.getEntry(2).set(horse, "Spine_2", reins, "Reins_5_R", &mtx, false);
            } else {
                _20.getEntry(2).reset();
            }
            flags &= ~8;
        }
    } else if (flags & 0x12) {
        _20.getEntry(3).reset();
        if (horse) {
            {
                sead::Matrix34f mtx;
                mtx.makeRT({0.0f, 0.0f, 0.0f}, {0.44f, 0.15f, -0.25f});
                _20.getEntry(1).set(horse, "Spine_2", reins, "Reins_5_L", &mtx, false);
            }
            {
                sead::Matrix34f mtx;
                mtx.makeRT({-sead::Mathf::pi(), 0.0f, 0.0f}, {0.44f, 0.15f, 0.25f});
                _20.getEntry(2).set(horse, "Spine_2", reins, "Reins_5_R", &mtx, false);
            }
        } else {
            _20.getEntry(1).reset();
            _20.getEntry(2).reset();
        }
        flags &= ~0xe;
    }
    flags &= ~0x10;
}

}  // namespace uking::action
