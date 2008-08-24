#include "prelude.hpp"
#include "objectmemory.hpp"
#include "vm/vmnativefunction.hpp"
#include "builtin/nativefunction.hpp"
#include "builtin/symbol.hpp"
#include "builtin/task.hpp"

namespace rubinius {

  /* Create a new VMNativeFunctions.
   *
   * NOTE: There is no state in VMNativeFunction, it's just a place to hang
   * the executor off, so we just reuse the same object for all usages */
  VMNativeFunction* VMNativeFunction::create(STATE) {
    static VMNativeFunction* object = NULL;
    if(!object) {
      object = new VMNativeFunction();
    }

    return object;
  }

  VMNativeFunction::VMNativeFunction() {
    execute = VMNativeFunction::executor;
  }

  /* Run when a NativeFunction is executed.  Executes the related C function.
   */
  bool VMNativeFunction::executor(STATE, VMExecutable* meth, Task* task, Message& msg) {
    NativeFunction* nfunc = as<NativeFunction>(msg.method);

    nfunc->call(state, &msg);

    return false;
  }
}
