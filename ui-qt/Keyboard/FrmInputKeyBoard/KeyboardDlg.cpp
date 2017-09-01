#include <QDebug>
#include "KeyboardDlg.h"
#include "ui_KeyboardDlg.h"
#include <QLineEdit>
#include "stdio.h"
QLineEdit *currentLineEdit;     //当前焦点的单行文本框
KeyboardDlg::KeyboardDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyboardDlg)
{
    ui->setupUi(this);
    currentLineEdit = 0;
    b_Caps = false;
    this->button_group=new QButtonGroup;
    this->SetKeyBoard();
    ui->lineEdit_window->setEchoMode(QLineEdit::Normal);
    ui->pushButton_sef->setVisible(false);

    //QDesktopWidget w;
    int deskWidth = 1024;
    int deskHeight = 768;
    int frmWidth = this->width();
    int frmHeight = this->height();

    //this->setGeometry(0, deskHeight - frmHeight, deskWidth, frmHeight);

    connect(this->button_group,SIGNAL(buttonClicked (int)),this,SLOT(ButtonJudge(int)));
    connect(this,SIGNAL(SendInputMessage(QString)),this,SLOT(PreeditContent(QString)));
    this->setGeometry(0, deskHeight - frmHeight, deskWidth, frmHeight);
}

KeyboardDlg::~KeyboardDlg()
{
    delete ui;
}

void KeyboardDlg::on_pushButton_ok_clicked()
{
    QDialog::accept();
}


void KeyboardDlg::SetKeyBoard()
{
    this->button_group->addButton(ui->pushButton_n0,Qt::Key_0);
    this->button_group->addButton(ui->pushButton_n1,Qt::Key_1);
    this->button_group->addButton(ui->pushButton_n2,Qt::Key_2);
    this->button_group->addButton(ui->pushButton_n3,Qt::Key_3);
    this->button_group->addButton(ui->pushButton_n4,Qt::Key_4);
    this->button_group->addButton(ui->pushButton_n5,Qt::Key_5);
    this->button_group->addButton(ui->pushButton_n6,Qt::Key_6);
    this->button_group->addButton(ui->pushButton_n7,Qt::Key_7);
    this->button_group->addButton(ui->pushButton_n8,Qt::Key_8);
    this->button_group->addButton(ui->pushButton_n9,Qt::Key_9);

    this->button_group->addButton(ui->pushButton_a,Qt::Key_A);
    this->button_group->addButton(ui->pushButton_b,Qt::Key_B);
    this->button_group->addButton(ui->pushButton_c,Qt::Key_C);
    this->button_group->addButton(ui->pushButton_d,Qt::Key_D);
    this->button_group->addButton(ui->pushButton_e,Qt::Key_E);
    this->button_group->addButton(ui->pushButton_f,Qt::Key_F);
    this->button_group->addButton(ui->pushButton_g,Qt::Key_G);
    this->button_group->addButton(ui->pushButton_h,Qt::Key_H);
    this->button_group->addButton(ui->pushButton_i,Qt::Key_I);
    this->button_group->addButton(ui->pushButton_j,Qt::Key_J);
    this->button_group->addButton(ui->pushButton_k,Qt::Key_K);
    this->button_group->addButton(ui->pushButton_l,Qt::Key_L);
    this->button_group->addButton(ui->pushButton_m,Qt::Key_M);
    this->button_group->addButton(ui->pushButton_n,Qt::Key_N);
    this->button_group->addButton(ui->pushButton_o,Qt::Key_O);
    this->button_group->addButton(ui->pushButton_p,Qt::Key_P);
    this->button_group->addButton(ui->pushButton_q,Qt::Key_Q);
    this->button_group->addButton(ui->pushButton_r,Qt::Key_R);
    this->button_group->addButton(ui->pushButton_s,Qt::Key_S);
    this->button_group->addButton(ui->pushButton_t,Qt::Key_T);
    this->button_group->addButton(ui->pushButton_u,Qt::Key_U);
    this->button_group->addButton(ui->pushButton_v,Qt::Key_V);
    this->button_group->addButton(ui->pushButton_w,Qt::Key_W);
    this->button_group->addButton(ui->pushButton_x,Qt::Key_X);
    this->button_group->addButton(ui->pushButton_y,Qt::Key_Y);
    this->button_group->addButton(ui->pushButton_z,Qt::Key_Z);
    this->button_group->addButton(ui->pushButton_z,Qt::Key_Z);
    this->button_group->addButton(ui->pushButton_period,Qt::Key_periodcentered);
    this->button_group->addButton(ui->pushButton_gang,Qt::Key_Minus);
    this->button_group->addButton(ui->pushButton_deng,Qt::Key_Equal);
    this->button_group->addButton(ui->pushButton_zuokuo,Qt::Key_BracketLeft);
    this->button_group->addButton(ui->pushButton_youkuo,Qt::Key_BracketRight);
    this->button_group->addButton(ui->pushButton_semicolon,Qt::Key_Semicolon);
    this->button_group->addButton(ui->pushButton_quote,Qt::Key_QuoteDbl	);
    this->button_group->addButton(ui->pushButton_backsplash,Qt::Key_Backslash);
    this->button_group->addButton(ui->pushButton_comma,Qt::Key_Comma);
    this->button_group->addButton(ui->pushButton_splash,Qt::Key_Slash);


    this->button_group->addButton(ui->pushButton_symbol1,Qt::Key_Exclam);// !
    this->button_group->addButton(ui->pushButton_symbol2,Qt::Key_At );//@
    this->button_group->addButton(ui->pushButton_symbol3,Qt::Key_NumberSign );//#
    this->button_group->addButton(ui->pushButton_symbol4,Qt::Key_Dollar );//$
    this->button_group->addButton(ui->pushButton_symbol5,Qt::Key_Percent);//%
    this->button_group->addButton(ui->pushButton_symbol6,Qt::Key_AsciiCircum);//^
    this->button_group->addButton(ui->pushButton_symbol7,Qt::Key_Ampersand);//&
    this->button_group->addButton(ui->pushButton_symbol8,Qt::Key_ParenLeft); //(
    this->button_group->addButton(ui->pushButton_symbol9,Qt::Key_ParenRight); //)
    this->button_group->addButton(ui->pushButton_symbol10,Qt::Key_Underscore);//_
    this->button_group->addButton(ui->pushButton_symbol11,Qt::Key_Less);//<
    this->button_group->addButton(ui->pushButton_symbol12,Qt::Key_Greater );//>
    this->button_group->addButton(ui->pushButton_Add,Qt::Key_Plus);//+
    this->button_group->addButton(ui->pushButton_Mul,Qt::Key_Asterisk);//*

//    this->button_group->addButton(ui->key_Space,Qt::Key_Space);
//    this->button_group->addButton(ui->key_Enter,Qt::Key_Enter);
//    this->button_group->addButton(ui->key_Backspace,Qt::Key_Backspace);
//    this->button_group->addButton(ui->key_Escape,Qt::Key_Escape);
}

