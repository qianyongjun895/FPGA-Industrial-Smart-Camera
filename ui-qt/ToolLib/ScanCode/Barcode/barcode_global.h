#ifndef BARCODE_GLOBAL_H
#define BARCODE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BARCODE_LIBRARY)
#  define BARCODESHARED_EXPORT Q_DECL_EXPORT
#else
#  define BARCODESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BARCODE_GLOBAL_H
