#include "controller.h"

MyController::MyController() : milx::Controller() {
  register_action("index", &MyController::index);
}

void MyController::index(milx::http::Call& call) {
  call.content_type("text/html");
  call.content() << "Hello from Milx!";
}

