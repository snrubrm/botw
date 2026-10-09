#include "Game/Actor/actCameraUtil.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actCamera.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Event/evtEventSystem.h"
#include "KingSystem/Event/evtUnk_7100dc816c.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Utils/MathUtil.h"

bool sub_7100EE7168(const ksys::map::Object* obj, sead::Matrix34f* out);

// Camera parameter globals (in .data / .bss). Nothing in the binary writes them or takes their
// address, yet the loads are not folded and do not go through the GOT: hidden visibility (as for
// ksys::gdt::detail::sCommonFlags0; KSYS_VISIBILITY_HIDDEN).
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474158 = 0.28f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_710247415c = -80.0f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474160 = 0.4f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474164 = 0.2f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474168 = 0.5f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_710247416c = 0.4f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474170 = 45.0f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474174 = 15.0f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474178 = 30.0f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_710247417c = 0.6f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474180 = 0.8f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474184 = 0.1f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474188 = 0.6f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_710247418c = 0.9f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474190 = 0.02f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474194 = 0.08f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474198 = 0.2f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_710247419c = 0.1f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_71024741a0 = 0.6f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_71025d24c8;
KSYS_VISIBILITY_HIDDEN f32 sUnk_71025d24cc;
KSYS_VISIBILITY_HIDDEN bool sUnk_71025d24d0;

bool sub_7100922030(u32 type, bool* is5) {
    if (type > 5)
        return false;
    if (is5)
        *is5 = type == 5;
    return true;
}

f32 sub_7100922058() {
    return 0.1f;
}

f32 sub_7100922064() {
    return 25000.0f;
}

bool sub_7100922070() {
    return false;
}

bool sub_7100922078() {
    return false;
}

s32 sub_7100922080() {
    return 16;
}

s32 sub_7100922088() {
    return 90;
}

f32 sub_7100922090() {
    return sUnk_7102474158;
}

f32 sub_710092209C() {
    return sUnk_710247415c;
}

f32 sub_71009220A8() {
    return sUnk_71025d24c8;
}

f32 sub_71009220B4() {
    return sUnk_7102474160;
}

f32 sub_71009220C0() {
    return sUnk_7102474164;
}

f32 sub_71009220CC() {
    return sUnk_7102474168;
}

f32 sub_71009220D8() {
    return sUnk_710247416c;
}

f32 sub_71009220E4() {
    return sUnk_7102474170;
}

f32 sub_71009220F0() {
    return sUnk_7102474174;
}

f32 sub_7100922120() {
    return 1.78f;
}

f32 sub_710092212C() {
    return 2.0f;
}

f32 sub_7100922134() {
    return 1.125f;
}

f32 sub_710092213C() {
    return 0.5f;
}

f32 sub_7100922144() {
    return 0.7f;
}

f32 sub_7100922150() {
    return 2.9f;
}

f32 sub_710092215C() {
    return 0.25f;
}

f32 sub_7100922164() {
    return 0.4f;
}

f32 sub_7100922170() {
    return 0.25f;
}

f32 sub_7100922178() {
    return 10.0f;
}

bool sub_7100922180() {
    return false;
}

f32 sub_7100922188() {
    return 0.005f;
}

f32 sub_7100922194() {
    return 0.0f;
}

f32 sub_710092219C() {
    return 0.023f;
}

f32 sub_71009221A8() {
    return 0.0f;
}

f32 sub_71009221B0() {
    return 5.0f;
}

bool sub_71009221B8() {
    return false;
}

f32 sub_71009221C0() {
    return 0.5f;
}

f32 sub_71009221C8() {
    return 0.005f;
}

f32 sub_71009221D4() {
    return 1.0f;
}

f32 sub_71009221DC() {
    return -1.5f;
}

f32 sub_71009221E4() {
    return 5.0f;
}

f32 sub_71009221EC() {
    return 0.1f;
}

f32 sub_71009221F8() {
    return 0.01f;
}

f32 sub_7100922204() {
    return 1.0f;
}

f32 sub_710092221C() {
    return 0.1f;
}

f32 sub_7100922228() {
    return 0.025f;
}

f32 sub_7100922234() {
    return 0.17f;
}

bool sub_7100922240() {
    return false;
}

