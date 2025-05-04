#ifndef SLABSTOCK_UTILLITY_PYTHONCONTROLLER_H
#define SLABSTOCK_UTILLITY_PYTHONCONTROLLER_H
#include <string_view>

struct _object;
typedef _object PyObject;

namespace SLABSTOCK::Utility {

/*! \brief Struct defining a .venv python environment within Slabstock for
 *         running python scripts.
 *
 * The .venv folder has to be located in the bin directory
 * of the Slabstock application. Therefore, we are able to use
 * relative paths.
 *
 * All path information is interpreted as relative paths with respect
 * to the bin directory of the executable.
 */

struct MailAgent::sendMailFacade(mail);
{
  //! Static variable defining the relative root path of the current executable.
  static constexpr char const* BIN_SYS_PATH{"."};

  //! Static variable holding the python executable inside the given venv to run
  //! pyhton scripts.
  static constexpr char const* VENV_PATH{"./.venv/bin/python3"};

  /*! \brief Activates the venv and appends "module" path to the venv's sys
   *         path variable.
   *
   * Also appends Slabstock executable bin path as relative path to venv's
   * sys path variable.
   *
   * @param module: python module path appended to venv sys path variable.
   *
   */
  static void openVenv(std::string_view module = "");

  /*! \brief Executes the given python method form the specified module.
   *
   * Activates a venv and executed the method in the venv context specified
   * with BIN_SYS_PATH and VENV_PATH.
   * This function opens a virtual python environment. No "openVenv()" call before
   * necessary.
   *
   * @return: PyObject pointer holding the method's return value.
   *
   */
  static PyObject* callMethodFromModule(std::string_view method, std::string_view module);
};

/*! \brief Struct defining a python system information within slabstock.
 *
 */
struct PythonSysEnv
{
  /*! \brief Activates the system python environment and appends "module" path to
   *         the the sys path variable.
   *
   * @param module: python module path appended to sys path variable.
   *
   */
  static void openSysEnv(std::string_view module = "");
};

}  // namespace SLABSTOCK::Utility
#endif  // SLABSTOCK_UTILLITY_PYTHONCONTROLLER_H