void KeyboardDlg::ButtonJudge(int id )
{
    switch (id)
    {
    case Qt::Key_0 :
        emit this->SendInputMessage("0");
        break;
    case Qt::Key_1 :
        emit this->SendInputMessage("1");
        break;
    case Qt::Key_2 :
        emit this->SendInputMessage("2");
        break;
    case Qt::Key_3 :
        emit this->SendInputMessage("3");
        break;
    case Qt::Key_4 :
        emit this->SendInputMessage("4");
        break;
    case Qt::Key_5 :
        emit this->SendInputMessage("5");
        break;
    case Qt::Key_6 :
        emit this->SendInputMessage("6");
        break;
    case Qt::Key_7 :
        emit this->SendInputMessage("7");
        break;
    case Qt::Key_8 :
        emit this->SendInputMessage("8");
        break;
    case Qt::Key_9 :
        emit this->SendInputMessage("9");
        break;


    case Qt::Key_A :
        emit this->SendInputMessage(ui->pushButton_a->text());
        break;
    case Qt::Key_B :
        emit this->SendInputMessage(ui->pushButton_b->text());
        break;
    case Qt::Key_C :
        emit this->SendInputMessage(ui->pushButton_c->text());
        break;
    case Qt::Key_D :
        emit this->SendInputMessage(ui->pushButton_d->text());
        break;
    case Qt::Key_E :
        emit this->SendInputMessage(ui->pushButton_e->text());
        break;
    case Qt::Key_F :
        emit this->SendInputMessage(ui->pushButton_f->text());
        break;
    case Qt::Key_G :
        emit this->SendInputMessage(ui->pushButton_g->text());
        break;
    case Qt::Key_H :
        emit this->SendInputMessage(ui->pushButton_h->text());
        break;
    case Qt::Key_I :
        emit this->SendInputMessage(ui->pushButton_i->text());
        break;
    case Qt::Key_J :
        emit this->SendInputMessage(ui->pushButton_j->text());
        break;
    case Qt::Key_K :
        emit this->SendInputMessage(ui->pushButton_k->text());
        break;
    case Qt::Key_L :
        emit this->SendInputMessage(ui->pushButton_l->text());
        break;
    case Qt::Key_M :
        emit this->SendInputMessage(ui->pushButton_m->text());
        break;
    case Qt::Key_N :
        emit this->SendInputMessage(ui->pushButton_n->text());
        break;
    case Qt::Key_O :
        emit this->SendInputMessage(ui->pushButton_o->text());
        break;
    case Qt::Key_P :
        emit this->SendInputMessage(ui->pushButton_p->text());
        break;
    case Qt::Key_Q :
        emit this->SendInputMessage(ui->pushButton_q->text());
        break;
    case Qt::Key_R :
        emit this->SendInputMessage(ui->pushButton_r->text());
        break;
    case Qt::Key_S :
        emit this->SendInputMessage(ui->pushButton_s->text());
        break;
    case Qt::Key_T :
        emit this->SendInputMessage(ui->pushButton_t->text());
        break;
    case Qt::Key_U :
        emit this->SendInputMessage(ui->pushButton_u->text());
        break;
    case Qt::Key_V :
        emit this->SendInputMessage(ui->pushButton_v->text());
        break;
    case Qt::Key_W :
        emit this->SendInputMessage(ui->pushButton_w->text());
        break;
    case Qt::Key_X :
        emit this->SendInputMessage(ui->pushButton_x->text());
        break;
    case Qt::Key_Y :
        emit this->SendInputMessage(ui->pushButton_y->text());
        break;
    case Qt::Key_Z :
        emit this->SendInputMessage(ui->pushButton_z->text());
        break;
    case Qt::Key_periodcentered :
        emit this->SendInputMessage(".");
        break;//
    case Qt::Key_Minus :
        emit this->SendInputMessage("-");
        break;//
    case Qt::Key_Equal :
        emit this->SendInputMessage("=");
        break;//
    case Qt::Key_BracketLeft :
        emit this->SendInputMessage("[");
        break;//
    case Qt::Key_BracketRight :
        emit this->SendInputMessage("]");
        break;//
    case Qt::Key_Semicolon :
        emit this->SendInputMessage(";");
        break;//
    case Qt::Key_QuoteDbl :
        emit this->SendInputMessage("\"");
        break;//
    case Qt::Key_Backslash :
        emit this->SendInputMessage(ui->pushButton_backsplash->text());
        break;//
    case Qt::Key_Comma :
        emit this->SendInputMessage(",");
        break;//
    case Qt::Key_Slash :
        emit this->SendInputMessage("/");
        break;//

    case Qt::Key_Space :
        emit this->SendInputMessage(" ");
        break;
    case Qt::Key_Exclam :
        emit this->SendInputMessage("!");
        break;
    case Qt::Key_At :
        emit this->SendInputMessage("@");
        break;
    case Qt::Key_NumberSign :
        emit this->SendInputMessage("#");
        break;
    case Qt::Key_Dollar :
        emit this->SendInputMessage("$");
        break;
    case Qt::Key_Percent :
        emit this->SendInputMessage("%");
        break;
    case Qt::Key_AsciiCircum :
        emit this->SendInputMessage("^");
        break;
    case Qt::Key_Ampersand :
        emit this->SendInputMessage("&");
        break;
    case Qt::Key_ParenLeft :
        emit this->SendInputMessage("(");
        break;
    case Qt::Key_ParenRight :
        emit this->SendInputMessage(")");
        break;
    case Qt::Key_Underscore :
        emit this->SendInputMessage("_");
        break;
    case Qt::Key_Less :
        emit this->SendInputMessage("<");
        break;
    case Qt::Key_Greater :
        emit this->SendInputMessage(">");
        break;
    case Qt::Key_Plus :
        emit this->SendInputMessage("+");
        break;
    case Qt::Key_Asterisk :
        emit this->SendInputMessage("*");
        break;


//    case Qt::Key_Backspace :
//        emit this->SendBackspace();
//        break;

//    case Qt::Key_Enter :
//        emit this->SendEnter();
//        break;
//    case Qt::Key_Escape :
//        emit this->SenEscape();
//        break;
    default:
        emit this->SendInputMessage("wrong");
        break;

    }
}
void KeyboardDlg::PreeditContent(QString str)
{
    m_InputStr = ui->lineEdit_window->text();
    m_InputStr.append(str);
    ui->lineEdit_window->setText(m_InputStr);
    if(currentLineEdit != 0)
        currentLineEdit->setText(m_InputStr);
}

