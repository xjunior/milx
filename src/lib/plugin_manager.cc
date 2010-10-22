#include <milx/plugin_manager.h>
#include <milx/plugins.h>

#include <dlfcn.h>

#include <memory>
#include <vector>
#include <exception>

void milx::PluginManager::load(const milx::Path& file) {
  Plugin *plug = new milx::Plugin;
  plug->_plugin_mem = dlopen(file.str().c_str(), RTLD_LAZY|RTLD_GLOBAL);

  if (plug->_plugin_mem) {
    typedef void(*on_load_f)(milx::Application&, milx::Plugin&);
    on_load_f on_load = (on_load_f) dlsym(plug->_plugin_mem, MILX_PLUGIN_LOAD);

    if (on_load) {
      on_load(_app, *plug);
      _plugins.push_back(plug);
    } else {
      // TODO(xjunior) throw a milx exception
      throw std::exception();
    }
  } else {
      // TODO(xjunior) throw a milx exception dlerror()
    throw std::exception();
  }
}

milx::PluginManager::~PluginManager() {
  // FIXME cleaning stuff breaks the plugin whereever it have been stored
  // (eg: milx::view::renderers)
  for (std::vector<Plugin*>::iterator begin = _plugins.begin();
      begin != _plugins.end();) {
    /*if ((*begin)->_plugin_mem)
      dlclose((*begin)->_plugin_mem);
    _plugins.erase(begin);*/
  }
}

