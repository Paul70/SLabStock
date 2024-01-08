#ifndef SLABSTOCK_EVENT_H
#define SLABSTOCK_EVENT_H
#include "libd/libdutil/loggingsource.h"
#include "libd/libdutil/namedparameter.h"
#include "libd/libdutil/namedreference.h"
#include "libd/libdutil/projectware.h"

namespace DUTIL {
struct ConstructionData;
class ConstructionValidator;
}  // namespace DUTIL

namespace SLABSTOCK {
class Callback;

/*! \brief description of Event
 *
 * Longer description of Event.
 */

class Event : public DUTIL::ProjectWare, public DUTIL::LoggingSource
{
  public:
  //! Set Id type identifying a concrete event.
  using Id = std::uint64_t;

  //! Id is a named parameter set at construction.
  D_NAMED_PARAMETER(IdParam, Id)

  //! Textual description of the event.
  D_NAMED_STRING(Description)

  //! Define all possible states of an event.
  D_NAMED_ENUM(State, NOT_SCHEDULED, SCHEDULED, TRIGGERED, PROCESSED)

  //! Define the list of callbacks needed during construction.
  D_NAMED_REFERENCE(CallbackList, Callback)

  //! Default constructor.
  explicit Event(DUTIL::ConstructionData const& cd, LoggingSinkPointer sink = nullptr);

  //! Define set of rules to validate construction data.
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  virtual ~Event() override;

  //! Interface function to get the derived class name.
  std::string whatAmI() const;

  //! Return the event id.
  Event::Id getId() const;

  //! Retrun the current event state.
  Event::State getState() const;

  //! Return a copy of the current event values.
  DUTIL::ConstructionData getValue() const;

  /*! \brief Event state machine method.
   *
   * Asserts if method is calles and state is set to 'PROCESSED'.
   */
  Event::State advanceState();

  void addCallback(DUTIL::ConstructionData const& callback_cd);

  private:
  virtual std::string whatAmIImpl() const = 0;

  std::unique_ptr<DUTIL::ConstructionData> value_;
  std::vector<std::unique_ptr<Callback>> callbacks_;
};

namespace EventDetail {
template <typename T>
struct is_event : public std::conjunction<std::is_same<T, Event>, std::is_base_of<Event, T>>
{};

template <typename T>
constexpr bool is_event_v = is_event<T>::value;
}  // namespace EventDetail

}  // namespace SLABSTOCK

D_DECLARE_FACTORYINTERFACE(::SLABSTOCK::Event)

#define D_DECLARE_EVENT(REGISTERED_CLASS)                                                     \
  static const DUTIL::ConcreteFactory<REGISTERED_CLASS, SLABSTOCK::Event, DUTIL::ProjectWare> \
      factory;

#define D_DEFINE_EVENT(REGISTERED_CLASS)                                               \
  const DUTIL::ConcreteFactory<REGISTERED_CLASS, SLABSTOCK::Event, DUTIL::ProjectWare> \
      REGISTERED_CLASS::factory;
#endif  // SLABSTOCK_EVENT_H
