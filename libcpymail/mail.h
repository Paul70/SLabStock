#ifndef SLABSTOCK_PYBIND_PYMAIL_H
#define SLABSTOCK_PYBIND_PYMAIL_H
#include "address.h"
#include "attachment.h"

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/loggingsource.h"
#include "libd/libdutil/namedclass.h"
#include "libd/libdutil/projectware.h"

namespace DUTIL {
struct ConstructionData;
}

namespace Slabstock::MailServices {

/*! \brief description of PyMailFactory
 *
 * Longer description of PyMailFactory.
 *
 * Task: ein protobuf dict bauen aus einem dutil Projectware instance
 */

class Mail final :
    public DUTIL::ProjectWare,
    public DUTIL::LoggingSource,
    public D_NAMED_CLASS(::Slabstock::CPy::MailServices::Mail)
{
  public:
  using Addresses = std::vector<std::unique_ptr<Address>>;
  using Attachments = std::vector<std::unique_ptr<Attachment>>;

  //! Declare static factory member
  D_DECLARE_PROJECTWARE(Mail)

  //! Set of mail addresses.
  D_NAMED_REFERENCE(AddressList, Address)

  //! Set of mail attachements.
  D_NAMED_REFERENCE(AttachmentList, Attachment)

  //! Mail subject
  D_NAMED_STRING(Subject);

  //! Mail message
  D_NAMED_STRING(Message);

  //! Return construction requirements.
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  //! Constructor using ConstructionData.
  explicit Mail(DUTIL::ConstructionData const& cd,
                DUTIL::LoggingSource::LoggingSinkPointer sink = nullptr);

  std::string getAddresses() const;

  std::string getMessage() const;

  std::string getSubject() const;

  private:
  Addresses addresses_;
  Attachments attachments_;
  std::string subject_;
  std::string message_;
};

}  // namespace Slabstock::MailServices
#endif  // SLABSTOCK_PYBIND_PYMAIL_H
