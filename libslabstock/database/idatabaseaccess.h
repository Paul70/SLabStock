#ifndef SLABSTOCK_IDATABASEACCESS_H
#define SLABSTOCK_IDATABASEACCESS_H
#include <functional>
#include <string>

namespace DUTIL {
struct ConstructionData;
}

namespace SLABSTOCK::Database {

/*! \brief description of Table
 *
 * Longer description of Table.
 */

class IDatabaseAccess
{
  public:
  IDatabaseAccess() = default;
  virtual ~IDatabaseAccess() = default;

  void setDataExportCallback() const;

  void executeQuery(const std::string& query) const;

  void queryTable() const;

  private:
  virtual void setDataExportCallbackImpl() const = 0;
  virtual void executeQueryImpl(const std::string& query) const = 0;
  virtual void queryTableImpl() const = 0;
};

template <typename Derived>
class IValueAccess : public IDatabaseAccess
{
  public:
  template <typename T>
  void setDataExportCallback(std::function<void(T)> callback) const
  {
    static_cast<const Derived*>(this)->setCallback(callback);
  }
};

}  // namespace SLABSTOCK::Database
#endif  // SLABSTOCK_IDATABASEACCESS_H
