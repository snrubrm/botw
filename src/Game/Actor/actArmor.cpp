#include <basis/seadNew.h>
#include "Game/Actor/actArmorBase.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerArmors.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::act {

Armor::Armor(const CreateArg& arg) : ArmorBase(arg) {}

ksys::act::BaseProc* Armor::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Armor(arg);
}

bool Armor::m81(const ksys::Message& message) {
    s32 frame;
    switch (message.getType()) {
    case 0x8000035:
        if (auto* owner = getOwner()) {
            if (owner->get1a0() ||
                (owner->getMapObject() &&
                 owner->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000))) {
                sub_71011C9964(owner);
                return true;
            }
        }
        return false;
    case 0x80000b9:
        frame = ksys::gdt::getFlag_ColorChange_MaterialIndex(false);
        sub_7100E2BACC(&frame);
        return true;
    case 0x80000ba:
        sub_7100E2BACC(&_85c);
        return true;
    default:
        return false;
    }
}

void Armor::m148() {
    if (auto* owner = getOwner()) {
        if (auto* player = sead::DynamicCast<ksys::act::PlayerBase>(owner)) {
            const f32 value = player->m317();
            if (_9a8 != value) {
                Unk_710260af28::instance()->sub_7100F1EAF8(mModel, value);
                if (auto* physics = mPhysics) {
                    if (value == 0.0f)
                        physics->getFlags().reset(ksys::phys::InstanceSet::Flag::_20000);
                    else
                        physics->getFlags().set(ksys::phys::InstanceSet::Flag::_20000);
                }
                _9a8 = value;
            }
            const sead::Color4f color = *static_cast<const sead::Color4f*>(player->m314());
            if (!(_9ac == color)) {
                Unk_710260af28::instance()->sub_7100F1E2F4(mModel, color);
                _9ac = color;
            }
            f32 weight;
            if (getProfile() == "ArmorHead" && _850 && _850->get133())
                weight = 0.0f;
            else
                weight = player->m139();
            sub_71011CCB1C(weight);
            x_3(player->m316());
        } else {
            const f32 value = owner->m139();
            if (m139() != value)
                sub_71011CCB1C(value);
        }
    }
    ArmorBase::m148();
}

}  // namespace uking::act
