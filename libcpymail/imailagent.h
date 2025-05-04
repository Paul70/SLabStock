#ifndef SLABSTOCK_CPY_IMAILAGENT_H
#define SLABSTOCK_CPY_IMAILAGENT_H

namespace Slabstock::MailServices {
class Mail;

class IMailAgent
{
  public:
  IMailAgent() = default;
  IMailAgent(const IMailAgent&) = delete;
  IMailAgent& operator=(const IMailAgent&) = delete;

  virtual ~IMailAgent() = default;

  void send(Mail const& mail) const;

  private:
  virtual void sendImpl(Mail const& mail) const = 0;
};

inline void IMailAgent::send(Mail const& mail) const
{
  sendImpl(mail);
}

}  // namespace Slabstock::MailServices
#endif  // SLABSTOCK_CPY_IMAILAGENT_H
