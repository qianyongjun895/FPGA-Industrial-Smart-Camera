#ifndef TOOLLOGICWORKOVER_GLOBAL_H
#define TOOLLOGICWORKOVER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TOOLLOGICWORKOVER_LIBRARY)
#  define TOOLLOGICWORKOVERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TOOLLOGICWORKOVERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TOOLLOGICWORKOVER_GLOBAL_H
