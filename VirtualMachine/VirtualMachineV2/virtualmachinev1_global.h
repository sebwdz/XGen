#ifndef VIRTUALMACHINEV1_GLOBAL_H
#define VIRTUALMACHINEV1_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(VIRTUALMACHINEV1_LIBRARY)
#  define VIRTUALMACHINEV1SHARED_EXPORT Q_DECL_EXPORT
#else
#  define VIRTUALMACHINEV1SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // VIRTUALMACHINEV1_GLOBAL_H
