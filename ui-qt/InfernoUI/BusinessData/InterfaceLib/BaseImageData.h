#ifndef BASEIMAGEDATA_H
#define BASEIMAGEDATA_H

#include <QObject>
#include <QString>
#include <QVector>

class BaseImageData : public QObject
{
    Q_OBJECT
public:
    BaseImageData();

    int SaveBaseImage(QString ImageName);

    int LoadBaseImage(QString ImageName);

    int DeleteBaseImage(QString ImageName);

    // -1  清空失败  0  清空成功
    int CleanBaseImage();

    QVector<QString> GetBaseImageDirAllName();
    void SetStepMsFileNameValue(int step,QString strName);
    QString GetStepMsFileNameValue(int step);
    QString GetSimulationDir();
    void SetSimulationDir(QString Str);
    void SimulationRunInit(QString str);
    int SaveImage(QString str);

};

#endif // BASEIMAGEDATA_H