bool sub_7100922248() {
    return false;
}

bool sub_7100922250() {
    return false;
}

bool sub_7100922258() {
    return true;
}

bool sub_7100922260() {
    return false;
}

bool sub_7100922268() {
    return false;
}

bool sub_7100922270() {
    return false;
}

bool sub_7100922278() {
    return false;
}

f32 sub_7100922280() {
    return 0.4f;
}

f32 sub_710092228C() {
    return 0.9f;
}

f32 sub_7100922298() {
    return 0.2f;
}

f32 sub_71009222A4() {
    return 0.7f;
}

f32 sub_71009222B0() {
    return 0.3f;
}

f32 sub_71009222BC() {
    return -30.0f;
}

f32 sub_71009222C4() {
    return 30.0f;
}

f32 sub_71009222CC() {
    return 2.0f;
}

f32 sub_71009222D4() {
    return 3.5f;
}

f32 sub_71009222DC() {
    return sUnk_7102474178;
}

f32 sub_71009222E8() {
    return 50.0f;
}

f32 sub_71009222F4() {
    return sUnk_710247417c;
}

f32 sub_7100922300() {
    return sUnk_7102474180;
}

f32 sub_710092230C() {
    return sUnk_7102474184;
}

f32 sub_7100922318() {
    return sUnk_7102474188;
}

f32 sub_7100922324() {
    return sUnk_710247418c;
}

f32 sub_7100922330() {
    return sUnk_7102474190;
}

f32 sub_710092233C() {
    return sUnk_71025d24cc;
}

f32 sub_7100922348() {
    return sUnk_7102474194;
}

f32 sub_7100922354() {
    return sUnk_7102474198;
}

f32 sub_7100922360() {
    return sUnk_710247419c;
}

f32 sub_710092236C() {
    return sUnk_71024741a0;
}

f32 sub_7100922378() {
    return 1.4f;
}

f32 sub_7100922384() {
    return 0.01f;
}

f32 sub_7100922390() {
    return 0.2f;
}

f32 sub_710092239C() {
    return 0.6f;
}

bool sub_71009223D8() {
    return false;
}

bool sub_71009223E0() {
    return false;
}

bool sub_71009223E8() {
    return false;
}

s32 sub_71009223F0() {
    return 0;
}

f32 sub_7100922418() {
    return 1.5f;
}

f32 sub_7100922420() {
    return 30.0f;
}

bool sub_7100922428() {
    return true;
}

f32 sub_71009220FC(s32 idx) {
    switch (idx) {
    case 0:
        return 0.8f;
    case 1:
        return 1.2f;
    case 2:
        return 1.6f;
    case 3:
        return 2.0f;
    case 4:
        return 2.4f;
    default:
        return 1.6f;
    }
}

void setFlagToOne() {
    sUnk_71025d24d0 = true;
}

void sub_71009223B8() {
    sUnk_71025d24d0 = false;
}

// NON_MATCHING: the original negates the loaded byte with mvn/and (no bool range assumption).
bool sub_71009223C4() {
    return !sUnk_71025d24d0;
}

f32 sub_71009223F8(s32 idx) {
    static const f32 sTable[] = {40.0f, 2.0f, 2.0f, 50.0f, 2.0f, 30.0f, 2.0f};
    return sTable[idx];
}

f32 sub_7100922408(s32 idx) {
    static const f32 sTable[] = {60.0f, 0.7f, 3.0f, 50.0f, 1.2f, 0.0f, 2.0f};
    return sTable[idx];
}

f32 angleStuff(f32 deg) {
    if (deg < -180.0f) {
        const f32 d = -180.0f - deg;
        const s32 i = d;
        const s32 m = i / 360 * 360;
        f32 n;
        if (i == d && i - m == 0)
            n = i;
        else
            n = m + (i < 0 ? -360 : 360);
        return n + deg;
    }
    if (deg >= 180.0f) {
        const f32 d = deg + 180.0f;
        const s32 i = d;
        const s32 m = i / 360 * 360;
        f32 n;
        if (i == d && i - m == 0)
            n = i;
        else
            n = m;
        return deg - n;
    }
    return deg;
}






















f32 sub_7100922530(const f32& deg) {
    return angleStuff(deg + 180.0f);
}