/**
 * @brief KeyboardDlg::on_pushButton_backspace_clicked
 * @note backspace,软键盘删除
 */
void KeyboardDlg::on_pushButton_backspace_clicked()
{
    int pos = ui->lineEdit_window->cursorPosition()-1;
    if(pos == -1)
    {
        return;
    }
    //ui->lineEdit_window->cursorPositionChanged();
    m_InputStr.remove(ui->lineEdit_window->cursorPosition()-1,1);
    ui->lineEdit_window->setText(m_InputStr);
    ui->lineEdit_window->setCursorPosition(pos);
    ui->lineEdit_window->setFocus();
    if(currentLineEdit != 0)
        currentLineEdit->setText(m_InputStr);
}


QString KeyboardDlg::GetInputString()
{
    return ui->lineEdit_window->text();
}

void KeyboardDlg::SetInputString(QString str)
{
    m_InputStr = str;
    ui->lineEdit_window->setText(m_InputStr);
}

void KeyboardDlg::SetInputObj(QObject *w)
{
    currentLineEdit = (QLineEdit*)w;
}

void KeyboardDlg::PassWordInput()
{
    ui->lineEdit_window->setEchoMode(QLineEdit::Password);
}

void KeyboardDlg::on_pushButton_Cancel_clicked()
{
    ui->lineEdit_window->clear();
    if(currentLineEdit == NULL)
    {
        return;
    }
    currentLineEdit->clear();
}
//lowercase  capital
void KeyboardDlg::on_pushButton_Caps_clicked()
{
    if(b_Caps){
        b_Caps = false;
        ChangeLowercase();
    }else{
        b_Caps = true;
        ChangeCapital();
    }
}

