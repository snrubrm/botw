#include "Game/AI/Action/actionGanonBeastDamageASPlay.h"

namespace uking::action {

GanonBeastDamageASPlay::GanonBeastDamageASPlay(const InitArg& arg) : ForkASPlayBase(arg) {}

GanonBeastDamageASPlay::~GanonBeastDamageASPlay() = default;

bool GanonBeastDamageASPlay::init_(sead::Heap* heap) {
    return ForkASPlayBase::init_(heap);
}

void GanonBeastDamageASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkASPlayBase::enter_(params);
}

void GanonBeastDamageASPlay::leave_() {
    ForkASPlayBase::leave_();
}

void GanonBeastDamageASPlay::loadParams_() {
    ForkASPlayBase::loadParams_();
    getStaticParam(&mIsStateChange_s, "IsStateChange");
    getAITreeVariable(&mLastDamageWeakPointIdx_a, "LastDamageWeakPointIdx");
}

void GanonBeastDamageASPlay::calc_() {
    ForkASPlayBase::calc_();
}

const char* GanonBeastDamageASPlay::m32() {
    if (*mIsStateChange_s) {
        switch (*mLastDamageWeakPointIdx_a) {
        case 0:
            return "Damage";
        case 1:
            return "DamageB";
        case 2:
            return "Damage";
        case 3:
            return "Damage";
        case 4:
            return "Damage";
        case 5:
            return "Damage";
        case 6:
            return "Damage";
        case 7:
            return "DamageF";
        case 8:
            return "Damage";
        case 9:
            return "Damage";
        case 10:
            return "Damage";
        case 11:
            return "Damage";
        case 12:
            return "DamageF";
        case 13:
            return "DamageB";
        case 14:
            return "DamageF";
        case 15:
            return "DamageF";
        case 16:
            return "DamageF";
        default:
            return "DamageR";
        }
    }

    switch (*mLastDamageWeakPointIdx_a) {
    case 0:
        return "DamageL";
    case 1:
        return "DamageB";
    case 2:
        return "DamageR";
    case 3:
        return "DamageR";
    case 4:
        return "DamageL";
    case 5:
        return "DamageR";
    case 6:
        return "DamageL";
    case 7:
        return "DamageF";
    case 8:
        return "DamageR";
    case 9:
        return "DamageL";
    case 10:
        return "DamageL";
    case 11:
        return "DamageR";
    case 12:
        return "DamageF";
    case 13:
        return "DamageB";
    case 14:
        return "DamageF";
    case 15:
        return "DamageF";
    case 16:
        return "DamageF";
    default:
        return "DamageR";
    }
}

}  // namespace uking::action
