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

#include "RCSRequest.h"
#include "OCApi.h"
#include "SceneListResource.h"

namespace OIC
{
    namespace Service
    {
        SceneListResource::SceneListResource()
        : m_SceneListName(), m_SceneListObj(), m_RequestHandler()
        {
            m_SceneListObj = RCSResourceObject::Builder(
                    SCENE_LIST_URI, SCENE_LIST_RT, OC_RSRVD_INTERFACE_DEFAULT).
                            addInterface(OC::BATCH_INTERFACE).
                            setDiscoverable(true).setObservable(false).build();

            {
                RCSResourceObject::LockGuard guard(m_SceneListObj);
                m_SceneListObj->setAttribute(SCENE_KEY_NAME, SCENE_LIST_DEFAULT_NAME);
                m_SceneListObj->setAttribute(SCENE_KEY_RTS, SCENE_LIST_RT);
            }

            m_SceneListObj->setSetRequestHandler(&SceneListRequestHandler::onSetRequest);
        }

        SceneListResource * SceneListResource::getInstance()
        {
            static SceneListResource instance;
            return & instance;
        }

        void SceneListResource::addSceneCollectionResource(
                SceneCollectionResource::Ptr newObject)
        {
            std::unique_lock<std::mutex> collectionlock(m_SceneCollectionLock);
            m_SceneCollections.push_back(newObject);
            m_SceneListObj->bindResource(newObject->getRCSResourceObject());
        }

        std::string SceneListResource::getName() const
        {
            return m_SceneListName;
        }

        void SceneListResource::setName(std::string && newName)
        {
            m_SceneListName = newName;

            RCSResourceObject::LockGuard guard(m_SceneListObj);
            m_SceneListObj->setAttribute(SCENE_KEY_NAME, m_SceneListName);
        }

        void SceneListResource::setName(const std::string & newName)
        {
            setName(std::string(newName));
        }

        const std::vector<SceneCollectionResource::Ptr>
        SceneListResource::getSceneCollections()
        {
            std::unique_lock<std::mutex> collectionlock(m_SceneCollectionLock);
            std::vector<SceneCollectionResource::Ptr> retCollections(m_SceneCollections);
            return retCollections;
        }

        RCSSetResponse
        SceneListResource::SceneListRequestHandler::onSetRequest(
                const RCSRequest & request, RCSResourceAttributes & attributes)
        {
            if (request.getInterface() != OC::BATCH_INTERFACE)
            {
                return RCSSetResponse::create(attributes, SCENE_CLIENT_BADREQUEST).
                        setAcceptanceMethod(RCSSetResponse::AcceptanceMethod::IGNORE);
            }

            auto newObject
                = SceneCollectionResource::createSceneCollectionObject();

            if (attributes.contains(SCENE_KEY_NAME))
            {
                newObject->setName(attributes.at(SCENE_KEY_NAME).get<std::string>());
            }

            SceneListResource::getInstance()->addSceneCollectionResource(newObject);

            auto responseAtt = attributes;
            responseAtt[SCENE_KEY_NAME] = RCSResourceAttributes::Value(newObject->getName());
            responseAtt[SCENE_KEY_ID] = RCSResourceAttributes::Value(newObject->getId());

            auto uri = COAP_TAG + newObject->getAddress() + newObject->getUri();
            responseAtt[SCENE_KEY_PAYLOAD_LINK]
                        = RCSResourceAttributes::Value(uri);

            return RCSSetResponse::create(responseAtt, SCENE_RESPONSE_SUCCESS).
                    setAcceptanceMethod(RCSSetResponse::AcceptanceMethod::IGNORE);
        }
    }
}