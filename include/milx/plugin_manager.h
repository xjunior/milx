#ifndef MILX_PLUGIN_MANAGER_H
#define MILX_PLUGIN_MANAGER_H

#include <milx/module.h>
#include <vector>
#include <memory>

namespace milx {
  struct Plugin;
  class PluginManager {
    std::vector<Plugin*> _plugins;
    Application& _app;
   public:
    PluginManager(Application& app) : _app(app) { }
    void load(const milx::Path& path);
    ~PluginManager();
  };
}

#endif // MILX_PLUGIN_MANAGER_H
