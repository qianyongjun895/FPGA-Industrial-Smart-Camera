#ifndef LEARNINGDIALOG_H
#define LEARNINGDIALOG_H

#include "learningdialog_global.h"
#include <QDialog>

class LEARNINGDIALOGSHARED_EXPORT LearningDialog
{

public:
    LearningDialog();
};

extern "C" Q_DECL_EXPORT QDialog *GetDialog();
extern "C" Q_DECL_EXPORT void SetResultString(QString code_string);
extern "C" Q_DECL_EXPORT void ReleaseDialog(QDialog *PWidget);
#endif // LEARNINGDIALOG_H
