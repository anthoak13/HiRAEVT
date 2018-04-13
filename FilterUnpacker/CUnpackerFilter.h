

#ifndef CUNPACKERFILTER_CPP
#define CUNPACKERFILTER_CPP

#include <RBShared.h>
#include <CFilter.h>
#include <stdint.h>

class TH1;
class CPhysicsEventItem;

/**! \class CUnpackerFilter
    Here is a sample implementation of a filter to append a reversed copy of the
    data in physics event to its body. This is for illustration purposes.

    See the documentation for the CFilter base class for the virtually declared
    methods available for dealing with non-physics events. The user has access
    to all of the different ring item types. In fact, it is not necessary for
    the user to return the same type of ring item from method as it received.
*/
class CUnpackerFilter : public CFilter
{
  private:
    char sourceFileName[1000];

  public:
    CUnpackerFilter();

    void PassArguments(int argc, char* argv[]);

    virtual CUnpackerFilter* clone() const { return new CUnpackerFilter(*this);}

    virtual CRingItem* handleStateChangeItem(CRingStateChangeItem* pItem);
    // handle the  physics events
    virtual CRingItem* handlePhysicsEventItem(CPhysicsEventItem* pItem);

};

#endif
