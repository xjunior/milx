#ifndef MILX_PLUGIN_MANAGER_H
#define MILX_PLUGIN_MANAGER_H

#include <vector>
#include <milx/path.h>

namespace milx {
  struct Plugin;
  struct Application;

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
