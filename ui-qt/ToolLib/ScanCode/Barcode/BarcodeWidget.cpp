#include "BarcodeWidget.h"
#include "ui_BarcodeWidget.h"
#include "FWBarcodeLabel.h"
#include <QDebug>
#include <QMessageBox>
BarcodeWidget::BarcodeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BarcodeWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    m_label = new FWBarcodeLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);

    ui->comboBox_Code_Type->addItem(tr("EAN8"));
    ui->comboBox_Code_Type->addItem(tr("EAN13"));
    ui->comboBox_Code_Type->addItem(tr("CODE-39"));
    ui->comboBox_Code_Type->addItem(tr("CODE-93"));
    ui->comboBox_Code_Type->addItem(tr("CODE-128"));
    ui->comboBox_Code_Type->addItem(tr("I2/5"));
    ui->comboBox_Code_Type->addItem(tr("UPC-A"));
    ui->comboBox_Code_Type->addItem(tr("UPC-E"));
    ui->comboBox_Code_Type->addItem(tr("ITF"));
    ui->comboBox_Code_Type->addItem(tr("CodaBar"));

    ui->comboBox_comp->addItem(tr("所有数据"));
    ui->comboBox_comp->addItem(tr("分割数据1"));
    ui->comboBox_comp->addItem(tr("分割数据2"));
    ui->comboBox_comp->addItem(tr("分割数据3"));
    ui->comboBox_comp->addItem(tr("分割数据4"));
    QList<QLineEdit*> EditList = this->findChildren<QLineEdit*>();
    foreach (QLineEdit *L, EditList) {
        L->installEventFilter(this);
    }

    Data_Flag.insert(ui->checkBox_Data1, 0);
    Data_Flag.insert(ui->checkBox_Data2, 1);
    Data_Flag.insert(ui->checkBox_Data3, 2);
    Data_Flag.insert(ui->checkBox_Data4, 3);

    Data_start_bit.insert(ui->lineEdit_Data1_Start_Bit, 0);
    Data_start_bit.insert(ui->lineEdit_Data2_Start_Bit, 1);
    Data_start_bit.insert(ui->lineEdit_Data3_Start_Bit, 2);
    Data_start_bit.insert(ui->lineEdit_Data4_Start_Bit, 3);

    Data_length.insert(ui->lineEdit_Data1_Length, 0);
    Data_length.insert(ui->lineEdit_Data2_Length, 1);
    Data_length.insert(ui->lineEdit_Data3_Length, 2);
    Data_length.insert(ui->lineEdit_Data4_Length, 3);
}

BarcodeWidget::~BarcodeWidget()
{
    QList<QLineEdit*> EditList = this->findChildren<QLineEdit*>();
    foreach (QLineEdit *L, EditList) {
        L->removeEventFilter(this);
    }
    delete ui;
}

