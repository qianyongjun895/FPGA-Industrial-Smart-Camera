#ifndef UDPCOMM_GLOBAL_H
#define UDPCOMM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UDPCOMM_LIBRARY)
#  define UDPCOMMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define UDPCOMMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // UDPCOMM_GLOBAL_H
