#include "SimulationSelsetDog.h"
#include "ui_SimulationSelsetDog.h"

SimulationSelsetDog::SimulationSelsetDog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimulationSelsetDog)
{
    ui->setupUi(this);
    ui->radioButton_Save->setChecked(true);
}

SimulationSelsetDog::~SimulationSelsetDog()
{
    delete ui;
}

void SimulationSelsetDog::on_btnSelectOk_clicked()
{
    if(ui->radioButton_Import->isChecked())
        m_dir = "ImageImport";
    else if(ui->radioButton_Save->isChecked())
        m_dir = "ImageSave";
    else if(ui->radioButton_Failed->isChecked())
        m_dir = "FailedImage";
    else if(ui->radioButton_OK->isChecked())
        m_dir = "OKImage";
    else if(ui->radioButton_Base->isChecked())
        m_dir = "BaseImage";


    QDialog::accept();
}

void SimulationSelsetDog::SetSimulatDir(QString str)
{
    if(str == "ImageImport")
        ui->radioButton_Import->setChecked(true);
    else if(str == "ImageSave")
        ui->radioButton_Save->setChecked(true);
    else if(str == "FailedImage")
        ui->radioButton_Failed->setChecked(true);
    else if(str == "OKImage")
        ui->radioButton_OK->setChecked(true);
    else if(str == "BaseImage")
        ui->radioButton_Base->setChecked(true);
}

QString SimulationSelsetDog::GetSimulatDir()
{
    return m_dir;
}