void BarcodeWidget::IniData()
{
    ui->comboBox_Code_Type->setCurrentIndex(pInputPara->Code_Type);
    if(pInputPara->Read_Data_Flag == 1){
        ui->lineEdit_Data_Start_Bit->setText(QString::number(pInputPara->start_bit));
        ui->lineEdit_Data_Length->setText(QString::number(pInputPara->Data_length));
        for(int i = 0; i < BARCODE_Segmentation_Data_Num; i++){
            if(pInputPara->Data_Config[i].Data_flag == 1){
                Data_Flag.key(i)->setChecked(true);
                Data_start_bit.key(i)->setEnabled(true);
                Data_start_bit.key(i)->setText(QString::number(pInputPara->Data_Config[i].start_bit));
                Data_length.key(i)->setEnabled(true);
                Data_length.key(i)->setText(QString::number(pInputPara->Data_Config[i].length));
            }
        }
        if(pInputPara->Fill_Config.Fill_Flag == 1){
            ui->checkBox_Output_Length->setChecked(true);
            ui->label_fill->setEnabled(true);
            ui->lineEdit_fill->setEnabled(true);
            ui->lineEdit_fill->setText(QString::fromUtf8(&pInputPara->Fill_Config.Fill_Data));
        }
    }
    if(pInputPara->Fail_Config.Fail_Output_Flag == 1){
        ui->checkBox_fail_Output->setChecked(true);
        ui->lineEdit_Fail_Output_String->setText(QString::fromUtf8(pInputPara->Fail_Config.Fail_Output_Data));
    }
    if(pInputPara->Cmp_Config.Cmp_Type != -1){
        ui->comboBox_comp->setCurrentIndex(pInputPara->Cmp_Config.Cmp_Type);
        ui->lineEdit_Comp_Data->setText(QString::fromUtf8(pInputPara->Cmp_Config.Cmp_Data));
    }
}
void BarcodeWidget::Init_Input_Ptr(void *pInpuPara,int i_step_index ,int new_flag,void *pen_color)
{
    pInputPara = (BARCODE_INPUT_PARAM*)pInpuPara;
    m_step_index = i_step_index;
    if(pInputPara == NULL){
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    if(new_flag){
        pInputPara->Code_Type = 0;
        pInputPara->Read_Data_Flag = 0;
        pInputPara->Fail_Config.Fail_Output_Flag = 0;
        pInputPara->Cmp_Config.Cmp_Type = -1;
        memset(pInputPara->Cmp_Config.Cmp_Data, 0, BARCODE_CMP_DATA_LENGTH);
    }
    IniData();
}

int BarcodeWidget::CheckSetParam()
{
    if(ui->lineEdit_Data_Start_Bit->text() == "---" && ui->lineEdit_Data_Length->text() == "---"){

    }else if(ui->lineEdit_Data_Start_Bit->text() == "---" || ui->lineEdit_Data_Length->text() == "---"){
        QMessageBox::about(NULL, tr("提示"), tr("读取开始位或读取长度未设置"));
        return -1;
    }
    for(int i = 0; i < BARCODE_Segmentation_Data_Num; i++){
        if(Data_Flag.key(i)->isChecked()){
            if(Data_start_bit.key(i)->text().isEmpty() || Data_length.key(i)->text().isEmpty()){
                QMessageBox::about(NULL, tr("提示"), tr("数据分割")+QString::number(i)+tr("的分割开始位或分割数据长度未设置"));
                return -1;
            }
        }
    }
    if(ui->checkBox_Output_Length->isChecked()){
        if(ui->lineEdit_fill->text() == ""){
            QMessageBox::about(NULL, tr("提示"), tr("填充字符不能为空"));
            return -1;
        }
    }
    if(ui->checkBox_fail_Output->isChecked()){
        if(ui->lineEdit_Fail_Output_String->text() == ""){
            QMessageBox::about(NULL, tr("提示"), tr("解码失败输出字符为空"));
            return -1;
        }
    }
    if(!ui->lineEdit_Comp_Data->text().isEmpty()){
        if((ui->comboBox_comp->currentIndex() != 0) && (!(Data_Flag.key(ui->comboBox_comp->currentIndex() - 1)->isChecked()))){
            QMessageBox::about(NULL, tr("提示"), tr("未设置")+tr("数据分割")+QString::number(ui->comboBox_comp->currentIndex())+tr(",无法比对！"));
            return -1;
        }
    }
    return 0;
}

int BarcodeWidget::Set_Parameter_To_Ram()
{
    int ret = CheckSetParam();
    if(ret == -1){
        return 0;
    }
    pInputPara->Code_Type = ui->comboBox_Code_Type->currentIndex();
    if(ui->lineEdit_Data_Start_Bit->text() == "---" && ui->lineEdit_Data_Length->text() == "---"){
        pInputPara->Read_Data_Flag = 0;
    }else{
        pInputPara->Read_Data_Flag = 1;
        pInputPara->start_bit = ui->lineEdit_Data_Start_Bit->text().toUInt();
        pInputPara->Data_length = ui->lineEdit_Data_Length->text().toUInt();
        for(int i = 0; i < BARCODE_Segmentation_Data_Num; i++){
            if(Data_Flag.key(i)->isChecked()){
                pInputPara->Data_Config[i].Data_flag = 1;
                pInputPara->Data_Config[i].start_bit = Data_start_bit.key(i)->text().toUInt();
                pInputPara->Data_Config[i].length = Data_length.key(i)->text().toUInt();
            }else{
                pInputPara->Data_Config[i].Data_flag = 0;
            }
        }
        if(ui->checkBox_Output_Length->isChecked()){
            pInputPara->Fill_Config.Fill_Flag = 1;
            pInputPara->Fill_Config.Fill_Data = *(ui->lineEdit_fill->text().toUtf8().data());
        }else{
            pInputPara->Fill_Config.Fill_Flag = 0;
        }
    }
    if(ui->checkBox_fail_Output->isChecked()){
        pInputPara->Fail_Config.Fail_Output_Flag = 1;
        QString fail_string = ui->lineEdit_Fail_Output_String->text();
        QByteArray ba = fail_string.toUtf8();
        memset(pInputPara->Fail_Config.Fail_Output_Data, 0, BARCODE_FAIL_OUTPUT_LENGTH);
        memcpy(pInputPara->Fail_Config.Fail_Output_Data, ba.data(), fail_string.length());
    }else{
        pInputPara->Fail_Config.Fail_Output_Flag = 0;
    }
    if(ui->lineEdit_Comp_Data->text().isEmpty()){
        pInputPara->Cmp_Config.Cmp_Type = -1;
    }else{
        pInputPara->Cmp_Config.Cmp_Type = ui->comboBox_comp->currentIndex();
        QString cmp_string = ui->lineEdit_Comp_Data->text();
        QByteArray ba = cmp_string.toUtf8();
        memset(pInputPara->Cmp_Config.Cmp_Data, 0, BARCODE_CMP_DATA_LENGTH);
        memcpy(pInputPara->Cmp_Config.Cmp_Data, ba.data(), cmp_string.length());
    }
    return 1;
}

QPoint BarcodeWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }
    return point;
}

