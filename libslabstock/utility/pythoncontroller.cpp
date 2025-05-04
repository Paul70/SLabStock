#include "pythoncontroller.h"

#include "libd/libdpython/pythoninterface.h"

using namespace DPYTHON;
using namespace SLABSTOCK::Utility;

void PythonVenv::openVenv(std::string_view module)
{
  openVenvEnvironment(PythonVenv::VENV_PATH);
  DPYTHON::appendSysPaht(PythonVenv::BIN_SYS_PATH);
  DPYTHON::appendSysPaht(module.data());
}

PyObject* PythonVenv::callMethodFromModule(std::string_view /*method*/, std::string_view module)
{
  openVenv(module);
  //return DPYTHON::runPythonModuleMethod("mail.py", method.data());
  return nullptr;
}

void PythonSysEnv::openSysEnv(std::string_view module)
{
  openSystemEnvironment();
  DPYTHON::appendSysPaht(module.data());
}
