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

#ifndef REMOTE_SCENE_UTILS_H
#define REMOTE_SCENE_UTILS_H

#include <cassert>

#include "OCApi.h"
#include "logger.h"
#include "RCSRemoteResourceObject.h"
#include "OCPlatform.h"
#include "SceneCommons.h"

#define SCENE_CLIENT_PRINT_LOG(strError) \
        OIC_LOG_V(ERROR, "[SCENE_CLIENT]", "%s:%d %s", __PRETTY_FUNCTION__, __LINE__, strError);

#define SCENE_CLIENT_ASSERT_NOT_NULL(Val) \
        { \
            if (!(Val)) \
            { \
                SCENE_CLIENT_PRINT_LOG("NULL value"); \
                assert(Val); \
                return; \
            } \
        }

namespace OIC
{
    namespace Service
    {

        const OCConnectivityType SCENE_CONNECTIVITY = CT_ADAPTER_IP;
        const std::string SCENE_CLIENT_REQ_IF = OC::DEFAULT_INTERFACE;
        const std::string SCENE_CLIENT_CREATE_REQ_IF = OC::BATCH_INTERFACE;

        enum class SceneResource
        {
            List = 0,
            Collection,
            Member
        };

        // This function will be moved to SceneUtills.cpp
        RCSRemoteResourceObject::Ptr createRCSResourceObject(
            const std::string &address, const OCConnectivityType ct,
            const std::vector< std::string > &vecRT, const std::vector< std::string > &vecIF);

    }
}

#endif // REMOTE_SCENE_UTILS_H