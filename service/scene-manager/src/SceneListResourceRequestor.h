//******************************************************************
//
// Copyright 2016 Samsung Electronics All Rights Reserved.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef SM_SCENELIST_RESOURCE_REQUESTOR_H_
#define SM_SCENELIST_RESOURCE_REQUESTOR_H_

#include "SceneCommons.h"
#include "RCSRemoteResourceObject.h"
#include "RCSRepresentation.h"
#include "RemoteSceneUtils.h"

namespace OIC
{
    namespace Service
    {

        class SceneListResourceRequestor
            : public std::enable_shared_from_this< SceneListResourceRequestor >
        {
            public:
                typedef std::shared_ptr< SceneListResourceRequestor > Ptr;
                typedef std::weak_ptr< SceneListResourceRequestor > wPtr;

                typedef std::function
                < void(const std::string &link, const std::string &id,
                       const std::string &name, int eCode) >
                InternalCreateSceneCollectionCallback;

                typedef std::function
                < void(int eCode) > InternalSetNameCallback;


            public:
                SceneListResourceRequestor(RCSRemoteResourceObject::Ptr pSceneList);
                ~SceneListResourceRequestor();

                void requestSceneCollectionCreation
                (const std::string &name, InternalCreateSceneCollectionCallback);

                void requestSetName(const std::string &, InternalSetNameCallback);

                void requestGet(const std::string &, RCSRemoteResourceObject::GetCallback);

                RCSRemoteResourceObject::Ptr getRemoteResourceObject();


            private:
                static void onSceneCollectionCreated
                (const HeaderOpts &, const RCSRepresentation &, int eCode,
                 const std::string &name, const InternalCreateSceneCollectionCallback &,
                 SceneListResourceRequestor::wPtr);

                void onSceneCollectionCreated_impl
                (const HeaderOpts &, const RCSRepresentation &, int eCode,
                 const std::string &name, const InternalCreateSceneCollectionCallback &);

                std::vector<std::pair<RCSResourceAttributes, std::vector<RCSResourceAttributes>>>
               parseSceneListFromAttributes(const RCSResourceAttributes &);

               std::vector<RCSResourceAttributes> getChildrenAttributes(
                       const RCSResourceAttributes &) const;

               RCSRemoteResourceObject::Ptr makeSceneRemoteResourceFromAttributes(
                       const RCSResourceAttributes &, const SceneResource &);


            private:
                RCSRemoteResourceObject::Ptr m_SceneListResourcePtr;
        };

    }
}

#endif /* SM_SCENELIST_RESOURCE_REQUESTOR_H_ */
