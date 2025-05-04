#include "mail.h"

#include "libd/libdutil/constructiondata.h"
#include "libd/libdutil/constructionvalidator.h"

using namespace DUTIL;
using namespace Slabstock::MailServices;

D_DEFINE_PROJECTWARE(Mail)

ConstructionValidator const& Mail::getConstructionValidator()
{
  using SR = SettingRule;
  using WR = WarelistRule;
  static const DUTIL::ConstructionValidator cv(
      // rules for construction data settings
      {SR::forNamedParameter<Mail::Subject>(SR::Usage::OPTIONAL, "Set the mail subject."),
       SR::forNamedParameter<Mail::Message>(SR::Usage::OPTIONAL, "Set the mail message")},

      // rules for ware objects
      {WR::forSubobjectList<Mail::AddressList>(
           "Set all addresses to which this mail shall be sent."),
       WR::forSubobject<Mail::AttachmentList>("Set all mail attachments")});

  return cv;
}

Mail::Mail(DUTIL::ConstructionData const& cd, DUTIL::LoggingSource::LoggingSinkPointer sink) :
    LoggingSource(sink),
    addresses_(getConstructionValidator().buildSubobjectList<Mail::AddressList>(cd)),
    //attachments_(getConstructionValidator().buildSubobjectList<Mail::AttachmentList>(cd)),
    subject_(getConstructionValidator().validateNamedParameter<Mail::Subject>(cd)),
    message_(getConstructionValidator().validateNamedParameter<Mail::Message>(cd))
{}

std::string Mail::getAddresses() const
{
  return "mail@paulheidenreich.com";
}

std::string Mail::getMessage() const
{
  return message_;
}

std::string Mail::getSubject() const
{
  return subject_;
}
