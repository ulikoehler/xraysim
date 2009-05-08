#include "alphatestdialog.h"
#include "ui_alphatestdialog.h"

AlphaTestDialog::AlphaTestDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AlphaTestDialog)
{
    m_ui->setupUi(this);
    //Connect the signals
    connect(m_ui->greaterRadioButton, SIGNAL(toggled(bool)), this, SLOT(guiStateChanged()));
    connect(m_ui->lessRadioButton, SIGNAL(toggled(bool)), this, SLOT(guiStateChanged()));
    connect(m_ui->lessOrEqualRadioButton, SIGNAL(toggled(bool)), this, SLOT(guiStateChanged()));
    connect(m_ui->greaterOrEqualRadioButton, SIGNAL(toggled(bool)), this, SLOT(guiStateChanged()));
    connect(m_ui->notEqualRadioButton, SIGNAL(toggled(bool)), this, SLOT(guiStateChanged()));
    connect(m_ui->equalRadioButton, SIGNAL(toggled(bool)), this, SLOT(guiStateChanged()));
    connect(m_ui->alwaysRadioButton, SIGNAL(toggled(bool)), this, SLOT(guiStateChanged()));
    connect(m_ui->neverRadioButton, SIGNAL(toggled(bool)), this, SLOT(guiStateChanged()));

    connect(m_ui->valueSpinBox, SIGNAL(valueChanged(double)), this, SLOT(guiStateChanged()));
}

AlphaTestDialog::~AlphaTestDialog()
{
    delete m_ui;
}

void AlphaTestDialog::guiStateChanged()
{
    uint mode = UINT_MAX;
    double value;
    //Select the mode
    if(m_ui->greaterRadioButton->isChecked()) {mode = GL_GREATER;}
    else if(m_ui->lessRadioButton->isChecked()) {mode = GL_LESS;}
    else if(m_ui->lessOrEqualRadioButton->isChecked()) {mode = GL_LEQUAL;}
    else if(m_ui->greaterOrEqualRadioButton->isChecked()) {mode = GL_GEQUAL;}
    else if(m_ui->notEqualRadioButton->isChecked()) {mode = GL_NOTEQUAL;}
    else if(m_ui->equalRadioButton->isChecked()) {mode = GL_EQUAL;}
    else if(m_ui->alwaysRadioButton->isChecked()){mode = GL_ALWAYS;}
    else if(m_ui->neverRadioButton->isChecked()) {mode = GL_NEVER;}

    //Get the value
    value = m_ui->valueSpinBox->value();
    //Emit the signal
    emit alphaTestChanged(mode, value);
}

void AlphaTestDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
