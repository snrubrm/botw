#include "Game/AI/AI/aiGiantArmorAsWeakPoint.h"
#include "Game/Actor/actGiantArmor.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

Unk_71023f36d8::Unk_71023f36d8(ksys::act::Actor* actor) {
    _8 = sead::DynamicCast<act::GiantArmor>(actor);
}

// NON_MATCHING: the original places the "no armor / no damage scale" block (store 1.0f and the level) after the
// bullet block and shares the final level store; we lay the blocks out the other way round.
void Unk_71023f36d8::m4(f32* out_scale, s32* out_level, const Info* info) {
    if (info->_c && _8 && info->_4 != 4) {
        *out_scale = _8->sub_7100029B54();
        if (info->_4 == 3 && info->attacker) {
            ksys::act::acc::Bullet accessor;
            ksys::act::acquireActor(info->attacker, &accessor);
            const sead::SafeString& name = accessor.getName();
            s32 level = 0x11;
            if (!accessor.sub_71000057DC() && name.findIndex("Bomb") != -1)
                level = 0x16;
            *out_level = sead::Mathi::max(info->level, level);
        } else {
            *out_level = sead::Mathi::max(info->level, 0x11);
        }
    } else {
        *out_scale = 1.0f;
        *out_level = info->level;
    }
}

// NON_MATCHING: the original keeps the store of the base vtable of _38 and stores its derived vtable only after the
// DynamicCast; we emit only the derived vtable store before the cast.
GiantArmorAsWeakPoint::GiantArmorAsWeakPoint(const InitArg& arg) : GiantArmorRoot(arg) {}

// _38's base has a virtual but trivial destructor (defaulted inline in
// gameUnkRttiClasses.h), so destroying _38 emits no call.
GiantArmorAsWeakPoint::~GiantArmorAsWeakPoint() = default;

bool GiantArmorAsWeakPoint::init_(sead::Heap* heap) {
    return GiantArmorRoot::init_(heap);
}

void GiantArmorAsWeakPoint::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantArmorRoot::enter_(params);
    if (auto* armor = sead::DynamicCast<act::GiantArmor>(mActor))
        armor->_c10 = &_38;
}

void GiantArmorAsWeakPoint::calc_() {
    GiantArmorRoot::calc_();
}

void GiantArmorAsWeakPoint::leave_() {
    if (auto* armor = sead::DynamicCast<act::GiantArmor>(mActor))
        armor->_c10 = nullptr;
    GiantArmorRoot::leave_();
}

void GiantArmorAsWeakPoint::loadParams_() {
    GiantArmorRoot::loadParams_();
}

}  // namespace uking::ai
