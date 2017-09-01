#include "FWMeanBrightnessLabel.h"

FWMeanBrightnessLabel::FWMeanBrightnessLabel(QWidget *parent) : QLabel(parent)
{
    m_pen_color = NULL;
}

FWMeanBrightnessLabel::~FWMeanBrightnessLabel()
{

}
void FWMeanBrightnessLabel::SetPenColor(void *pen_color)
{
    this->m_pen_color = pen_color;
}
