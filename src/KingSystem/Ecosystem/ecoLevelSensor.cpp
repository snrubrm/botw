#include "KingSystem/Ecosystem/ecoLevelSensor.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::eco {

LevelSensor::LevelSensor() = default;

LevelSensor::~LevelSensor() {
    mResHandle.requestUnload2();
    if (mRootIter)
        delete mRootIter;
}

void LevelSensor::init(sead::Heap* heap) {
    res::LoadRequest req;
    req.mRequester = "LevelSensor";
    mResHandle.load("Ecosystem/LevelSensor.byml", &req);
    auto* res = sead::DynamicCast<sead::DirectResource>(mResHandle.getResource());
    mRootIter = new (heap) al::ByamlIter(res->getRawData());
}

// NON_MATCHING: loop layout and the "return" flag handling of the inner loop differ
bool LevelSensor::scaleWeapon(const sead::SafeString& weapon, WeaponModifier min_modifier,
                              const char** scaled_weapon, WeaponModifier* scaled_modifier,
                              act::Actor* actor) const {
    if (actor) {
        if (auto* obj = actor->getMapObject()) {
            const sead::Vector3f pos = obj->getTranslate();
            if (world::Manager::instance()->isAocField())
                return false;
            if (Ecosystem::instance()->getFieldMapArea(pos.x, pos.z) == 28)
                return false;
        } else {
            sead::Vector3f pos;
            actor->getMtx().getTranslation(pos);
            if (world::Manager::instance()->isAocField())
                return false;
            if (Ecosystem::instance()->getFieldMapArea(pos.x, pos.z) == 28)
                return false;
        }
    }

    al::ByamlIter weapon_iter;
    if (!mRootIter->tryGetIterByKey(&weapon_iter, "weapon"))
        return false;

    for (int i = 0; i < weapon_iter.getSize(); ++i) {
        al::ByamlIter weapon_table;
        if (!weapon_iter.tryGetIterByIndex(&weapon_table, i))
            return false;

        al::ByamlIter actors;
        if (!weapon_table.tryGetIterByKey(&actors, "actors"))
            return false;

        for (int j = 0; j < actors.getSize() - 1; ++j) {
            al::ByamlIter actor_iter;
            const char* name;
            if (!actors.tryGetIterByIndex(&actor_iter, j))
                return false;
            if (!actor_iter.tryGetStringByKey(&name, "name"))
                return false;

            f32 value;
            int plus;
            if (!actor_iter.tryGetFloatByKey(&value, "value"))
                return false;
            if (!actor_iter.tryGetIntByKey(&plus, "plus"))
                return false;

            if (min_modifier == WeaponModifier::None) {
                if (plus != -1)
                    continue;
            } else if (min_modifier == WeaponModifier::Blue) {
                if (plus != 0)
                    continue;
            } else if (min_modifier != WeaponModifier::Yellow || plus != 1) {
                continue;
            }

            if (value >= mWeaponPoints)
                continue;

            if (weapon != sead::SafeString(name))
                continue;

            bool not_rank_up = false;
            if (!weapon_table.tryGetBoolByKey(&not_rank_up, "not_rank_up"))
                return false;

            al::ByamlIter next_iter;
            f32 next_value = 0.0;
            int next_idx = -1;
            for (int k = j + 1; k < actors.getSize(); ++k) {
                if (!actors.tryGetIterByIndex(&next_iter, k))
                    return false;
                if (!next_iter.tryGetFloatByKey(&next_value, "value"))
                    return false;

                if (not_rank_up) {
                    const char* next_name;
                    if (!next_iter.tryGetStringByKey(&next_name, "name"))
                        return false;
                    if (weapon != sead::SafeString(next_name))
                        continue;
                }

                next_idx = k;
                if (mWeaponPoints <= next_value)
                    break;
            }

            if (next_idx < 0)
                return false;

            if (!actors.tryGetIterByIndex(&next_iter, next_idx))
                return false;

            const char* scaled_name;
            if (!next_iter.tryGetStringByKey(&scaled_name, "name"))
                return false;

            const char* series;
            if (!weapon_table.tryGetStringByKey(&series, "series"))
                return false;

            const char* actor_type;
            if (!weapon_table.tryGetStringByKey(&actor_type, "actorType"))
                return false;

            int scaled_plus;
            if (!next_iter.tryGetIntByKey(&scaled_plus, "plus"))
                return false;

            *scaled_weapon = scaled_name;
            if (scaled_plus == 0)
                *scaled_modifier = WeaponModifier::Blue;
            else if (scaled_plus == 1)
                *scaled_modifier = WeaponModifier::Yellow;
            else
                *scaled_modifier = WeaponModifier::None;
            return true;
        }
    }

    return false;
}

