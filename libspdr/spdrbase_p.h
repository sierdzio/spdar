#ifndef SPDRBASE_P_H
#define SPDRBASE_P_H

#include "spdrbase.h"
#include "spdrlog.h"

#include <QString>

/*!
  \ingroup libspdr
  \internal
  */
class SpdrBasePrivate
{
    Q_DECLARE_PUBLIC(SpdrBase)

public:
    SpdrBasePrivate(SpdrBase *q) : q_ptr(q) {}
    SpdrBase *q_ptr;

    SpdrLog mLog;
    QString mInputPath;
    QString mOutputPath;
    bool mSimulate;
    Spdr::UpdateMode mUpdateMode;
    bool mSuffixCaseSensitive;
};

#endif // SPDRBASE_P_H
