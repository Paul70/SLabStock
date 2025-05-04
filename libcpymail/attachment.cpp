#include "attachment.h"

#include "libd/libdutil/constructiondata.h"
#include "libd/libdutil/constructionvalidator.h"

using namespace DUTIL;
using namespace Slabstock::MailServices;

D_DEFINE_PROJECTWARE(Attachment)

ConstructionValidator const& Attachment::getConstructionValidator()
{
  using SR = SettingRule;
  static const DUTIL::ConstructionValidator cv({
      SR::forNamedParameter<Attachment::FileName>(SR::Usage::MANDATORY_NO_DEFAULT,
                                                  "Attachment file path"),
  });
  return cv;
}

Attachment::Attachment(ConstructionData const& cd, LoggingSinkPointer sink) :
    LoggingSource(sink),
    file_(getConstructionValidator().validateNamedParameter<Attachment::FileName>(cd))
{}

std::string Attachment::getFilePath() const
{
  return file_.string();
}
