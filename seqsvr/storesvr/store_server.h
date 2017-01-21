/*
 *  Copyright (c) 2016, https://github.com/nebula-im
 *  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// TODO(@benqi): 使用zrpc-code-gen代码生成工具自动生成

#ifndef	STORESVR_STORE_SERVER_H_
#define	STORESVR_STORE_SERVER_H_

#include <folly/io/async/EventBase.h>

#include "nebula/base/configurable.h"
#include "nebula/net/base_server.h"

struct StoreConfig : public nebula::Configurable {
  virtual ~StoreConfig() = default;
  
  // Override from Configurable
  bool SetConf(const std::string& conf_name, const folly::dynamic& conf) override {
    folly::dynamic v = nullptr;
    
    v = Configurable::GetConfigValue(conf, "store_path");
    if (v.isString()) store_path = v.asString();
    v = Configurable::GetConfigValue(conf, "set_id");
    if (v.isInt()) set_id = static_cast<int>(v.asInt());

    return true;
  }
  
  std::string store_path;
  int set_id {0};
};

class StoreServer : public nebula::BaseServer {
public:
  StoreServer();
  ~StoreServer() override = default;
  
protected:
  bool Initialize() override;
  
  bool Run() override {
    BaseServer::Run();
    return true;
  }
  
  StoreConfig store_config_;
};

#endif // STORESVR_STORE_SERVER_H_