// NON_MATCHING: stack slot assignment and some store scheduling
bool LevelSensor::scaleActor(const sead::SafeString& name, map::Object* obj,
                             const char** scaled_name, act::InstParamPack* pack,
                             const sead::Vector3f& position) const {
    if (world::Manager::instance()->isAocField())
        return false;
    if (Ecosystem::instance()->getFieldMapArea(position.x, position.z) == 28)
        return false;

    if (name.startsWith("Enemy")) {
        int mode = 0;
        if (obj->getMubinIter().tryGetParamIntByKey(&mode, "LevelSensorMode") && mode > 0) {
            al::ByamlIter enemy_iter;
            if (!mRootIter->tryGetIterByKey(&enemy_iter, "enemy"))
                return false;

            for (int i = 0; i < enemy_iter.getSize(); ++i) {
                al::ByamlIter enemy_table;
                if (!enemy_iter.tryGetIterByIndex(&enemy_table, i))
                    return false;

                al::ByamlIter actors;
                if (!enemy_table.tryGetIterByKey(&actors, "actors"))
                    return false;

                for (int j = 0; j < actors.getSize() - 1; ++j) {
                    al::ByamlIter actor_iter;
                    if (!actors.tryGetIterByIndex(&actor_iter, j))
                        return false;

                    const char* actor_name;
                    if (!actor_iter.tryGetStringByKey(&actor_name, "name"))
                        return false;

                    f32 value;
                    if (!actor_iter.tryGetFloatByKey(&value, "value"))
                        return false;

                    if (!(value < mEnemyPoints) || name != sead::SafeString(actor_name))
                        continue;

                    al::ByamlIter next_iter;
                    for (int k = j + 1; k < actors.getSize();) {
                        if (!actors.tryGetIterByIndex(&next_iter, k))
                            return false;
                        f32 next_value;
                        if (!next_iter.tryGetFloatByKey(&next_value, "value"))
                            return false;
                        ++k;
                        if (mEnemyPoints <= next_value)
                            break;
                    }

                    const char* scaled;
                    if (!next_iter.tryGetStringByKey(&scaled, "name"))
                        return false;
                    const char* species;
                    if (!enemy_table.tryGetStringByKey(&species, "species"))
                        return false;

                    *scaled_name = scaled;
                    return true;
                }
            }
        }
    }

    if (name.startsWith("Weapon")) {
        int mode = 0;
        if (obj->getMubinIter().tryGetParamIntByKey(&mode, "LevelSensorMode") && mode > 0) {
            int judge_type = 0;
            if (!obj->getMubinIter().tryGetParamIntByKey(&judge_type, "SharpWeaponJudgeType"))
                return false;

            const auto modifier = act::getRandomWeaponModifier(WeaponModifier(judge_type),
                                                               obj->getUnitConfigName());
            const char* scaled_weapon;
            WeaponModifier scaled_modifier;
            if (scaleWeapon(obj->getUnitConfigName(), modifier, &scaled_weapon,
                            &scaled_modifier, nullptr)) {
                pack->getBuffer().add(int(scaled_modifier), "SharpWeaponJudgeType");
                *scaled_name = scaled_weapon;
                return true;
            }
        }
    }

    return false;
}

void LevelSensor::calculatePoints() {
    if (mDefaultPoints >= 0) {
        mPoints = mDefaultPoints;
    } else {
        al::ByamlIter flag;
        if (!mRootIter->tryGetIterByKey(&flag, "flag")) {
            return;
        }
        float point_sum = 0;
        for (int index = 0; index < flag.getSize(); index++) {
            al::ByamlIter iter_enemy;
            if (!flag.tryGetIterByIndex(&iter_enemy, index)) {
                return;
            }
            const char* name;
            if (!iter_enemy.tryGetStringByKey(&name, "name")) {
                return;
            }
            s32 kill_count = 0;
            if (!gdt::Manager::instance()->getParam().get().getS32(&kill_count, name)) {
                bool unique_kill = false;
                if (gdt::Manager::instance()->getParam().get().getBool(&unique_kill, name)) {
                    if (unique_kill) {
                        kill_count = 1;
                    }
                }
            }
            if (kill_count > 0) {
                f32 point;
                if (!iter_enemy.tryGetFloatByKey(&point, "point")) {
                    return;
                }
                point_sum += point * kill_count;
            }
        }
        mPoints = point_sum;
    }
    al::ByamlIter setting_iter;
    if (mRootIter->tryGetIterByKey(&setting_iter, "setting")) {
        f32 Level2WeaponPower;
        f32 Level2EnemyPower;
        if (setting_iter.tryGetFloatByKey(&Level2WeaponPower, "Level2WeaponPower") &&
            setting_iter.tryGetFloatByKey(&Level2EnemyPower, "Level2EnemyPower")) {
            mWeaponPoints = mPoints * Level2WeaponPower;
            mEnemyPoints = mPoints * Level2EnemyPower;
        }
    }
}

}  // namespace ksys::eco
