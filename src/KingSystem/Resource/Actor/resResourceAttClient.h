#pragma once

#include <container/seadBuffer.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <utility/aglParameter.h>
#include <utility/aglParameterList.h>
#include <utility/aglParameterObj.h>
#include "KingSystem/ActorSystem/Attention/actAttention.h"
#include "KingSystem/Resource/Actor/resResourceAttPos.h"
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
class ActorConstDataAccess;
}  // namespace ksys::act

namespace ksys::res {

struct AttCheck_Unk1;

class AttCheck;

class AttClient : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(AttClient, Resource)
public:
    AttClient() : ParamIO("atcl", 0) {}
    ~AttClient() override;

    act::AttType getAttType() const { return mAttType; }
    act::AttActionCode getActionCode() const { return mActionCode; }
    act::AttPriorityType getPriorityType() const { return mPriorityType; }
    const sead::SafeString& getPriorityTypeStr() const { return mPriorityTypeStr; }
    const sead::Buffer<AttCheck*>& getChecks() const { return mChecks; }

    int getNumChecks() const;

    // 0x71010945d4 (CSV res::AttClient::checkM4; lane4 s50, declaration only, name is a guess): AttClient::sub_7100D72178
    // passes the actor and the client's matrix buffer.
    void checkM4(act::Actor* actor, sead::Buffer<sead::Matrix34f>* mtxs);

    // 0x7101094670 (CSV res::AttClient::check): runs every check with the matching matrix of
    // `mtxs`; returns the index of the first failing check, -1 if all pass, -2 if `mtxs` is too
    // small.
    int check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
              const sead::Buffer<sead::Matrix34f>& mtxs, const sead::Vector3f& pos,
              const AttCheck_Unk1* arg, bool a6, bool a7) const;

    void appendPriority(sead::BufferedSafeString* str);

    void doCreate_(u8*, u32, sead::Heap*) override;
    bool needsParse() const override { return true; }
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

private:
    act::AttType mAttType = act::AttType::Action;
    act::AttActionCode mActionCode = act::AttActionCode::None;
    act::AttPriorityType mPriorityType = act::AttPriorityType::Default;
    sead::FixedSafeString<32> mPriorityTypeStr;
    agl::utl::ParameterObj mAttClientParamsObj;
    agl::utl::Parameter<sead::FixedSafeString<32>> mAttTypeParam;
    agl::utl::Parameter<sead::FixedSafeString<32>> mActionTypeParam;
    agl::utl::Parameter<sead::FixedSafeString<32>> mPriorityTypeParam;
    sead::Buffer<AttCheck*> mChecks;
};
KSYS_CHECK_SIZE_NX150(AttClient, 0x428);

class AttClientList : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(AttClientList, Resource)
public:
    struct Client {
        const char* getFileName() const { return file_name.ref().cstr(); }

        agl::utl::Parameter<sead::SafeString> name;
        agl::utl::Parameter<sead::SafeString> file_name;
        agl::utl::Parameter<bool> is_valid;
        agl::utl::ParameterObj obj;
        AttClient* client;
    };
    KSYS_CHECK_SIZE_NX150(Client, 0xa8);

    AttClientList() : ParamIO("atcllist", 0) {}
    ~AttClientList() override;
    AttClientList(const AttClientList&) = delete;
    auto operator=(const AttClientList&) = delete;

    const AttPos& getAttPos() const { return mAttPos; }
    bool isForceEdit() const;
    const sead::Buffer<Client>& getClients() const { return mClients; }

    // 0x000000710109308c
    void x(sead::Vector3f* out, act::Actor* actor, const gsys::BoneAccessKey* key) const;

    void addClient_(s32 index, AttClient* client) { mClients[index].client = client; }

    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;
    bool needsParse() const override { return true; }
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;
    bool finishParsing_() override;
    bool m7_() override;

private:
    agl::utl::ParameterList mAttClientsList;
    agl::utl::ParameterObj mAttPosObj;
    AttPos mAttPos;
    agl::utl::Parameter<bool> mForceEdit;
    sead::Buffer<Client> mClients;
};
KSYS_CHECK_SIZE_NX150(AttClientList, 0x3f0);

}  // namespace ksys::res