void KeyboardDlg::ChangeCapital()
{
    ui->pushButton_a->setText(tr("A"));
    ui->pushButton_b->setText(tr("B"));
    ui->pushButton_c->setText(tr("C"));
    ui->pushButton_d->setText(tr("D"));
    ui->pushButton_e->setText(tr("E"));
    ui->pushButton_f->setText(tr("F"));
    ui->pushButton_g->setText(tr("G"));
    ui->pushButton_h->setText(tr("H"));
    ui->pushButton_i->setText(tr("I"));
    ui->pushButton_j->setText(tr("J"));
    ui->pushButton_k->setText(tr("K"));
    ui->pushButton_l->setText(tr("L"));
    ui->pushButton_m->setText(tr("M"));
    ui->pushButton_n->setText(tr("N"));
    ui->pushButton_o->setText(tr("O"));
    ui->pushButton_p->setText(tr("P"));
    ui->pushButton_q->setText(tr("Q"));
    ui->pushButton_r->setText(tr("R"));
    ui->pushButton_s->setText(tr("S"));
    ui->pushButton_t->setText(tr("T"));
    ui->pushButton_u->setText(tr("U"));
    ui->pushButton_v->setText(tr("V"));
    ui->pushButton_w->setText(tr("W"));
    ui->pushButton_x->setText(tr("X"));
    ui->pushButton_y->setText(tr("Y"));
    ui->pushButton_z->setText(tr("Z"));
}


void KeyboardDlg::ChangeLowercase()
{
    ui->pushButton_a->setText(tr("a"));
    ui->pushButton_b->setText(tr("b"));
    ui->pushButton_c->setText(tr("c"));
    ui->pushButton_d->setText(tr("d"));
    ui->pushButton_e->setText(tr("e"));
    ui->pushButton_f->setText(tr("f"));
    ui->pushButton_g->setText(tr("g"));
    ui->pushButton_h->setText(tr("h"));
    ui->pushButton_i->setText(tr("i"));
    ui->pushButton_j->setText(tr("j"));
    ui->pushButton_k->setText(tr("k"));
    ui->pushButton_l->setText(tr("l"));
    ui->pushButton_m->setText(tr("m"));
    ui->pushButton_n->setText(tr("n"));
    ui->pushButton_o->setText(tr("o"));
    ui->pushButton_p->setText(tr("p"));
    ui->pushButton_q->setText(tr("q"));
    ui->pushButton_r->setText(tr("r"));
    ui->pushButton_s->setText(tr("s"));
    ui->pushButton_t->setText(tr("t"));
    ui->pushButton_u->setText(tr("u"));
    ui->pushButton_v->setText(tr("v"));
    ui->pushButton_w->setText(tr("w"));
    ui->pushButton_x->setText(tr("x"));
    ui->pushButton_y->setText(tr("y"));
    ui->pushButton_z->setText(tr("z"));
}

void KeyboardDlg::on_pushButton_Quit_clicked()
{
    QDialog::reject();
}