void sub_7100922600(f32& deg) {
    deg = angleStuff(deg + 180.0f);
}

f32 sub_71009226D8(const f32& deg) {
    return deg < 0 ? -deg : deg;
}

f32 sub_71009226EC(const f32& deg) {
    return std::cos(deg * (sead::Mathf::pi() / 180.0f));
}

namespace uking::act {

void CameraTargetResult::sub_7100923ECC(ksys::act::ActorConstDataAccess* accessor) {
    if (accessor && accessor->getProc()) {
        accessor->linkAcquire(&link);
        object = nullptr;
        kind = 1;
    }
}

void CameraTargetResult::sub_7100923F0C(ksys::map::Object* target) {
    if (target) {
        link.reset();
        object = target;
        kind = 2;
    }
}

void CameraTargetLink::sub_71009240C0(CameraTargetResult* result) {
    if (kind == 1) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (accessor.getProc()) {
            accessor.linkAcquire(&result->link);
            result->object = nullptr;
            result->kind = 1;
        }
    } else if (kind == 2) {
        s32 resolved_index = index;
        auto* object = ksys::act::findLinkReferenceObj(&link, "", "", &resolved_index);
        if (object && resolved_index == index) {
            result->link.reset();
            result->object = object;
            result->kind = 2;
        }
    }
}

// NON_MATCHING: temporary stack placement and matrix/translation copy scheduling differ.
void Unk_71009241ac::sub_71009242AC(Camera* camera) {
    CameraTargetResult result;
    CameraTargetLink target_link;
    sub_71009243FC(camera, selector, actorName, uniqueName, &result, &target_link);
    if (result.kind == 1) {
        bool valid;
        {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&result.link, &accessor);
            valid = sub_710092479C(accessor);
        }
        if (!valid)
            return;
        status = 1;
    } else if (result.kind == 2) {
        if (!result.object)
            return;
        sead::Matrix34f mtx = sead::Matrix34f::ident;
        if (!sub_7100EE7168(result.object, &mtx) || ksys::util::sub_71011F10F4(mtx))
            return;
        matrix = mtx;
        previousPos = mtx.getTranslation();
        position = mtx.getTranslation();
        status = 2;
    } else {
        return;
    }
    targetLink.link = target_link.link;
    targetLink.index = target_link.index;
    targetLink.kind = target_link.kind;
}

// NON_MATCHING: the kind snapshot stays in a register; stack placement and copy scheduling differ.
void Unk_71009241ac::sub_710092464C() {
    if (targetLink.kind == 0)
        return;
    CameraTargetResult result;
    targetLink.sub_71009240C0(&result);
    const s32 kind = result.kind;
    if (kind == 0)
        return;
    if (selector == 4) {
        if (!result.object)
            return;
        if (auto* actor = result.object->tryGetActor(false)) {
            ksys::act::ActorConstDataAccess accessor(actor);
            sub_710092479C(accessor);
            return;
        }
    } else if (kind == 1) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&result.link, &accessor);
        sub_710092479C(accessor);
        return;
    } else if (kind != 2) {
        return;
    }
    if (!result.object)
        return;
    sead::Matrix34f mtx = sead::Matrix34f::ident;
    if (!sub_7100EE7168(result.object, &mtx) || ksys::util::sub_71011F10F4(mtx))
        return;
    matrix = mtx;
    previousPos = mtx.getTranslation();
    position = mtx.getTranslation();
}

