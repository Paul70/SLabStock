#include "address.h"

#include "libd/libdutil/constructiondata.h"
#include "libd/libdutil/constructionvalidator.h"

using namespace DUTIL;
using namespace Slabstock::MailServices;

D_DEFINE_PROJECTWARE(Address)

ConstructionValidator const& Address::getConstructionValidator()
{
  using SR = SettingRule;
  static const DUTIL::ConstructionValidator cv({
      SR::forNamedParameter<Address::MailAddress>(SR::Usage::MANDATORY_NO_DEFAULT, "Mail address"),
  });
  return cv;
}

Address::Address(ConstructionData const& cd) :
    address_(getConstructionValidator().validateNamedParameter<Address::MailAddress>(cd))
{}

std::string Address::get() const
{
  return address_;
}
