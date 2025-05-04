#ifndef SLABSTOCK_PYBIND_PYMAILFACTORY_H
#define SLABSTOCK_PYBIND_PYMAILFACTORY_H

#include "libcpymail/imailagent.h"

#include <memory>

namespace Slabstock::MailServices {
class Mail;

/*! \brief description of PyMailFactory
 *
 * Longer description of PyMailFactory.
 */

class MailAgent : public IMailAgent
{
  public:
  static std::unique_ptr<MailAgent> create();

  using IMailAgent::IMailAgent;

  MailAgent(const MailAgent&) = delete;
  MailAgent& operator=(const MailAgent&) = delete;

  virtual ~MailAgent() override = default;

  private:
  virtual void sendImpl(Mail const& mail) const override;
};

}  // namespace Slabstock::MailServices
#endif  // SLABSTOCK_PYBIND_PYMAILFACTORY_H