// NON_MATCHING: clang duplicates the player branch and shares different branch/destructor tails.
void sub_71009243FC(ksys::act::Actor* actor, s32 selector, const sead::SafeString& name,
                    const sead::SafeString& unique_name, CameraTargetResult* result,
                    CameraTargetLink* target_link) {
    if (!actor)
        return;
    switch (selector) {
    case 0: {
        auto& actor_link = ksys::evt::sub_7100DC85D4(actor);
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&actor_link, &accessor);
        if (accessor.getProc()) {
            accessor.linkAcquire(&result->link);
            result->object = nullptr;
            result->kind = 1;
        }
        target_link->link = actor_link;
        target_link->kind = 1;
        break;
    }
    case 1: {
        ksys::act::ActorConstDataAccess accessor;
        if (auto* info = ksys::act::PlayerInfo::instance())
            ksys::act::acquireActor(&info->getPlayerLink(), &accessor);
        if (accessor.getProc()) {
            accessor.linkAcquire(&result->link);
            result->object = nullptr;
            result->kind = 1;
        }
        accessor.linkAcquire(&target_link->link);
        target_link->kind = 1;
        break;
    }
    case 2: {
        ksys::act::ActorConstDataAccess accessor;
        ksys::evt::EventSystem::instance()->sub_71008ABF38(&accessor);
        if (!accessor.getProc()) {
            auto& actor_link = ksys::evt::sub_7100DC85D4(actor);
            if (actor_link.hasProc())
                ksys::act::acquireActor(&actor_link, &accessor);
        }
        if (accessor.getProc()) {
            accessor.linkAcquire(&result->link);
            result->object = nullptr;
            result->kind = 1;
        }
        accessor.linkAcquire(&target_link->link);
        target_link->kind = 1;
        break;
    }
    case 3:
        sub_7100924A4C(actor, name, unique_name, result);
        if (result->kind == 1) {
            target_link->link = result->link;
            target_link->kind = 1;
        }
        break;
    case 4: {
        auto& actor_link = ksys::evt::sub_7100DC85D4(actor);
        s32 index = 0;
        auto* object = ksys::act::findLinkReferenceObj(&actor_link, name, unique_name, &index);
        if (!object)
            return;
        if (auto* target = object->tryGetActor(false)) {
            ksys::act::ActorConstDataAccess accessor(target);
            if (accessor.getProc()) {
                accessor.linkAcquire(&result->link);
                result->object = nullptr;
                result->kind = 1;
            }
        } else {
            result->link.reset();
            result->object = object;
            result->kind = 2;
        }
        target_link->link = actor_link;
        target_link->index = index;
        target_link->kind = 2;
        break;
    }
    }
}

Unk_71009241ac::Unk_71009241ac()
    : selector(-1), matrix(sead::Matrix34f::ident), previousPos(sead::Vector3f::zero),
      position(sead::Vector3f::zero), status(0) {}

void Unk_71009241ac::sub_7100924238(const Params& params) {
    selector = -1;
    targetLink.link.reset();
    targetLink.index = -1;
    targetLink.kind = 0;
    status = 0;
    if (params.selector) {
        selector = u32(*params.selector) + 1 < 6 ? *params.selector : -1;
        actorName = params.actorName;
        uniqueName = params.uniqueName;
    }
}


bool Unk_71009241ac::sub_710092479C(const ksys::act::ActorConstDataAccess& accessor) {
    if (!accessor.getProc())
        return false;
    const auto& mtx = accessor.getActorMtx();
    if (ksys::util::sub_71011F10F4(mtx))
        return false;
    const auto& prev = accessor.getPreviousPos2();
    if (ksys::util::sub_71011F1040(prev))
        return false;
    const auto& pos = accessor.getField458_Vec3();
    if (ksys::util::sub_71011F1040(pos))
        return false;
    matrix = mtx;
    previousPos = prev;
    position = pos;
    return true;
}

Unk_7100922700::Unk_7100922700(f32 r, f32 a, f32 b) {
    set(r, a, b);
}

Unk_7100922700& Unk_7100922700::set(f32 r, f32 a, f32 b) {
    _0 = r;
    _4 = angleStuff(a);
    _8 = angleStuff(b);
    sub_7100922B1C();
    return *this;
}

Unk_7100922700::Unk_7100922700(const sead::Vector3f& v) {
    set(v);
}

Unk_7100922700& Unk_7100922700::set(const sead::Vector3f& v) {
    const f32 x = v.x;
    const f32 y = v.y;
    const f32 z = v.z;
    const f64 xx = x * x;
    const f64 yy = y * y;
    const f64 zz = z * z;
    const f64 xz2 = xx + zz;
    const f64 len2 = yy + xz2;
    f32 xz = 0;
    if (xz2 > 0)
        xz = std::sqrt(xz2);
    f32 len = 0;
    if (len2 > 0)
        len = std::sqrt(len2);
    _0 = len;
    _4 = angleStuff((sead::Mathf::piHalf() - std::atan2(xz, y)) * (180.0f / sead::Mathf::pi()));
    _8 = angleStuff(std::atan2(x, z) * (180.0f / sead::Mathf::pi()));
    sub_7100922B1C();
    return *this;
}


