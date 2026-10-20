#include "Game/Actor/actSandworm.h"
#include <basis/seadNew.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_7102451120.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::act {

// Sandworm's material filter, vtable 0x71023cf690. The factory allocates only the vptr.
class Unk_71023cf690 : public ksys::phys::NavMeshCharacterUnk58 {
public:
    ~Unk_71023cf690() override;
    f32 m3(ksys::phys::NavMeshCharacter* nav, s32 material, s32 a,
           ksys::phys::NavMeshCharacterType type, f32 cost) override {
        return ksys::phys::NavMeshCharacter::sub_7100F74FD8(
            ksys::phys::NavMeshCharacter::sub_7100F74F94(nav), material);
    }
    bool m5(ksys::phys::NavMeshCharacter* nav, s32 material, s32 a, s32 other_material, s32 other_a,
            ksys::phys::NavMeshCharacterType type) override;
};
KSYS_CHECK_SIZE_NX150(Unk_71023cf690, 0x8);

// The original keeps its vptr store; { ; } follows GameDataFlagSelector (96101229).
Unk_71023cf690::~Unk_71023cf690() { ; }

// Materials 5 and 10 are accepted directly; otherwise the pair is usable when the first material is.
bool Unk_71023cf690::m5(ksys::phys::NavMeshCharacter* nav, s32 material, s32 a, s32 other_material,
                        s32 other_a, ksys::phys::NavMeshCharacterType type) {
    if (material == 5 || material == 10)
        return true;
    if (!m4(nav, material, a, type))
        return true;
    return m4(nav, other_material, other_a, type);
}

ksys::phys::NavMeshCharacterUnk58* Sandworm::m179(sead::Heap* heap) {
    return new (heap, 8) Unk_71023cf690;
}

Sandworm::Sandworm(const CreateArg& arg) : Enemy(arg) {
    _1c0 = 1;
}

Sandworm::~Sandworm() = default;

ksys::act::BaseProc* Sandworm::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Sandworm(arg);
}

// NON_MATCHING: the original loads the vtable pointer separately in each branch (ours hoists the common load)
void Sandworm::sub_71002CDAE4(bool on) {
    if (auto* x = _1250) {
        if (auto* y = x->_18) {
            if (on)
                y->m0();
            else
                y->m1();
        }
    }
}

bool Sandworm::m81(const ksys::Message& message) {
    const auto& type = message.getType();
    // NON_MATCHING: check order only: the original tests 0x3000004 before 0x3000003; our toolchain
    // emits this if-chain in reverse (0x3000003 first) with the bodies attached. Else-if in either
    // order, separate ifs and a switch were all tried.
    if (type == 0x3000004) {
        if (_14c8 != 2) {
            _14cc = _14c8;
            sub_71007208EC(this);
        }
    } else if (type == 0x3000003) {
        if (_14cc != 2) {
            sub_7100720814(this, _14cc);
            _14cc = 2;
        }
    }
    return Enemy::m81(message);
}

void Sandworm::killWithDropsAndEffects(int a1) {
    sub_71002CDB48();
    Enemy::killWithDropsAndEffects(a1);
    incrementGiantOrSandwormDefeatCount();
}

void Sandworm::sub_71002CDDE8() {
    auto* controller = getCharacterController();
    if (!controller || !controller->sub_7100F5F14C())
        return;
    auto* nav = m45();
    if (!nav)
        return;
    if ((nav->_2a4 & 0xffff) == 0x17 || (nav->_2a4 & 0xffff) == 5 || (nav->_2a4 & 0xffff) == 10)
        return;

    const sead::Vector3f from = _1644;
    sead::Vector3f pos = getMtx().getTranslation();
    const f32 dist = sead::Mathf::sqrt(sead::Mathf::square(from.x - pos.x) + sead::Mathf::square(from.z - pos.z));
    if (dist >= 30.0f || sead::Mathf::abs(from.y - pos.y) >= 15.0f) {
        _1644.e = pos.e;
        return;
    }
    if (dist >= 5.0f) {
        sub_710072FBD4(this, from, pos, &pos, -1, 0.0f, -1.0f);
        _1644.e = pos.e;
    }
}

void Sandworm::m56(sead::Vector3f* pos) {
    if (_1650 && _1650->isAddedToWorld())
        _1650->getCenterOfMassInWorld(pos);
    else
        x_18(pos);
}

void Sandworm::setNecklaceFlag(s32 index) {
    if (index >= 1 && ksys::act::hasTag(this, 0x12ad8456))
        Enemy::setNecklaceFlag(index + 1);
}

void Sandworm::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    Enemy::m76(setter);
}

}  // namespace uking::act
