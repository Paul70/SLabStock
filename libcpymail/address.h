#ifndef SLABSTOCK_CPYMAIL_ADDRESS_H
#define SLABSTOCK_CPYMAIL_ADDRESS_H

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"
#include "libd/libdutil/projectware.h"

namespace DUTIL {
struct ConstructionData;
}

namespace Slabstock::MailServices {

class Address final :
    public DUTIL::ProjectWare,
    public D_NAMED_CLASS(::Slabstock::CPy::MailServices::Address)
{
  public:
  //! Declare static factory member
  D_DECLARE_PROJECTWARE(Address)

  D_NAMED_STRING(MailAddress)

  //! Return construction requirements.
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  //! Constructor using ConstructionData.
  explicit Address(DUTIL::ConstructionData const& cd);

  std::string get() const;

  private:
  const std::string address_;
};
}  // namespace Slabstock::MailServices
#endif  // SLABSTOCK_CPYMAIL_ADDRESS_H
