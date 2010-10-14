#ifndef MILX_PLUGINS_H
#define MILX_PLUGINS_H

#include <string>

namespace milx {
  class Application;
  class PluginManager;
  struct Plugin {
    friend class PluginManager;
    unsigned int version;
    std::string name;
   private:
    void* _plugin_mem;
  };
}

#define MILX_PLUGIN_LOAD "milx_plugin_load"
extern "C" void milx_plugin_load(milx::Application& app, milx::Plugin& plug);

#endif
