#ifndef SLABSTOCK_CPYMAIL_ATTACHMENT_H
#define SLABSTOCK_CPYMAIL_ATTACHMENT_H
#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/loggingsource.h"
#include "libd/libdutil/namedclass.h"
#include "libd/libdutil/projectware.h"

#include <filesystem>

namespace DUTIL {
struct ConstructionData;
}

namespace Slabstock::MailServices {

class Attachment final :
    public DUTIL::ProjectWare,
    public DUTIL::LoggingSource,
    public D_NAMED_CLASS(::Slabstock::CPy::MailServices::Attachment)
{
  public:
  using Path = std::filesystem::path;

  //! Declare static factory member
  D_DECLARE_PROJECTWARE(Attachment)

  //! Attachment file name
  D_NAMED_STRING(FileName);

  //! Return construction requirements.
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  //! Constructor using ConstructionData.
  explicit Attachment(DUTIL::ConstructionData const& cd,
                      DUTIL::LoggingSource::LoggingSinkPointer sink = nullptr);

  std::string getFilePath() const;

  private:
  Path file_;
};
}  // namespace Slabstock::MailServices
#endif  // SLABSTOCK_CPYMAIL_ATTACHMENT_H
