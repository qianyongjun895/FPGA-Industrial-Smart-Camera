#ifndef VERSIONINFO_H
#define VERSIONINFO_H

#include <QWidget>

namespace Ui {
class VersionInfo;
}

class VersionInfo : public QWidget
{
    Q_OBJECT

public:
    explicit VersionInfo(QWidget *parent = 0);
    ~VersionInfo();

private:
    Ui::VersionInfo *ui;
};

#endif // VERSIONINFO_H
