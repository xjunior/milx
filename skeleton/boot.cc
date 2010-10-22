#include <milx/plugins.h>
#include <milx/application.h>

#include "classes.milx.h"

#define ADD_CONTROLLER(klass)\
  app.controller(new klass, GET_CLASS_NAME(klass));
#define ADD_ROUTE(regex, controller, action)\
  app.routes().route(#regex, #controller, #action);

#ifndef PROJECT_NAME
#define PROJECT_NAME "my-project"
#endif
#ifndef PROJECT_VERSION
#define PROJECT_VERSION 1
#endif

void milx_plugin_load(milx::Application& app, milx::Plugin& plugin) {
  plugin.version = PROJECT_VERSION;
  plugin.name = PROJECT_NAME;

  #include "routes.milx.cc"
}

#undef ADD_CONTROLLER
#undef ADD_ROUTE