bool BarcodeWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_Data_Start_Bit || watched == ui->lineEdit_Data_Length){
        if(event->type() == QEvent::MouseButtonRelease){
            if(((QLineEdit*)watched)->isEnabled()){

                NumKeyBoardDlg(watched, 1, 1, BARCODE_RESULT_LENGTH);

            }
        }
    }
    if(watched == ui->lineEdit_Data1_Start_Bit|| watched == ui->lineEdit_Data2_Start_Bit\
            || watched == ui->lineEdit_Data3_Start_Bit || watched == ui->lineEdit_Data4_Start_Bit){
        if(event->type() == QEvent::MouseButtonRelease){
            if(((QLineEdit*)watched)->isEnabled()){
                NumKeyBoardDlg(watched, 0, ui->lineEdit_Data_Start_Bit->text().toInt(), ui->lineEdit_Data_Start_Bit->text().toInt()+ui->lineEdit_Data_Length->text().toInt());
            }
        }
    }
    if(watched == ui->lineEdit_Data1_Length|| watched == ui->lineEdit_Data2_Length\
            || watched == ui->lineEdit_Data3_Length || watched == ui->lineEdit_Data4_Length){
        if(event->type() == QEvent::MouseButtonRelease){
            if(((QLineEdit*)watched)->isEnabled()){
                NumKeyBoardDlg(watched, 0, 1, ui->lineEdit_Data_Length->text().toInt());
            }
        }
    }
    if(watched == ui->lineEdit_fill){
        if(event->type() == QEvent::MouseButtonRelease){
            if(((QLineEdit*)watched)->isEnabled()){
                KeyBoardDlg(watched, event, 0, 0, 1);
            }
        }
    }
    if(watched == ui->lineEdit_Fail_Output_String){
        if(event->type() == QEvent::MouseButtonRelease){
            if(((QLineEdit*)watched)->isEnabled()){
                KeyBoardDlg(watched, event, 0, 0, BARCODE_FAIL_OUTPUT_LENGTH);
            }
        }
    }
    if(watched == ui->lineEdit_Comp_Data){
        if(event->type() == QEvent::MouseButtonRelease){
            if(((QLineEdit*)watched)->isEnabled()){
                KeyBoardDlg(watched, event, 0, 150, BARCODE_CMP_DATA_LENGTH);
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void BarcodeWidget::LoadKeyBoardLib()
{
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.isLoaded())
    {
        return;
    }
    if(m_keyBoard_Lib.load())
    {
        qDebug()<<"libFrmInputKeyBoard.so OK";
    }
    else
    {
        qDebug()<<"load libFrmInputKeyBoard.so fail"<<m_keyBoard_Lib.errorString();
    }
}

void BarcodeWidget::NumKeyBoardDlg(QObject *watched, int clear_en, int Min_value, int Max_value)
{
    Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
    if(GetNumKeyBoardDlg)
    {
        Numkey = GetNumKeyBoardDlg();
        if(clear_en == 1){
            ShowRangeEn RangEn = (ShowRangeEn)m_keyBoard_Lib.resolve("SetRangeEnvBtn");
            if(RangEn){
                RangEn();
            }else{
                return;
            }
        }
        int ret = Numkey->exec();
        if(ret == QDialog::Accepted)
        {
            Fun_GetNumString GetNumString = (Fun_GetNumString)m_keyBoard_Lib.resolve("GetNum");
            if(GetNumString)
            {
                QString num = GetNumString();
                if(num == "---"){

                }else if(num.toInt() > Max_value || num.toInt() < Min_value){
                    QMessageBox::about(NULL, tr("提示"), tr("该值无效,请输入")+QString::number(Min_value)+tr("~")+QString::number(Max_value)+tr("之间的值"));
                    return;
                }
                ((QLineEdit *)watched)->setText(num);
            }
        }
        delete Numkey;
        Numkey = NULL;
    }
    else
    {
        qDebug()<<"get GetDialog func fail:"<<m_keyBoard_Lib.errorString();
    }
}

void BarcodeWidget::KeyBoardDlg(QObject *watched, QEvent *event, int dlg_x, int dlg_y, int String_Len)
{
    Fun_GetkeyBoardDlg GetKeyBoardDlg = (Fun_GetkeyBoardDlg)m_keyBoard_Lib.resolve("GetKeyBoardDialog");
    Fun_GetInputString GetInputString = (Fun_GetInputString)m_keyBoard_Lib.resolve("GetInputString");
    if(GetKeyBoardDlg)
    {
        m_dlg = GetKeyBoardDlg();
        if(!(dlg_x == 0 && dlg_y == 0))
            m_dlg->move(dlg_x, dlg_y);
        int ret = m_dlg->exec();
        if(ret == QDialog::Accepted)
        {
            if(GetInputString)
            {
                QString labelString =  GetInputString();
                if(labelString.length() > String_Len)
                {
                    QMessageBox::about(NULL, tr("提示"), tr("请输入长度小于")+QString::number(String_Len + 1)+tr("的字符串"));
                }
                else
                {
                    ((QLineEdit *)watched)->setText(labelString);
                }
            }
        }
        delete m_dlg;
        m_dlg = NULL;
    }
    else
    {
        qDebug()<<"get GetDialog func fail:"<<m_keyBoard_Lib.errorString();
    }
}

void BarcodeWidget::DataEnable()
{
    if(ui->lineEdit_Data_Start_Bit->text() == "---" || ui->lineEdit_Data_Length->text() == "---"){
        for(int i = 0; i < BARCODE_Segmentation_Data_Num; i++){
            Data_Flag.key(i)->setEnabled(false);
            Data_Flag.key(i)->setChecked(false);
            Data_start_bit.key(i)->setEnabled(false);
            Data_length.key(i)->setEnabled(false);
        }
        ui->checkBox_Output_Length->setChecked(false);
        ui->checkBox_Output_Length->setEnabled(false);
        ui->lineEdit_fill->setEnabled(false);
    }else{
        for(int i = 0; i < BARCODE_Segmentation_Data_Num; i++){
            Data_Flag.key(i)->setEnabled(true);
            Data_Flag.key(i)->setChecked(false);
            Data_start_bit.key(i)->setText("");
            Data_length.key(i)->setText("");
        }
        ui->checkBox_Output_Length->setEnabled(true);
    }
}

void BarcodeWidget::on_lineEdit_Data_Start_Bit_textChanged(const QString &arg1)
{
    DataEnable();
}

void BarcodeWidget::on_lineEdit_Data_Length_textChanged(const QString &arg1)
{
    DataEnable();
}

void BarcodeWidget::on_checkBox_Data1_clicked()
{
    if(ui->checkBox_Data1->isChecked()){
        ui->lineEdit_Data1_Start_Bit->setEnabled(true);
        ui->lineEdit_Data1_Length->setEnabled(true);
    }else{
        ui->lineEdit_Data1_Start_Bit->setEnabled(false);
        ui->lineEdit_Data1_Length->setEnabled(false);
    }
}

void BarcodeWidget::on_checkBox_Data2_clicked()
{
    if(ui->checkBox_Data2->isChecked()){
        ui->lineEdit_Data2_Start_Bit->setEnabled(true);
        ui->lineEdit_Data2_Length->setEnabled(true);
    }else{
        ui->lineEdit_Data2_Start_Bit->setEnabled(false);
        ui->lineEdit_Data2_Length->setEnabled(false);
    }
}

void BarcodeWidget::on_checkBox_Data3_clicked()
{
    if(ui->checkBox_Data3->isChecked()){
        ui->lineEdit_Data3_Start_Bit->setEnabled(true);
        ui->lineEdit_Data3_Length->setEnabled(true);
    }else{
        ui->lineEdit_Data3_Start_Bit->setEnabled(false);
        ui->lineEdit_Data3_Length->setEnabled(false);
    }
}

void BarcodeWidget::on_checkBox_Data4_clicked()
{
    if(ui->checkBox_Data4->isChecked()){
        ui->lineEdit_Data4_Start_Bit->setEnabled(true);
        ui->lineEdit_Data4_Length->setEnabled(true);
    }else{
        ui->lineEdit_Data4_Start_Bit->setEnabled(false);
        ui->lineEdit_Data4_Length->setEnabled(false);
    }
}

void BarcodeWidget::on_checkBox_Output_Length_clicked()
{
    if(ui->checkBox_Output_Length->isChecked()){
        ui->lineEdit_fill->setEnabled(true);
        ui->label_fill->setEnabled(true);
    }else{
        ui->lineEdit_fill->setEnabled(false);
        ui->label_fill->setEnabled(false);
    }
}

