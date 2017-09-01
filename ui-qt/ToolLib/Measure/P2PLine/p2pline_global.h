#ifndef P2PLINE_GLOBAL_H
#define P2PLINE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(P2PLINE_LIBRARY)
#  define P2PLINESHARED_EXPORT Q_DECL_EXPORT
#else
#  define P2PLINESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // P2PLINE_GLOBAL_H