// NON_MATCHING: the original keeps separate copies of the inlined angle wrapping in the two
// pitch branches (ours shares one).
Unk_7100922700* Unk_7100922700::sub_7100922B1C() {
    if (_0 < 0) {
        _0 = -_0;
        _4 = angleStuff(-_4);
        _8 = angleStuff(angleStuff(_8 + 180.0f));
    }
    if (_4 < -90.0f) {
        _4 = angleStuff(_4 + 180.0f);
        _8 = angleStuff(angleStuff(_8 + 180.0f));
    } else if (_4 > 90.0f) {
        _4 = angleStuff(-180.0f - _4);
        _8 = angleStuff(angleStuff(_8 + 180.0f));
    }
    return this;
}

sead::Vector3f Unk_7100922700::sub_7100923254() const {
    const f32 ca = std::cos(_4 * (sead::Mathf::pi() / 180.0f));
    const f32 sa = std::sin(_4 * (sead::Mathf::pi() / 180.0f));
    const f32 cb = std::cos(_8 * (sead::Mathf::pi() / 180.0f));
    const f32 sb = std::sin(_8 * (sead::Mathf::pi() / 180.0f));
    const f32 h = ca * _0;
    return {sb * h, sa * _0, cb * h};
}

s32 sub_7100923494(s32 n) {
    if (n >= 3)
        return n * sub_7100923494(n - 1);
    if (n > 0)
        return n;
    return n == 0 ? 1 : -1;
}


Unk_71024741b8::Unk_71024741b8() = default;

void Unk_71024741b8::set(f32 p0, f32 p1, f32 p2, f32 p3, f32 w1, f32 w2) {
    _8 = p0;
    _c = p1;
    _10 = p2;
    _14 = p3;
    _18 = sead::Mathf::clampMin(w1, 0.0f);
    _1c = sead::Mathf::clampMin(w2, 0.0f);
}

}  // namespace uking::act

bool sub_7100926210(const ksys::act::ActorConstDataAccess& accessor, sead::Vector3f* out) {
    const sead::Vector3f* pos;
    if (accessor.isPlayerProfile()) {
        ksys::act::acc::PlayerBase player;
        player.acquireActor(accessor);
        pos = &player.getLookAtPosForCamera();
    } else {
        pos = &accessor.getPreviousPos2();
    }
    const bool invalid = ksys::util::sub_71011F1040(*pos);
    if (!invalid)
        *out = *pos;
    return !invalid;
}

bool sub_7100926DF0(const ksys::act::ActorConstDataAccess& accessor) {
    return uking::act::sub_7100E6ECC4(accessor) == 6;
}

bool sub_7100926E0C() {
    ksys::act::ActorConstDataAccess accessor;
    bool result = false;
    if (auto* info = ksys::act::PlayerInfo::instance()) {
        if (ksys::act::acquireActor(&info->getHorseLink(), &accessor))
            result = uking::act::sub_7100E6ECC4(accessor) == 8;
    }
    return result;
}

bool sub_7100926E7C(const ksys::act::ActorConstDataAccess& accessor) {
    return uking::act::sub_7100E6ECC4(accessor) == 8;
}

bool sub_710092634C(const ksys::act::ActorConstDataAccess& accessor, sead::Vector3f* out) {
    const sead::Vector3f& pos = accessor.getPreviousPos2();
    const bool valid = !ksys::util::sub_71011F1040(pos);
    if (valid)
        *out = pos;
    return valid;
}

bool sub_7100926398(const ksys::act::ActorConstDataAccess& accessor, sead::Vector3f* out) {
    const sead::Vector3f& pos = accessor.getField458_Vec3();
    const bool valid = !ksys::util::sub_71011F1040(pos);
    if (valid)
        *out = pos;
    return valid;
}

bool sub_71009263E4(const ksys::act::ActorConstDataAccess& accessor, sead::Vector3f* out) {
    const sead::Vector3f& pos = accessor.getVelocity();
    const bool valid = !ksys::util::sub_71011F1040(pos);
    if (valid)
        *out = pos;
    return valid;
}
