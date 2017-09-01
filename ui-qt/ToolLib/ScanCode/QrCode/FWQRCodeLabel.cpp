#include "FWQRCodeLabel.h"

FWQRCodeLabel::FWQRCodeLabel(QWidget *parent) : QLabel(parent)
{

}
void FWQRCodeLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
