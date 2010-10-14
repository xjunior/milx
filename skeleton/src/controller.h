#ifndef MY_CONTROLLER
#define MY_CONTROLLER

#include <milx/controller.h>

class MyController : public milx::Controller {
 public:
  MyController();
  void index(milx::http::Call& call);
};

#endif
