#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckDistanceForWarp : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckDistanceForWarp, Query)
public:
    explicit CheckDistanceForWarp(const InitArg& arg);
    ~CheckDistanceForWarp() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
    // 0x7100689298 (CSV m13): whether the player is at least 500 (XZ) away from the warp destination (true when
    // the destination is unknown or there is no player).
    virtual bool m13();

protected:
    sead::SafeString mWarpDestMapName{};
    sead::SafeString mWarpDestPosName{};
};

}  // namespace uking::query
