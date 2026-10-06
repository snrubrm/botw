#include "Game/AI/AI/aiGuardianAI.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GuardianAI::GuardianAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianAI::~GuardianAI() = default;

bool GuardianAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GuardianAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardianAI::calc_() {}

void GuardianAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianAI::loadParams_() {}

act::Guardian* GuardianAI::sub_710040DA6C() {
    return sead::DynamicCast<act::Guardian>(mActor);
}

// Inline-only in the original (name is a guess; 0x710040daf8 and 0x710040dc54 both contain it): the actor as a
// Guardian, else its connected calc parent as a Guardian.
static inline act::Guardian* getGuardianOrParent(ksys::act::Actor* actor) {
    if (!actor)
        return nullptr;
    if (auto* guardian = sead::DynamicCast<act::Guardian>(actor))
        return guardian;
    if (auto* parent = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent()))
        return sead::DynamicCast<act::Guardian>(parent);
    return nullptr;
}

act::Guardian::Unk15a8* GuardianAI::sub_710040DAF8() {
    auto* guardian = getGuardianOrParent(mActor);
    return guardian ? guardian->_15a8 : nullptr;
}

act::Guardian::Unk1* GuardianAI::sub_710040DC54() {
    auto* guardian = getGuardianOrParent(mActor);
    return guardian ? guardian->_15b0 : nullptr;
}

act::Guardian::Unk15a8* GuardianAI::sub_710040DC50() {
    return sub_710040DAF8();
}

act::Guardian::Unk1* GuardianAI::sub_710040DDAC() {
    return sub_710040DC54();
}

void GuardianAI::sub_710040DDB0(s32 state) {
    if (auto* guardian = sead::DynamicCast<act::Guardian>(mActor))
        guardian->sub_7100035A90(state);
}

void GuardianAI::sub_710040DE48(bool on) {
    if (auto* guardian = sead::DynamicCast<act::Guardian>(mActor))
        guardian->sub_7100034514(on);
}

bool GuardianAI::sub_710040DEE0() {
    if (auto* guardian = sead::DynamicCast<act::Guardian>(mActor))
        return guardian->sub_710003B43C();
    return false;
}

bool GuardianAI::sub_710040DF74() {
    if (auto* guardian = sead::DynamicCast<act::Guardian>(mActor))
        return guardian->sub_710003B4C8();
    return false;
}

bool GuardianAI::sub_710040E008(sead::Vector3f* out) {
    if (auto* data = sub_710040DAF8()) {
        *out = data->_3c;
        return true;
    }
    return false;
}

bool GuardianAI::sub_710040E048(sead::Vector3f* out) {
    if (auto* data = sub_710040DAF8()) {
        *out = data->_30;
        return true;
    }
    return false;
}

void GuardianAI::sub_710040E088(u32 value) {
    if (auto* guardian = sead::DynamicCast<act::Guardian>(mActor))
        guardian->sub_710003B090(value);
}

}  // namespace uking::ai
